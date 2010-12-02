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
	this->_data.IMaxFrameIndex = FRAMES_PER_BUFFER;
	this->_data.OMaxFrameIndex = 0;
	this->_data.ThreadEnd = true;
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
		throw "opening fail";
	_err = Pa_StartStream(reinterpret_cast<PaStream *>(this->_stream));
	if(_err != paNoError) 
		throw "start fail";
}

IOStreamData<SAMPLE>    *PaIOSound::getdata()
{
	return &this->_data;
}

Encoder         &PaIOSound::getEncode()
{
	return this->enc;
}

void PaIOSound::playVoice(QString ip, quint16 port)
{
	AudioThread<SAMPLE>     *th = new AudioThread<SAMPLE>(ip, port, &this->_data);

	this->_data.ThreadEnd = true;
	th->start();     
	this->recordVoice();
}

void	PaIOSound::StopPlayRecord()
{
	PaError _err;
	this->_data.ThreadEnd = false;
	_err = Pa_StopStream(reinterpret_cast<PaStream *>(this->_stream));
	if(_err != paNoError)
		throw "Stopping fail";
	/*_err = Pa_CloseStream(reinterpret_cast<PaStream *>(this->_stream));
	if(_err != paNoError)
		throw "closing fail";*/
}