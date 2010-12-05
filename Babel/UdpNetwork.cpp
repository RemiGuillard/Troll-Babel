#include <QUdpSocket>
#include <QMessageBox>
#include "UdpNetwork.h"
#include "DataClientPack.h" 

UdpNetwork::UdpNetwork() { this->setSocketStatus(false); }

UdpNetwork::~UdpNetwork() { }

UdpNetwork::UdpNetwork(const UdpNetwork &cpy) { *this = cpy; }

UdpNetwork&				UdpNetwork::operator=(const UdpNetwork &cpy) { return *this; }

void					UdpNetwork::createSocket() { }

void					UdpNetwork::socketConnection(const QString & hostName, quint16 port)
{
	_sock.bind(port);
	this->_ip = hostName;
	this->_port = port;
	this->setSocketStatus(true);
}

char*					UdpNetwork::packetRcv()
{
	char	*data = new char[sizeof(DataClientPack)];
	
	this->_sock.readDatagram(data, sizeof(DataClientPack));
	return data;
}

void					UdpNetwork::packetSend(const char *data)
{
	this->_sock.writeDatagram(data, sizeof(DataClientPack), QHostAddress(this->_ip), this->_port);
}

void					UdpNetwork::disconnect()
{
	_sock.close();
	this->setSocketStatus(false);
}

QAbstractSocket&	UdpNetwork::getSocket()
{
	return _sock;
}