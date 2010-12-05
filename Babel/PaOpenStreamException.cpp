#include "PaOpenStreamException.h"

const char	*PaOpenStreamException::what() const throw()
{
	return "verifiez que votre micro et ecouteurs sont branches";
}