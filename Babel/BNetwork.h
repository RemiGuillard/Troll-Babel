#ifndef BNETWORK
# define BNETWORK

#include <QString>
#include <QAbstractSocket>

class		BNetwork
{
public:
	BNetwork();

	virtual void		createSocket(QAbstractSocket::SocketType) = 0;
	virtual void		socketConnection(const QString &, quint16) = 0;
	virtual void		packetRcv() = 0;
	virtual void		packetSend() = 0;
	virtual void		disconnect() = 0;

	const bool&			getSocketStatus() const;
	void				setSocketStatus(const bool&);
	
private:
	bool				_sockState;
};

#endif // !BNETWORK