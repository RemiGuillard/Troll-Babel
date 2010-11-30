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
public:
	PaIOSound();
	~PaIOSound();
public:
	virtual void recordVoice();
	virtual void playVoice(QString ip, quint16 port);
	//virtual StopPlayRecord();
	virtual IOStreamData<SAMPLE>    *getdata();
	virtual Encoder                 &getEncode();
};

#endif  //      !PAIOSOUND_H
