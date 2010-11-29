#ifndef         IOSTREAMDATA
# define        IOSTREAMDATA

#define FRAMES_PER_BUFFER (160)

#include "UdpNetwork.h"
//#include <QMutex>

template <typename T>
struct IOStreamData
{
	T               IBuf[FRAMES_PER_BUFFER];
	//QMutex mutex;
	bool    IAvailable; // a transformer en mutex
	//int           IFrameIndex;  /* Index into sample array. */
	int         IMaxFrameIndex;
	T               OBuf[FRAMES_PER_BUFFER];
	bool    OAvailable; // mutex
	//int           OFrameIndex;  /* Index into sample array. */
	int         OMaxFrameIndex;
	char    encoded[FRAMES_PER_BUFFER];
	bool            ThreadEnd;
	UdpNetwork      *Net;
};

#endif  //      !IOSTREAMDATA
