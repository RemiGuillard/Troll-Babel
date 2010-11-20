#ifndef		DATASERVERPACK_H
#define		DATASERVERPACK_H

struct	DataServerPack
{
	char	code[2];
	char	id[2];
	int		timeStamp;
	int		dataLenght;
	char	reserved[16];
	char	data[512];
};

#endif	//	!DATASERVERPACK_H