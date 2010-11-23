#ifndef		ABSIOSOUND_H
# define	ABSIOSOUND_H

#include <iostream>
#include "IOStreamData.hpp"
#include "UdpNetwork.h"

#define SAMPLE_RATE  (8000)
#define NUM_CHANNELS    (2)


template <typename T>
class		AbsIOSound
{
public:
	typedef void* IOStream;
	/*AbsIOSound() {}
	~AbsIOSound() {}*/
public:
	virtual void recordVoice() = 0;
	//virtual stopRecord() = 0;
	virtual void playVoice(const UdpNetwork&) = 0;
	//virtual StopPlay() = 0;
	virtual IOStreamData<T>	*getdata() = 0;
protected:
	IOStream		*_stream;
	IOStreamData<T>	_data;
};

#endif	//	!ABSIOSOUND_H