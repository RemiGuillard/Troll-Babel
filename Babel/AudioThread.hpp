#ifndef		AUDIOTHREAD_H
# define	AUDIOTHREAD_H

#include <QThread>
#include "IOStreamData.hpp"
#include "AbsIOSound.hpp"
#include "UdpNetwork.h"
#include "DataClientPack.h"
#include <QMessageBox>

template <typename T>
class	AudioThread : public QThread
{
public:
	AudioThread(UdpNetwork &net) : Net(net) {}
	//Instanciation explicite!!!!!!
public:
	void	setIOSound(AbsIOSound<T> *obj)
	{
		this->IOSound = obj;
	}
	//////////////////////
	template <typename A>
	void	setBuf(A *dest, A *from)
	{
		int i;
		for (i=0;from[i];i++)
			dest[i] = from[i];
	}
/////////////////////////////////////////
	void	setData(IOStreamData<T> &Data, IOStreamData<T> *obj)
	{
		Data.IAvailable = obj->IAvailable;
		Data.IMaxFrameIndex = obj->IMaxFrameIndex;
		Data.OAvailable = obj->IAvailable;	
		this->setBuf<T>(Data.IBuf, obj->IBuf);
	}

///////////////////////////////////////////
	void	run()
	{
		QUdpSocket	*socket = dynamic_cast<QUdpSocket *>(&this->Net.getSocket());
		while (1)//this->IOSound->getdata()->ThreadEnd)
		{
			this->setData(this->DataTmp, this->IOSound->getdata());
			if (this->DataTmp.IAvailable)
			{
				this->IOSound->getEncode().encode(this->DataTmp.IBuf, this->DataTmp.encoded);
				DataClientPack	send;
				send.dataLenght = FRAMES_PER_BUFFER;
				this->setBuf(send.data, this->DataTmp.encoded);
				Net.packetSend(reinterpret_cast<char*>(&send));
				this->IOSound->getdata()->IAvailable = false;
			}
							//QMessageBox::information(NULL, "test", "test");
/*			if (!this->DataTmp.OAvailable)
			{
				if (socket->waitForReadyRead(10))
				{	
					int i;
					DataClientPack	*rcv;
					rcv = reinterpret_cast<DataClientPack*>(Net.packetRcv());
					SAMPLE output[FRAMES_PER_BUFFER];
					this->IOSound->getEncode().decode(rcv->data, output);
					this->IOSound->getdata()->OMaxFrameIndex = FRAMES_PER_BUFFER / NUM_CHANNELS;
					this->setBuf(this->IOSound->getdata()->OBuf, output);				
					this->IOSound->getdata()->OAvailable = true;
				}
			}*/
	}
		return ;
	}
private:
	AbsIOSound<T>	*IOSound;
	IOStreamData<T>	DataTmp;
	UdpNetwork		&Net;
};

#endif	//	!AUDIOTHREAD_H