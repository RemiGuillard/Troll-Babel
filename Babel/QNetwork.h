#ifndef QNETWORK
# define QNETWORK

#include <QAbstractSocket>
#include <QString>
#include "BNetwork.h"

class		QNetwork : public BNetwork
{
public:
	QNetwork();
	~QNetwork();

private:
	QNetwork(const QNetwork &);
	QNetwork&			operator=(const QNetwork &);

public:
	void				createSocket(QAbstractSocket::SocketType = QAbstractSocket::TcpSocket);
	void				socketConnection(const QString &, quint16);
	void				packetRcv();
	void				packetSend();
	void				disconnect();

	QAbstractSocket*	getSocket() const;

private:
	QAbstractSocket*	_sock;
};

#endif // !QNETWORK