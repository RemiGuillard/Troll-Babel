#ifndef		AUDIOTHREAD_H
# define	AUDIOTHREAD_H

#include <QThread>
#include "IOStreamData.hpp"
#include "AbsIOSound.hpp"
#include "UdpNetwork.h"

template <typename T>
class	AudioThread : public QThread
{
public:
	void	run();
private:
	// remplacer &data par &AbsIOSound
	AbsIOSound<T>	*IOSound;
	IOStreamData<T>	DataTmp;
	UdpNetwork		&Net;
};

#endif	//	!AUDIOTHREAD_H