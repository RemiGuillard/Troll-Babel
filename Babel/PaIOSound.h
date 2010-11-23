#ifndef		PAIOSOUND_H
# define	PAIOSOUND_H

#include <iostream>
#include "AbsIOSound.hpp"
#include "portaudio.h"

/*#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SILENCE  (0.0f)
typedef float SAMPLE;*/

#define PA_SAMPLE_TYPE  paInt16
#define SAMPLE_SILENCE  (0)
typedef short SAMPLE;

class		PaIOSound : public AbsIOSound<SAMPLE>
{
public:
	PaIOSound();
	~PaIOSound();
public:
	virtual void recordVoice();
	virtual void playVoice(const UdpNetwork&);
	//virtual StopPlayRecord();
	virtual IOStreamData<SAMPLE>	*getdata();
};

#endif	//	!PAIOSOUND_H