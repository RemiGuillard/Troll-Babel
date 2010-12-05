#ifndef		DATASERVERPACK_H
#define		DATASERVERPACK_H

struct	DataServerPack
{
	unsigned int	code:16;
	unsigned int	id:16;
	unsigned int	timeStamp:32;
	unsigned int	dataLenght:32;
	char			data[512];
};

#endif	//	!DATASERVERPACK_H