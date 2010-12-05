#include "PaStopStreamException.h"

const char	*PaStopStreamException::what() const throw()
{
	return "une erreur est survenue, impossible d'arreter la conversation.";
}