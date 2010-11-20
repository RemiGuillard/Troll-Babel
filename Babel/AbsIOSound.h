#ifndef		ABSIOSOUND_H
# define	ABSIOSOUND_H

#include <iostream>
#include "AudioThread.h"

#define SAMPLE_RATE  (8000)
#define FRAMES_PER_BUFFER (160)
#define NUM_CHANNELS    (2)

template <typename T>
struct IOStreamData
{
	T		IBuf[FRAMES_PER_BUFFER];
	bool	IAvailable; // a transformer en mutex
	int		IFrameIndex;  /* Index into sample array. */
    int		IMaxFrameIndex;
	T		OBuf[FRAMES_PER_BUFFER];
	bool	OAvailable; // mutex
	int		OFrameIndex;  /* Index into sample array. */
    int		OMaxFrameIndex;
	char	encoded[FRAMES_PER_BUFFER];
	int		ThreadEnd;
};

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
	virtual void playVoice() = 0;
	//virtual StopPlay() = 0;
	virtual IOStreamData<T>	*getdata() = 0;
protected:
	IOStream		*_stream;
	IOStreamData<T>	_data;
};

#endif	//	!ABSIOSOUND_H