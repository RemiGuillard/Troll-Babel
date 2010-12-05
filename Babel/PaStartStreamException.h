#ifndef		PASTARTSTREAMEXEPTION_H
# define	PASTARTSTREAMEXEPTION_H

#include <exception>

class	PaStartStreamException : virtual public std::exception
{
public:
	PaStartStreamException() throw() {};
	virtual ~PaStartStreamException() throw() {};
	const char	*what() const throw();
};

#endif	//	!PASTARTSTREAMEXEPTION_H