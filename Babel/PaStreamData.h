#ifndef		PASTREAMDATA_H
# define	PASTREAMDATA_H

#include <iostream>

class	PaStreamData
{
public:
	PaStreamData();
	void	*getIBuff();
	void	*getOBuff();
	bool	getIAvailable();
	bool	getOAvailable();
	bool	setIAvailable();
	bool	setOAvailable();
private:
	bool	IAvailable;
	bool	OAvailable;
	void	*IBuff;
	void	*OBuff;
};

#endif	//	!PASTREAMDATA_H