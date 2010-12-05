#ifndef		PAINIEXEPTION_H
# define	PAINIEXEPTION_H

#include <exception>

class	PaIniException : virtual public std::exception
{
public:
	PaIniException() throw() {};
	virtual ~PaIniException() throw() {};
	const char	*what() const throw();
};

#endif	//	!PAINIEXEPTION_H