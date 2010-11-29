#ifndef         PAIOSOUND_H
# define        PAIOSOUND_H

#include <iostream>
#include <QObject>
#include "AbsIOSound.hpp"
#include "portaudio.h"
#include "AudioThread.hpp"


/*#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SILENCE  (0.0f)
typedef float SAMPLE;*/

#define PA_SAMPLE_TYPE  paInt16
#define SAMPLE_SILENCE  (0)
typedef short SAMPLE;

class           PaIOSound : public AbsIOSound<SAMPLE>
{
	//      Q_OBJECT
public:
	PaIOSound();
	~PaIOSound();
public:
	virtual void recordVoice();
	virtual void playVoice();
	//virtual StopPlayRecord();
	virtual IOStreamData<SAMPLE>    *getdata();
	virtual Encoder                                 &getEncode();
	/*      template <typename A>
	void    setBuf(A *dest, A *from)
	{
	int i;
	for (i=0;i<FRAMES_PER_BUFFER;i++)
	dest[i] = from[i];
	}*/
	/*int PaRecordCallback(const void *input, void *output, 
	unsigned long frameCount, 
	const PaStreamCallbackTimeInfo*, 
	PaStreamCallbackFlags, 
	void *userData);*/

	/*signals:
	void   dataAvailable(IOStreamData<SAMPLE> data);

	public slots:
	void    writeDataToNetwork(IOStreamData<SAMPLE> data);*/

};

#endif  //      !PAIOSOUND_H
