//
// AudioThread.hpp for AudioThread.hpp in /partage/babel/Babel
//
// Made by laurent pouyet
// Login   <pouyet_l@epitech.net>
//
// Started on  Sun Dec  5 11:12:01 2010 laurent pouyet
// Last update Sun Dec  5 11:23:10 2010 laurent pouyet
//

#ifndef         AUDIOTHREAD_H
# define        AUDIOTHREAD_H

#include <QThread>
#include <QMessageBox>
#include "IOStreamData.hpp"
#include "UdpNetwork.h"
#include "DataClientPack.h"
#include "Encoder.h"

template <typename T>
class   AudioThread : public QThread
{
public:
  AudioThread(IOStreamData<T> *Data, UdpNetwork *Net) : data(Data), net(Net) {}
public:
  template <typename A>
  void    setBuf(A *dest, A *from)
  {
    int i;
    for (i = 0 ; i < FRAMES_PER_BUFFER ; ++i)
      dest[i] = from[i];
  }

  void    run()
  {
    while (this->data->ThreadEnd)
      {
		T	tmp[FRAMES_PER_BUFFER];

		data->IBuf->readBlock(tmp, FRAMES_PER_BUFFER);
		this->enc.encode(tmp, this->data->encoded);
		DataClientPack  send;
		send.dataLenght = FRAMES_PER_BUFFER;
		this->setBuf(send.data, this->data->encoded);
		this->net->packetSend(reinterpret_cast<char*>(&send));
      }
    return ;
  }
private:
  IOStreamData<T> *data;
  UdpNetwork      *net;
  Encoder enc;
};

#endif  //      !AUDIOTHREAD_H
