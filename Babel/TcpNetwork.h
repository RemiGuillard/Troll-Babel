#ifndef TCPNETWORK
# define TCPNETWORK

#include <QTcpSocket>
#include <QString>
#include "ABSNetwork.h"

class		TcpNetwork : public ABSNetwork
{
public:
	TcpNetwork();
	~TcpNetwork();

private:
	TcpNetwork(const TcpNetwork &);
	TcpNetwork&			operator=(const TcpNetwork &);

public:
	void				createSocket();
	void				socketConnection(const QString &, quint16);
	char*				packetRcv();
	void				packetSend(const char *);
	void				disconnect();

	QAbstractSocket*	getSocket() const;

private:
	QTcpSocket*			_sock;
	QString				_ip;
	quint16				_port;
};

#endif // !  TCPNETWORK