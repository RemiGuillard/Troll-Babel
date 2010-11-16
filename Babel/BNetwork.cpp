#include "BNetwork.h"

BNetwork::BNetwork() : _sockState(false)
{
}

const bool&		BNetwork::getSocketStatus() const
{
	return _sockState;
}

void			BNetwork::setSocketStatus(const bool& state)
{
	_sockState = state;
}