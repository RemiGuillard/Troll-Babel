#ifndef BABEL_H
#define BABEL_H

#include <QtGui/QMainWindow>
#include "DataServerPack.h"
#include "ui_babel.h"
#include "UdpNetwork.h"
#include "TcpNetwork.h"
#include "AbsIOSound.hpp"
#include "PaIOSound.h"
#include "contact.h"

class Babel : public QMainWindow
{
	Q_OBJECT

typedef	void	(Babel::*answer)(DataServerPack*);

public:
	Babel(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Babel();

public slots:
	void			changerPage();
	void			connectToServer();
	void			login();
	//void			appeler(int ip);
	void			appeler();
	void			endACall();
	void			dataReceived();
	void			disconnectedFromServer();
	void			updateContactList();

	/// ENVOI DE COMMANDE AU SERVER///
	void			serverIdentify();
	void			serverRegister();
	void			disconnectFromServer();
	void			serverAnswer();
	void			addAContact();
	void			delAContact();
	void			acceptInvit();
	void			refuseInvit();
	void			contactList();
	void			getContactStatus();
	void			callSomeone();
	void			cancelCall();
	void			acceptCall();
	void			refuseCall();
	void			hangUp();


	///SLOTS REPONSE SERVEUR///
	void			identified(DataServerPack*);
	void			registered(DataServerPack*);
	void			newContactStatus(DataServerPack*);
	void			errorAnswer(DataServerPack*);
	void			notifInvitRecv(DataServerPack*);
	void			notifInvitAccept(DataServerPack*);
	void			notifContactDeleted(DataServerPack*);
	void			notifCallIncomming(DataServerPack*);
	void			notifCallAccepted(DataServerPack*);
	void			notifCallRefused(DataServerPack*);
	void			notifCallEnded(DataServerPack*);

signals:
	void			valueChanged(int);

private:
	Ui::BabelClass							ui;
	TcpNetwork								_server;
	UdpNetwork								_client;
	AbsIOSound<SAMPLE>*						_IOSound;
	unsigned short							counter;
//	QList<QMap<QString, QString> >			_contactList;
	QMap<unsigned short, unsigned short>	_cmdList;
	QMap<unsigned short, answer>			_serverCmd;
	contact									_contact;
};

#endif // BABEL_H
