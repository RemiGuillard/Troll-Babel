#include "AudioThread.hpp"
//#include "Encoder.h"

template <typename T>
void	AudioThread<T>::run()
{
	QUdpSocket	*socket = reinterpret_cast<QUdpSocket>(this->Net->getSocket());
	while (this->Data.ThreadEnd)
	{
		this->DataTmp = this->Data;
		if (this->DataTmp.IAvailable)
		{
			//encode data
			//transfert de data.buf => pack.data
			this->Net.packetSend();
			this->Data.IAvailable = false;
		}
		if (!this->DataTmp.OAvailable)
		{
			if (socket->waitForReadyRead(10))
			{	
				data = this->Net.packetRcv();
				this->Data.OAvailable = true;
			}
			//decode pack.data
			//transfert de pack.data => data.buf
		}
	}
	return 0;
}