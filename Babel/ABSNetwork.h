#ifndef ABSNETWORK
# define ABSNETWORK

#include <QString>
#include <QAbstractSocket>

class		ABSNetwork
{
public:
	ABSNetwork();

	virtual void		createSocket() = 0;
	virtual void		socketConnection(const QString &, quint16) = 0;
	virtual char*		packetRcv() = 0;
	virtual void		packetSend(const char *) = 0;
	virtual void		disconnect() = 0;

	const bool&			getSocketStatus() const;
	void				setSocketStatus(const bool&);
	
private:
	bool				_sockState;
};

#endif // !ABSNETWORK