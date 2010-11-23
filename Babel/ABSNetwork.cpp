#include "ABSNetwork.h"

ABSNetwork::ABSNetwork() {}

const bool&			ABSNetwork::getSocketStatus() const { return this->_sockState; }

void				ABSNetwork::setSocketStatus(const bool& newState) { this->_sockState = newState; }