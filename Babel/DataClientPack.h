#ifndef		DATACLIENTPACK_H
# define	DATACLIENTPACK_H

struct	DataClientPack
{
	char	code;
	int		bitRate;
	int		sampleRate;
	char	quality;
	int		dataLenght;
	char	data[256];
}; 

#endif	//	!DATACLIENTPACK_H