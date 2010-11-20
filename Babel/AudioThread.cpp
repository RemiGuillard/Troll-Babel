#include "AudioThread.h"
//#include "Encoder.h"

template <typename T>
void	AudioThread<T>::run()
{
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
			this->Net.packetRcv();
			//decode pack.data
			//transfert de pack.data => data.buf
			this->Data.OAvailable = true;
		}
	}
	return;
}