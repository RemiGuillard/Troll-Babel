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
		QUdpSocket& socket = static_cast<QUdpSocket&>(this->net.getSocket());
		socket.bind(port);
		this->net.socketConnection(ip, port);
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
			this->setData(this->DataTmp, this->data);
		//	if (this->DataTmp.IAvailable)
		//	{
				this->enc.encode(this->DataTmp.IBuf, this->DataTmp.encoded);
				DataClientPack  send;
				send.dataLenght = FRAMES_PER_BUFFER;
				this->setBuf(send.data, this->DataTmp.encoded);
				this->net.packetSend(reinterpret_cast<char*>(&send));
				//this->data->IAvailable = false;
		//	}
		//	if (!this->DataTmp.OAvailable)
		//	{
				if (this->net.getSocket().waitForReadyRead(10))
				{     
					DataClientPack  *rcv;
					rcv = reinterpret_cast<DataClientPack*>(this->net.packetRcv());
					SAMPLE output[FRAMES_PER_BUFFER];
					this->enc.decode(rcv->data, output);
					this->data->OMaxFrameIndex = rcv->dataLenght / NUM_CHANNELS;
					this->setBuf(this->data->OBuf, output);                         
				//	this->data->OAvailable = true;
				}
		//	}
		}
		/*this->net.disconnect();*/
		return ;
	}
private:
	IOStreamData<T> *data;
	UdpNetwork      net;    
	IOStreamData<T> DataTmp;
	Encoder enc;
};

#endif  //      !AUDIOTHREAD_H



/*#ifndef               AUDIOTHREAD_H
# define        AUDIOTHREAD_H

#include <QThread>
#include "IOStreamData.hpp"
#include "AbsIOSound.hpp"
#include "UdpNetwork.h"
#include "DataClientPack.h"
#include <QMessageBox>
//#include <QMutex>

template <typename T>
class   AudioThread : public QThread
{
public:
AudioThread() : {}
//Instanciation explicite!!!!!!
public:
void    setIOSound(AbsIOSound<T> *obj)
{
//this->IOSound = obj;
//data = this->
}
//////////////////////
template <typename A>
void    setBuf(A *dest, A *from)
{
int i;
for (i=0;i<FRAMES_PER_BUFFER;i++)
dest[i] = from[i];
}
/////////////////////////////////////////
void    setData(IOStreamData<T> &Data, IOStreamData<T> &obj)
{
Data.IAvailable = obj.IAvailable;
Data.IMaxFrameIndex = obj.IMaxFrameIndex;
Data.OAvailable = obj.OAvailable;       
this->setBuf<T>(Data.IBuf, obj.IBuf);
}

///////////////////////////////////////////
void    run()
{
//AbsIOSound    *sound = new PaIOSound();
//Encoder               enc(8);
//UdpNetwork            Net;
//sound->recordVoice();

while (1)//sound->getdata().ThreadEnd)
{
/////////////////       this->data->mutex.lock();       
//this->setData(this->DataTmp, sound->data);
if (this->DataTmp.IAvailable)
{
enc.encode(this->DataTmp.IBuf, this->DataTmp.encoded);
DataClientPack  send;
send.dataLenght = FRAMES_PER_BUFFER;
this->setBuf(send.data, this->DataTmp.encoded);
//serialisation
Net.packetSend(reinterpret_cast<char*>(&send));
sound->getdata().IAvailable = false;
}


if (!this->DataTmp.OAvailable)
{
if (socket->waitForReadyRead(10))
{       
int i;
DataClientPack  *rcv;
rcv = reinterpret_cast<DataClientPack*>(Net.packetRcv());
//deserialisation
SAMPLE output[FRAMES_PER_BUFFER];
enc.decode(rcv->data, output);
sound->getdata()->OMaxFrameIndex = rcv->dataLenght / NUM_CHANNELS;
this->setBuf(sound->getdata()->OBuf, output);                           
sound->getdata()->OAvailable = true;
}
}

//usleep(10000);
//      this->data->mutex.unlock();     
}
return ;
}

private:
//AbsIOSound<T> *IOSound;
//Encoder                       enc;
//      IOStreamData<T> &data;
IOStreamData<T> DataTmp;
};

#endif  //      !AUDIOTHREAD_H


/////////////////////////////////////////////

//Pa_Sleep(1000);
if (!this->DataTmp.OAvailable)
{
if (socket->waitForReadyRead(10))
{       
int i;
DataClientPack  *rcv;
rcv = reinterpret_cast<DataClientPack*>(Net.packetRcv());
SAMPLE output[FRAMES_PER_BUFFER];
this->IOSound->getEncode().decode(rcv->data, output);
this->IOSound->getdata()->OMaxFrameIndex = FRAMES_PER_BUFFER / NUM_CHANNELS;
this->setBuf(this->IOSound->getdata()->OBuf, output);                           
this->IOSound->getdata()->OAvailable = true;
}
}*/
