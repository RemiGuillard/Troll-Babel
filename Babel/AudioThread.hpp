#ifndef         AUDIOTHREAD_H
# define        AUDIOTHREAD_H

#include <QThread>
#include <QMessageBox>
#include "IOStreamData.hpp"
#include "AbsIOSound.hpp"
#include "PaIOSound.h"
#include "UdpNetwork.h"
#include "DataClientPack.h"

template <typename T>
class   AudioThread : public QThread
{
public:
	AudioThread(QString ip, quint16 port, IOStreamData<T> *Data) : data(Data)
	{
		this->net.socketConnection(ip, port);
	}
public:
	template <typename A>
	void    setBuf(A *dest, A *from)
	{
		int i;
		for (i = 0 ; i < FRAMES_PER_BUFFER ; ++i)
			dest[i] = from[i];
	}

	/////////////////////////////////////////
	void    setData(IOStreamData<T> &Data, IOStreamData<T> *obj)
	{
		Data.IAvailable = obj->IAvailable;
		Data.IMaxFrameIndex = obj->IMaxFrameIndex;
		Data.OAvailable = obj->IAvailable;      
		this->setBuf<T>(Data.IBuf, obj->IBuf);
	}

	///////////////////////////////////////////
	void    run()
	{
		while (this->data->ThreadEnd)
		{
				T	tmp[160];
				data->IBuf->readBlock(tmp, 160);
				//this->enc.encode(tmp, this->data->encoded);
				DataClientPack  send;
				send.dataLenght = FRAMES_PER_BUFFER;
				this->setBuf(send.data, tmp);//this->data->encoded);
				this->net.packetSend(reinterpret_cast<char*>(&send));
		}
		this->net.disconnect();
		return ;
	}
private:
	IOStreamData<T> *data;
	UdpNetwork      net;    
	Encoder enc;
};

#endif  //      !AUDIOTHREAD_H
