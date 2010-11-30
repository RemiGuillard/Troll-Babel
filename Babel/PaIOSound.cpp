#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "AbsIOSound.hpp"
#include "portaudio.h"
#include "PaIOSound.h"

PaIOSound::PaIOSound()
{
	PaError _err;
	_err = Pa_Initialize();
	if(_err != paNoError)
		throw "construction fail";
	this->_data.IBuf = new BabelBuffer<SAMPLE>(4096);
	this->_data.OBuf = new BabelBuffer<SAMPLE>(4096);
	this->_data.IAvailable = false;
	//this->_data.IFrameIndex = 0;
	this->_data.IMaxFrameIndex = FRAMES_PER_BUFFER / NUM_CHANNELS;
	this->_data.OAvailable = false;
	//this->_data.OFrameIndex = 0;
	this->_data.OMaxFrameIndex = 0;
	this->_data.ThreadEnd = true;
	std::cout << "object created" << std::endl;
}

PaIOSound::~PaIOSound()
{
	PaError _err;
	_err = Pa_IsStreamActive(reinterpret_cast<PaStream *>(this->_stream));
	if (_err == 0)
	{
		_err = Pa_StopStream(reinterpret_cast<PaStream *>(this->_stream));
		if(_err != paNoError)
			throw "Stopping fail";
	}        
	_err = Pa_CloseStream(reinterpret_cast<PaStream *>(this->_stream));
	if(_err != paNoError)
		throw "closing fail";
	_err = Pa_Terminate();
	if(_err != paNoError)
		throw "destruction fail";
}


int PaRecordCallback(const void *input, void *output, 
					 unsigned long frameCount, 
					 const PaStreamCallbackTimeInfo*, 
					 PaStreamCallbackFlags, 
					 void *userData)
{
	IOStreamData<SAMPLE> *data = static_cast<IOStreamData<SAMPLE> *>(userData);
	//data->mutex.lock();   
	const SAMPLE *riptr = static_cast<const SAMPLE *>(input);
	//SAMPLE *wiptr = data->IBuf;
	unsigned long framesToCalc, i;
	framesToCalc = frameCount;

	//if (!data->IAvailable)
	//{
	data->IBuf->writeBlock(riptr, 160);
		
	/*for(i=0; i<framesToCalc; i++)
	{
	*(wiptr++) = *(riptr++);  // left 
	if( NUM_CHANNELS == 2 ) *(wiptr++) = *(riptr++);  // right 
	}*/

	//	data->IAvailable = true;
	//emit dataAvailable(*data);
	//	}
	//if (data->OAvailable)
	//{
	SAMPLE *woptr = static_cast<SAMPLE *>(output);
	//const SAMPLE *roptr = data->OBuf;
	framesToCalc = data->OMaxFrameIndex;
	
	data->OBuf->readBlock(woptr, 160);
	
	/*for(i=0; i<framesToCalc; i++)
	{
		*woptr++ = *roptr++;  // left 
		if( NUM_CHANNELS == 2 ) *woptr++ = *roptr++;  // right 
	}*/
	//	data->OAvailable = false;
	//}
	//data->mutex.unlock(); 
	return 0;
}

/*int PatestCallback(const void *input, void *output, 
unsigned long frameCount, 
const PaStreamCallbackTimeInfo*, 
PaStreamCallbackFlags, 
void *userData)
{
int i;
const SAMPLE *riptr = static_cast<const SAMPLE *>(input);
SAMPLE *wiptr = static_cast<SAMPLE *>(output);

for (i=0; i<frameCount; i++)
{
*(wiptr++) = *(riptr++);
if (NUM_CHANNELS == 2) *(wiptr++) = *(riptr++);
}
return 0;
}*/

void    PaIOSound::recordVoice()
{
	PaError _err;
	std::cout << "before opening" << std::endl;
	_err = Pa_OpenDefaultStream(reinterpret_cast<PaStream **>(&this->_stream),
		NUM_CHANNELS, //input 2
		NUM_CHANNELS, //output 2
		PA_SAMPLE_TYPE, // short (PaInt16) pour speex
		SAMPLE_RATE,  // 8000
		FRAMES_PER_BUFFER / NUM_CHANNELS, // size buff 256
		PaRecordCallback,
		static_cast<void *>(&this->_data));
	std::cout << "after opening" << std::endl;
	if(_err != paNoError) 
	{
		std::cout << Pa_GetErrorText(_err) << std::endl;
		throw "opening fail";
	}
	std::cout << "before starting" << std::endl;
	_err = Pa_StartStream(reinterpret_cast<PaStream *>(this->_stream));
	std::cout << "after starting" << std::endl;
	if(_err != paNoError) 
		throw "start fail";
}

//template <typename T>
IOStreamData<SAMPLE>    *PaIOSound::getdata()
{
	return &this->_data;
}

Encoder         &PaIOSound::getEncode()
{
	return this->enc;
}

/*void  PaIOSound::writeDataToNetwork(IOStreamData<SAMPLE> data)
{
if (data.IAvailable)
{
Encoder enc;
enc.encode(data.IBuf, data.encoded);
DataClientPack  send;
send.dataLenght = FRAMES_PER_BUFFER;
//      this->setBuf(send.data, this->DataTmp.encoded);
int i;
for(i=0;i<FRAMES_PER_BUFFER;i++)
send.data[i] = data.encoded[i];
data.Net->packetSend(reinterpret_cast<char*>(&send));
this->_data.IAvailable = false;
}
}*/

void PaIOSound::playVoice(QString ip, quint16 port)
{
	AudioThread<SAMPLE>     *th = new AudioThread<SAMPLE>(ip, port, &this->_data);
	//AudioThread<SAMPLE>   th(Net, this->_data);

	//th.setIOSound(this);
	th->start();     
	this->recordVoice();
	//QMessageBox::information(NULL, "test", QString(this->_data.aff));
}
