#ifndef		PAOPENSTREAMEXCEPTION_H
# define	PAOPENSTREAMEXEPTION_H

#include <exception>

class	PaOpenStreamException : virtual public std::exception
{
public:
	PaOpenStreamException() throw() {};
	virtual ~PaOpenStreamException() throw() {};
	const char	*what() const throw();
};

#endif	//	!PAOPENSTREAMEXEPTION_H