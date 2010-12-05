#ifndef         PAIOSOUND_H
# define        PAIOSOUND_H

#include <iostream>
#include <QObject>
#include "AbsIOSound.hpp"
#include "portaudio.h"

/*#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SILENCE  (0.0f)
typedef float SAMPLE;*/

#define PA_SAMPLE_TYPE  paInt16
#define SAMPLE_SILENCE  (0)
typedef short SAMPLE;

class           PaIOSound : public AbsIOSound<SAMPLE>
{ 
public:
	PaIOSound(UdpNetwork *net);
	~PaIOSound();
public:
	virtual void					recordVoice();
	virtual void					playVoice();
	virtual void					StopPlayRecord();
	virtual IOStreamData<SAMPLE>	*getdata();
	virtual Encoder                 &getEncode();
};

#endif  //      !PAIOSOUND_H
