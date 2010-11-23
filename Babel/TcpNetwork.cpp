#include <QTcpSocket>
#include <QMessageBox>
#include "TcpNetwork.h"

TcpNetwork::TcpNetwork() { this->setSocketStatus(false); }

TcpNetwork::~TcpNetwork() { delete this->_sock; }

TcpNetwork::TcpNetwork(const TcpNetwork &cpy) { *this = cpy; }

TcpNetwork&		TcpNetwork::operator=(const TcpNetwork &cpy) { return *this; }

void		TcpNetwork::createSocket()
{
	_sock = new QTcpSocket;
}

void		TcpNetwork::socketConnection(const QString & hostName, quint16 port)
{
	_sock->connectToHost(hostName, port);
	this->_ip = hostName;
	this->_port = port;
}

char*		TcpNetwork::packetRcv()
{
	char	*data = new char[652];

	_sock->read(data, 652);
	return data;
}

void		TcpNetwork::packetSend(const char *data)
{
	this->_sock->write(data, 652);
}

void		TcpNetwork::disconnect()
{
	_sock->close();
	this->setSocketStatus(false);
	QMessageBox::information(NULL, "Connection Exit", "You're now disconnected");
}

QAbstractSocket*		TcpNetwork::getSocket() const
{
	return _sock;
}