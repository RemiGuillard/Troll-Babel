#include "PaStartStreamException.h"

const char	*PaStartStreamException::what() const throw()
{
	return "une erreur est survenue, veuillez verifier vos ecouteurs";
}