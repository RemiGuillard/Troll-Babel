#include "PaIniException.h"

const char	*PaIniException::what() const throw()
{
	return "une erreur est survenue, veuillez relancer l'application";
}