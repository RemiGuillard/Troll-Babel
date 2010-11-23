#include <QUdpSocket>
#include <QMessageBox>
#include "UdpNetwork.h"

UdpNetwork::UdpNetwork() { this->setSocketStatus(false); }

UdpNetwork::~UdpNetwork() { delete this->_sock; }

UdpNetwork::UdpNetwork(const UdpNetwork &cpy) { *this = cpy; }

UdpNetwork&		UdpNetwork::operator=(const UdpNetwork &cpy) { return *this; }

void		UdpNetwork::createSocket()
{
	_sock = new QUdpSocket;
}

void		UdpNetwork::socketConnection(const QString & hostName, quint16 port)
{
	_sock->bind(QHostAddress(hostName), port);
	this->_ip = hostName;
	this->_port = port;
}

char*		UdpNetwork::packetRcv()
{
	char	*data = new char[398];

	this->_sock->readDatagram(data, 398);
	return data;
}

void		UdpNetwork::packetSend(const char *data)
{
	this->_sock->writeDatagram(data, 398, QHostAddress(this->_ip), this->_port);
}

void		UdpNetwork::disconnect()
{
	_sock->close();
	this->setSocketStatus(false);
}

QAbstractSocket*		UdpNetwork::getSocket() const
{
	return _sock;
}