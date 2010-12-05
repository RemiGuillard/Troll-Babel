#ifndef		PACLOSEEXEPTION_H
# define	PACLOSEEXEPTION_H

#include <exception>

class	PaCloseException : virtual public std::exception
{
public:
	PaCloseException() throw() {};
	virtual ~PaCloseException() throw() {};
	const char	*what() const throw();
};

#endif	//	!PACLOSEEXEPTION_H