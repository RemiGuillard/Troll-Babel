#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "AbsIOSound.hpp"
#include "portaudio.h"
#include "PaIOSound.h"

PaIOSound::PaIOSound()/*: AbsIOSound<SAMPLE>()*/
{
	PaError	_err;
	_err = Pa_Initialize();
	if(_err != paNoError)
		throw "construction fail";
	this->_data.IAvailable = false;
	//this->_data.IFrameIndex = 0;
	this->_data.IMaxFrameIndex = FRAMES_PER_BUFFER / NUM_CHANNELS;
	this->_data.OAvailable = false;
	//this->_data.OFrameIndex = 0;
	this->_data.OMaxFrameIndex = 0;
	this->_data.ThreadEnd = 1;
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
	const SAMPLE *riptr = static_cast<const SAMPLE *>(input);
	SAMPLE *wiptr = data->IBuf;
	unsigned long framesToCalc, i;
	framesToCalc = frameCount;
	for(i=0; i<framesToCalc; i++)
	{
		*(wiptr++) = *(riptr++);  /* left */
		if( NUM_CHANNELS == 2 ) *(wiptr++) = *(riptr++);  /* right */
	}
	/*Encoder		*encode = new Encoder(8);
	encode->encode(data->IBuf, data->encode);
	encode->decode(data->encode, data->OBuf);*/
	/*data->OBuf = data->IBuf;
	data->OMaxFrameIndex = 160 /2;
	data->OAvailable = true;*/
	if (data->OAvailable)
	{
		SAMPLE *woptr = static_cast<SAMPLE *>(output);
		const SAMPLE *roptr = data->OBuf;
		framesToCalc = data->OMaxFrameIndex;
		for(i=0; i<framesToCalc; i++)
		{
			*woptr++ = *roptr++;  /* left */
			if( NUM_CHANNELS == 2 ) *woptr++ = *roptr++;  /* right */
		}
		data->OAvailable = false;
	}
	data->IAvailable = true;
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

void	PaIOSound::recordVoice()
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
IOStreamData<SAMPLE>	*PaIOSound::getdata()
{
	return &this->_data;
}

Encoder		&PaIOSound::getEncode()
{
	return this->enc;
}

void PaIOSound::playVoice(UdpNetwork &Net)
{
	AudioThread<SAMPLE>	th(Net);

	//th.setIOSound(this);
	//this->recordVoice();
}