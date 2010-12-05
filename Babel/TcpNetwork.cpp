#include <QTcpSocket>
#include <QMessageBox>
#include "TcpNetwork.h"
#include "DataServerPack.h"

TcpNetwork::TcpNetwork() { this->setSocketStatus(false); }

TcpNetwork::~TcpNetwork() { }

TcpNetwork::TcpNetwork(const TcpNetwork &cpy) { *this = cpy; }

TcpNetwork&				TcpNetwork::operator=(const TcpNetwork &cpy) { return *this; }

void					TcpNetwork::createSocket() { }

void					TcpNetwork::socketConnection(const QString & hostName, quint16 port)
{
	_sock.connectToHost(hostName, port);
	this->_ip = hostName;
	this->_port = port;
	this->setSocketStatus(true);
}

char*					TcpNetwork::packetRcv()
{
	char	*data = new char[sizeof(DataServerPack)];

	_sock.read(data, sizeof(DataServerPack));
	return data;
}

void					TcpNetwork::packetSend(const char *data)
{
	this->_sock.write(data, sizeof(DataServerPack));
}

void					TcpNetwork::disconnect()
{
	_sock.close();
	this->setSocketStatus(false);
	QMessageBox::information(NULL, "Connection Exit", "You're now disconnected");
}

const QAbstractSocket&	TcpNetwork::getSocket() const
{
	return _sock;
}