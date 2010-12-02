#ifndef         AUDIOTHREAD_H
# define        AUDIOTHREAD_H

#include <QByteArray>
#include <QQueue>
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

	///////////////////////////////////////////
	void    run()
	{
		while (this->data->ThreadEnd)
		{
				T	tmp[160];
				
				data->IBuf->readBlock(tmp, FRAMES_PER_BUFFER);
				this->enc.encode(tmp, this->data->encoded);
				DataClientPack  send;
				send.dataLenght = FRAMES_PER_BUFFER;
				this->setBuf(send.data, this->data->encoded);
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
