#ifndef		AUDIOTHREAD_H
# define	AUDIOTHREAD_H

#include <QThread>
#include "AbsIOSound.hpp"
#include "ABSNetwork.h"

//template <typename T>
class	AudioThread : public QThread
{
public:
	void	run();
private:
	// remplacer &data par &AbsIOSound
	//IOStreamData<T>	&Data;
	//IOStreamData<SAMPLE>	DataTmp;
	ABSNetwork		&Net;
};

#endif	//	!AUDIOTHREAD_H