#ifndef		PASTOPSTREAMEXEPTION_H
# define	PASTOPSTREAMEXEPTION_H

#include <exception>

class	PaStopStreamException : virtual public std::exception
{
public:
	PaStopStreamException() throw() {};
	virtual ~PaStopStreamException() throw() {};
	const char	*what() const throw();
};

#endif	//	!PASTOPSTREAMEXEPTION_H