#ifndef UDPNETWORK
# define UDPNETWORK

#include <QUdpSocket>
#include <QString>
#include "ABSNetwork.h"

class		UdpNetwork : public ABSNetwork
{
public:
	UdpNetwork();
	~UdpNetwork();

private:
	UdpNetwork(const UdpNetwork &);
	UdpNetwork&			operator=(const UdpNetwork &);

public:
	void					createSocket();
	void					socketConnection(const QString &, quint16);
	char*					packetRcv();
	void					packetSend(const char *);
	void					disconnect();

	QAbstractSocket&	getSocket();

private:
	QUdpSocket			_sock;
	QString				_ip;
	quint16				_port;
};

#endif // !  UDPNETWORK