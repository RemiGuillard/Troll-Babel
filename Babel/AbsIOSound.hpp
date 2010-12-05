#ifndef         ABSIOSOUND_H
# define        ABSIOSOUND_H

#include <QString>
#include <iostream>
#include "IOStreamData.hpp"
#include "Encoder.h"
#include "AudioThread.hpp"

#define SAMPLE_RATE  (8000)
#define NUM_CHANNELS    (2)

template <typename T>
class           AbsIOSound
{
public:
        typedef void* IOStream;
public:
        virtual void			recordVoice() = 0;
        virtual void			playVoice() = 0;
		virtual void			StopPlayRecord() = 0;
        virtual IOStreamData<T> *getdata() = 0;
        virtual Encoder         &getEncode() = 0;
protected:
        IOStream                *_stream;
        IOStreamData<T>			_data;
        Encoder                 enc;
		AudioThread<T>			*th;
};

#endif  //      !ABSIOSOUND_H
