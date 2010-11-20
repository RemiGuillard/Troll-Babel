#ifndef		AUDIOTHREAD_H
# define	AUDIOTHREAD_H

#include <QThread>
#include "AbsIOSound.h"
#include "BNetwork.h"

template <typename T>
class	AudioThread : public QThread
{
public:
	void	run();
private:
	// remplacer &data par &AbsIOSound
	IOStreamData<T>	&Data;
	IOStreamData<T>	DataTmp;
	BNetwork		&Net;
};

#endif	//	!AUDIOTHREAD_H