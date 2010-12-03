#ifndef         IOSTREAMDATA
# define        IOSTREAMDATA

#define FRAMES_PER_BUFFER (160)

#include "BabelBuffer.hpp"

template <typename T>
struct IOStreamData
{
	BabelBuffer<T>	*IBuf;
	int				IMaxFrameIndex;
	BabelBuffer<T>	*OBuf;
	int				OMaxFrameIndex;
	char			encoded[FRAMES_PER_BUFFER];
	bool            ThreadEnd;
};

#endif  //      !IOSTREAMDATA
