#include "PaCloseException.h"

const char	*PaCloseException::what() const throw()
{
	return "une erreur est survenue, impossible de terminer l'application correctement";
}