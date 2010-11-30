#ifndef         IOSTREAMDATA
# define        IOSTREAMDATA

#define FRAMES_PER_BUFFER (160)

#include "UdpNetwork.h"
#include "BabelBuffer.hpp"
//#include <QMutex>

template <typename T>
struct IOStreamData
{
	BabelBuffer<T>	*IBuf;
	//QMutex mutex;
	bool			IAvailable; // a transformer en mutex
	//int           IFrameIndex;  /* Index into sample array. */
	int				IMaxFrameIndex;
	BabelBuffer<T>	*OBuf;
	bool			OAvailable; // mutex
	//int			OFrameIndex;  /* Index into sample array. */
	int				OMaxFrameIndex;
	char			encoded[FRAMES_PER_BUFFER];
	bool            ThreadEnd;
};

#endif  //      !IOSTREAMDATA
