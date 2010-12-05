#ifndef		DATACLIENTPACK_H
# define	DATACLIENTPACK_H

struct	DataClientPack
{
	char			code:8;
	unsigned int	bitRate:32;
	unsigned int	sampleRate:32;
	unsigned int	quality:8;
	unsigned int	dataLenght:32;;
	char			data[256];
};

#endif	//	!DATACLIENTPACK_H
