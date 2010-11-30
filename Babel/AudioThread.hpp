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
	/*	QUdpSocket& socket = static_cast<QUdpSocket&>(this->net.getSocket());
		socket.bind(port);
		this->net.socketConnection(ip, port);*/
	}
	//Instanciation explicite!!!!!!
public:
	//void  setIOSound(AbsIOSound<T> *);
	template <typename A>
	void    setBuf(A *dest, A *from)
	{
		int i;
		for (i = 0 ; i < FRAMES_PER_BUFFER ; i++)
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
			//this->setData(this->DataTmp, this->data);
		//if (this->DataTmp.IAvailable)
		//{
				T	tmp[160];
				data->IBuf->readBlock(tmp, 160);
				this->enc.encode(tmp, this->data->encoded);
				DataClientPack  send;
				send.dataLenght = FRAMES_PER_BUFFER;
				this->setBuf(send.data, this->data->encoded);
				this->net.packetSend(reinterpret_cast<char*>(&send));
			//this->data->IAvailable = false;
		//}
		/*if (!this->DataTmp.OAvailable)
			{
				if (this->net.getSocket().waitForReadyRead(10))
				{     
					DataClientPack  *rcv;
					rcv = reinterpret_cast<DataClientPack*>(this->net.packetRcv());
					SAMPLE output[FRAMES_PER_BUFFER];
					this->enc.decode(rcv->data, output);
					this->data->OMaxFrameIndex = rcv->dataLenght / NUM_CHANNELS;
					this->setBuf(this->data->OBuf, output);                         
					this->data->OAvailable = true;
				}
			}*/
		}
		/*this->net.disconnect();*/
		return ;
	}
private:
	IOStreamData<T> *data;
	UdpNetwork      net;    
	//IOStreamData<T> DataTmp;
	Encoder enc;
};

#endif  //      !AUDIOTHREAD_H
