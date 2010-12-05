#include "PaIOSound.h"
#include "PaOpenStreamException.h"
#include "PaStartStreamException.h"
#include "PaStopStreamException.h"
#include "PaIniException.h"
#include "PaCloseException.h"

PaIOSound::PaIOSound(UdpNetwork *net)
{
  PaError _err;
  _err = Pa_Initialize();
  if(_err != paNoError)
    throw new PaIniException;
  this->_data.IBuf = new BabelBuffer<SAMPLE>(4096);
  this->_data.OBuf = new BabelBuffer<SAMPLE>(4096);
  this->_data.IMaxFrameIndex = FRAMES_PER_BUFFER;
  this->_data.OMaxFrameIndex = 0;
  this->_data.ThreadEnd = false;
  this->th = new AudioThread<SAMPLE>(&this->_data, net);
}

PaIOSound::~PaIOSound()
{
  PaError _err;
  this->_data.ThreadEnd = false;
  _err = Pa_IsStreamActive(reinterpret_cast<PaStream *>(this->_stream));
  if (_err == 1)
    {
      _err = Pa_StopStream(reinterpret_cast<PaStream *>(this->_stream));
      if(_err != paNoError)
		throw new PaStopStreamException;
    }
  _err = Pa_CloseStream(reinterpret_cast<PaStream *>(this->_stream));
  if(_err != paNoError)
    throw new PaCloseException;
  _err = Pa_Terminate();
  if(_err != paNoError)
    throw new PaCloseException;
  delete this->th;
  delete this->_data.IBuf;
  delete this->_data.OBuf;
}


int PaRecordCallback(const void *input, void *output,
		     unsigned long frameCount,
		     const PaStreamCallbackTimeInfo*,
		     PaStreamCallbackFlags,
		     void *userData)
{
  IOStreamData<SAMPLE> *data = static_cast<IOStreamData<SAMPLE> *>(userData);
  const SAMPLE *riptr = static_cast<const SAMPLE *>(input);
  unsigned long framesToCalc;
  framesToCalc = frameCount * NUM_CHANNELS;

  data->IBuf->writeBlock(riptr, framesToCalc);

  SAMPLE *woptr = static_cast<SAMPLE *>(output);
  framesToCalc = data->OMaxFrameIndex;

  data->OBuf->readBlock(woptr, framesToCalc);
  return 0;
}

void    PaIOSound::recordVoice()
{
  PaError _err;
  _err = Pa_OpenDefaultStream(reinterpret_cast<PaStream **>(&this->_stream),
			      NUM_CHANNELS, //input 2
			      NUM_CHANNELS, //output 2
			      PA_SAMPLE_TYPE, // short (PaInt16) pour speex
			      SAMPLE_RATE,  // 8000
			      FRAMES_PER_BUFFER / NUM_CHANNELS, // size buff 160
			      PaRecordCallback,
			      static_cast<void *>(&this->_data));
  if(_err != paNoError)
    throw new PaOpenStreamException;
  _err = Pa_StartStream(reinterpret_cast<PaStream *>(this->_stream));
  if(_err != paNoError)
    throw new PaStartStreamException;
}

IOStreamData<SAMPLE>    *PaIOSound::getdata()
{
  return &this->_data;
}

Encoder         &PaIOSound::getEncode()
{
  return this->enc;
}

void PaIOSound::playVoice()
{
	this->_data.ThreadEnd = true;
	this->th->start();
	this->recordVoice();
}

void	PaIOSound::StopPlayRecord()
{
  PaError _err;

  if (this->_data.ThreadEnd == true)
  {
	  this->_data.ThreadEnd = false;
	  _err = Pa_IsStreamActive(reinterpret_cast<PaStream *>(this->_stream));
	  if (_err == 1)
	  {
		  _err = Pa_StopStream(reinterpret_cast<PaStream *>(this->_stream));
		  if(_err != paNoError)
			  throw new PaStopStreamException;
	  }
  }
  /*_err = Pa_CloseStream(reinterpret_cast<PaStream *>(this->_stream));
    if(_err != paNoError)
    throw "closing fail";*/
}
