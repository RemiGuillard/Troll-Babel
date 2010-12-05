#include <QMessageBox>
#include <QString>
#include <QInputDialog>
#include "babel.h"
#include "PaIOSound.h"
#include "AbsIOSound.hpp"

Babel::Babel(QWidget *parent, Qt::WFlags flags)
: QMainWindow(parent, flags)
{
	this->ui.setupUi(this);
	this->_server.createSocket();
	this->_client.createSocket();
	this->counter = 1;

	this->_serverCmd.insert(1001, &Babel::registered);
	this->_serverCmd.insert(1002, &Babel::identified);
	this->_serverCmd.insert(1010, &Babel::notifInvitRecv);
	this->_serverCmd.insert(1011, &Babel::notifInvitAccept);
	this->_serverCmd.insert(1012, &Babel::notifContactDeleted);
	this->_serverCmd.insert(1013, &Babel::newContactStatus);
	this->_serverCmd.insert(1020, &Babel::notifCallIncomming);
	this->_serverCmd.insert(1021, &Babel::notifCallAccepted);
	this->_serverCmd.insert(1022, &Babel::notifCallRefused);
	this->_serverCmd.insert(1023, &Babel::notifCallEnded);
	this->_serverCmd.insert(1111, &Babel::errorAnswer);
	
	try
	{
		this->_IOSound = new PaIOSound(&_client);
	}
	catch (std::exception* e)
	{
		QMessageBox::information(this, "Information", e->what());
		delete e;
	}

	/////// CONNECTION ///////
	connect(&(this->_server.getSocket()), SIGNAL(connected()), this, SLOT(changerPage()));
	connect(this->ui.connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
	connect(&(this->_server.getSocket()), SIGNAL(disconnected()), this, SLOT(disconnectedFromServer()));
	connect(this->ui.actionLogout, SIGNAL(triggered()), this, SLOT(disconnectFromServer()));
	
	/////// CHANGEMENT DE PAGE ///////
	connect(this, SIGNAL(valueChanged(int)), this->ui.stackWindows, SLOT(setCurrentIndex(int)));

	/////// IDENTIFICATION SERVER ///////
	connect(this->ui.loginButton, SIGNAL(clicked()), this, SLOT(serverIdentify()));
	connect(this->ui.registerButton, SIGNAL(clicked()), this, SLOT(serverRegister()));

	/////// RECEPTION INFOS SERVER ///////
	connect(&(this->_server.getSocket()), SIGNAL(readyRead()), this, SLOT(serverAnswer()));

	/////// APPEL ///////
	connect(this->ui.testButton, SIGNAL(clicked()), this, SLOT(callMyself()));
	connect(this->ui.callButton, SIGNAL(clicked()), this, SLOT(callSomeone()));
	connect(this->ui.dirCallButton, SIGNAL(clicked()), this, SLOT(appeler()));
	connect(this->ui.endCallButton, SIGNAL(clicked()), this, SLOT(hangUp()));

	/////// CONTACT ///////
	connect(this->ui.addContactButton, SIGNAL(clicked()), this, SLOT(addAContact()));
	connect(this->ui.delContactButton, SIGNAL(clicked()), this, SLOT(delAContact()));

	////// NOTIF CONTACT ///////

}

Babel::~Babel()
{
  this->_IOSound->StopPlayRecord();
  delete this->_IOSound;
}

void            Babel::connectToServer()

{
	quint16 port = 0;
	QString server;

	server = ui.serverField->displayText();
	port = ui.portField->displayText().toUShort();

	this->_server.socketConnection(server, port);
}

void            Babel::changerPage()
{
	emit valueChanged(1);
}

void            Babel::login()
{
	std::string     login = ui.loginField->text().toStdString();
	std::string     pwd = ui.passwordField->text().toStdString();

	QString toto;
	toto = "Login: ";
	toto += ui.loginField->text();
	toto += "\nPwd:  ";
	toto += ui.passwordField->text();
	QMessageBox::information(this, "Information", toto);

	emit valueChanged(2);
}

void            Babel::appeler()
{
	try
	{
		this->_client.socketConnection(this->ui.IpClientLine->text(), this->ui.PortClientLine->text().toUShort());
		this->_IOSound->playVoice();
		emit valueChanged(3);
	}
	catch (std::exception* e)
	{
		QMessageBox::information(this, "Information", e->what());
		delete e;
		this->_IOSound->StopPlayRecord();
	}
}

void            Babel::endACall()
{
	try
	{
		this->_IOSound->StopPlayRecord();
		_client.disconnect();
		emit valueChanged(2);
	}
	catch (std::exception* e)
	{
		QMessageBox::information(this, "Information", e->what());
		delete e;
	}
}
 
void            Babel::dataReceived()
{
	DataClientPack  *rcv;
	rcv = reinterpret_cast<DataClientPack*>(this->_client.packetRcv());
	SAMPLE output[FRAMES_PER_BUFFER];

	/*QString	t(0);
	QMessageBox::information(this, "Information", t.setNum(rcv->dataLenght));*/
	this->_IOSound->getEncode().decode(rcv->data, output);
	this->_IOSound->getdata()->OMaxFrameIndex = FRAMES_PER_BUFFER;
	this->_IOSound->getdata()->OBuf->writeBlock(output, FRAMES_PER_BUFFER);
	delete rcv;
}

void            Babel::disconnectedFromServer()
{
	this->_client.disconnect();
	QMessageBox::information(this, "Server information", "You've been disconnected form the server");
	emit valueChanged(0);
}

void				Babel::updateContactList()
{
	this->ui.FriendList->clear();
	std::map<std::string, std::string> list = this->_contact.getContactList();
	std::map<std::string, std::string>::iterator it = list.begin();
	std::map<std::string, std::string>::iterator end = list.end();

	while (it != end)
	{
		QString		name;
		name = it->first.c_str();
		name += "\t\t";
		name += it->second.c_str();
		this->ui.FriendList->addItem(name);
		++it;
	}
}

void				Babel::serverIdentify()
{
	std::string		user = ui.loginField->text().toStdString();
	std::string		pwd = ui.passwordField->text().toStdString();
	int				userLen = user.length();
	int				pwdLen = pwd.length();

	if (userLen > 32) userLen = 32;
	if (pwdLen > 64) pwdLen = 64;

	DataServerPack	*data = new DataServerPack;
	data->code = 2;
	data->id = this->counter++;
	data->timeStamp = 0;
	data->dataLenght = sizeof(data->data);
	memset(data->data, 0, 512);
	memcpy(data->data, user.c_str(), userLen);
	memcpy(&(data->data[32]), pwd.c_str(), pwdLen);
	this->_cmdList.insert(data->id, data->code);
	this->_server.packetSend(reinterpret_cast<char *>(data));
	delete data;

	/*QString	toto(0);
	QMessageBox::information(NULL, "test", toto.setNum(sizeof(DataClientPack)));*/
}

void				Babel::serverRegister()
{
	std::string		user = ui.RLoginField->text().toStdString();
	std::string		pwd = ui.RPwdField->text().toStdString();
	int				userLen = user.length();
	int				pwdLen = pwd.length();

	if (userLen > 32) userLen = 32;
	if (pwdLen > 64) pwdLen = 64;

	DataServerPack	*data = new DataServerPack;
	data->code = 1;
	data->id = this->counter++;
	data->timeStamp = 0;
	data->dataLenght = sizeof(data->data);
	memset(data->data, 0, 512);
	memcpy(data->data, user.c_str(), userLen);
	memcpy(&(data->data[32]), pwd.c_str(), pwdLen);
	this->_cmdList.insert(data->id, data->code);
	this->_server.packetSend(reinterpret_cast<char *>(data));
	delete data;

}

void				Babel::disconnectFromServer()
{
	if (this->_server.getSocketStatus())
	{
		DataServerPack	*data = new DataServerPack;

		data->code = 3;
		data->id = this->counter++;
		data->timeStamp = 0;
		data->dataLenght = sizeof(data->data);
		memset(data->data, 0, 512);
		this->_server.packetSend(reinterpret_cast<char *>(data));
//		this->_server.disconnect();
		delete data;
		emit valueChanged(1);
	}
}

void				Babel::addAContact()
{
	QString	name = QInputDialog::getText(this, "Ajouter un ami", "Inserez le login du contact");

	if (!name.isEmpty())
	{
		DataServerPack	*data = new DataServerPack;
		data->code = 10;
		data->id = this->counter++;
		data->timeStamp = 0;
		data->dataLenght = sizeof(data->data);
		memset(data->data, 0, 512);
		if (name.length() < 32)
			memcpy(data->data, name.toStdString().c_str(), name.length());
		else
			memcpy(data->data, name.toStdString().c_str(), 32);
		this->_cmdList.insert(data->id, data->code);
		this->_server.packetSend(reinterpret_cast<char *>(data));
		delete data;
	}
}

void				Babel::delAContact()
{
	QString	name = QInputDialog::getText(this, "Supprimer un ami", "Inserez le login du contact");

	if (!name.isEmpty())
	{
		DataServerPack	*data = new DataServerPack;
		data->code = 12;
		data->id = this->counter++;
		data->timeStamp = 0;
		data->dataLenght = sizeof(data->data);
		memset(data->data, 0, 512);
		if (name.length() < 32)
			memcpy(data->data, name.toStdString().c_str(), name.length());
		else
			memcpy(data->data, name.toStdString().c_str(), 32);
		this->_cmdList.insert(data->id, data->code);
		this->_server.packetSend(reinterpret_cast<char *>(data));
		delete data;
	}
}

void			Babel::acceptInvit() {}
void			Babel::refuseInvit() {}

void			Babel::contactList()
{
	DataServerPack	*data = new DataServerPack;
	data->code = 13;
	data->id = this->counter++;
	data->timeStamp = 0;
	data->dataLenght = sizeof(data->data);
	memset(data->data, 0, 512);
	this->_cmdList.insert(data->id, data->code);
	this->_server.packetSend(reinterpret_cast<char *>(data));
	delete data;
}

void			Babel::getContactStatus()
{
}

void			Babel::callSomeone()
{
	QString user = this->ui.FriendList->currentItem()->text();
	user.truncate(user.indexOf("\t"));

	DataServerPack	*data = new DataServerPack;
	data->code = 20;
	data->id = this->counter++;
	data->timeStamp = 0;
	data->dataLenght = sizeof(data->data);
	memset(data->data, 0, 512);
	memcpy(data->data, user.toStdString().c_str(), user.length());
	this->_cmdList.insert(data->id, data->code);
	this->_server.packetSend(reinterpret_cast<char *>(data));
	delete data;
}

void			Babel::cancelCall() {}
void			Babel::acceptCall() {}
void			Babel::refuseCall() {}

void			Babel::hangUp()
{
	DataServerPack	*data = new DataServerPack;
	data->code = 24;
	data->id = this->counter++;
	data->timeStamp = 0;
	data->dataLenght = sizeof(data->data);
	memset(data->data, 0, 512);
	this->_cmdList.insert(data->id, data->code);
	this->_server.packetSend(reinterpret_cast<char *>(data));
	delete data;
	this->endACall();
}

void				Babel::serverAnswer()
{
	while (this->_server.getSocket().bytesAvailable() != 0)
	{
		DataServerPack	*data = reinterpret_cast<DataServerPack*>(this->_server.packetRcv());

//	QMap<int, unsigned short>::iterator	cmd = this->_cmdList.find(data->id);
//	if (this->_cmdList.find(data->id) != this->_cmdList.end())
//	(this->*(this->_serverCmd.find(this->_cmdList.find(data->id).value()).value()))(data);
//  else

		if (this->_serverCmd.find(data->code) != this->_serverCmd.end())
			(this->*(*(this->_serverCmd.find(data->code))))(data);
	}

}

void						Babel::identified(DataServerPack* data)
{
	emit valueChanged(2);
	this->contactList();
}

void						Babel::registered(DataServerPack* data)
{
	this->ui.loginField->setText(this->ui.RLoginField->text());
	this->ui.passwordField->setText(this->ui.RPwdField->text());
	QMessageBox::information(this, "Registered", "you are Registered");
	this->serverIdentify();
}

void						Babel::newContactStatus(DataServerPack* data)
{
	this->_contact.setContactStatus(data->data, &(data->data[32]));
	this->updateContactList();
}

void						Babel::errorAnswer(DataServerPack* data)
{
	int	value = (int)*(data->data);

	if (value == 11)
		QMessageBox::information(this, "Register", "Nom invalide");
	else if (value == 12)
		QMessageBox::information(this, "Connection", "Pass invalide");
	else if (value == 13)
		QMessageBox::information(this, "Register", "Nom deja use");
	else if (value == 14)
		QMessageBox::information(this, "Connection", "Nom inexistant");
	else if (value == 15)
		QMessageBox::information(this, "Connection", "Cet utilisateur est hors-ligne");
	else if (value == 16)
		QMessageBox::information(this, "Contact", "Cet utilisateur n'est pas votre ami");
	else if (value == 17)
		QMessageBox::information(this, "Contact", "Cet utilisateur est déjà connecté");
	else if (value == 20)
		QMessageBox::information(this, "Contact", "Contact Déja Ajouté");
}

void						Babel::notifInvitRecv(DataServerPack* data)
{
	QString					newContact;
	newContact = data->data;
	newContact += " souhaiterait vous ajouter à sa liste d'amis. Voulez vous accepter ?";
	if (QMessageBox::question(this, "Demande d'ajout d'un contact", newContact, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
		data->code = 11;
	else
		data->code = 15;
	data->id = this->counter++;
	data->timeStamp = 0;
	data->dataLenght = sizeof(data->data);
	this->_server.packetSend(reinterpret_cast<char *>(data));

	if (data->code == 11)
	{
		data->code = 14;
		data->id = this->counter++;
		data->timeStamp = 0;
		data->dataLenght = sizeof(data->data);
		this->_cmdList.insert(data->id, data->code);
		this->_server.packetSend(reinterpret_cast<char *>(data));
	}
}

void						Babel::notifInvitAccept(DataServerPack* data)
{
	data->code = 14;
	data->id = this->counter++;
	data->timeStamp = 0;
	data->dataLenght = sizeof(data->data);
	this->_cmdList.insert(data->id, data->code);
	this->_server.packetSend(reinterpret_cast<char *>(data));
}

void						Babel::notifContactDeleted(DataServerPack* data)
{
	this->_contact.delContact(data->data);
	this->updateContactList();
}

void						Babel::notifCallIncomming(DataServerPack* data)
{
	int	ip = (int)*(&(data->data[32]));
	QString		username = data->data;
	username += " est en train d'essayer de vous joindre. Voulez vous accepter ?";
	if (QMessageBox::question(this, "Incoming Call", username, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
		data->code = 22;
	else
		data->code = 23;
	data->id = this->counter++;
	data->timeStamp = 0;
	data->dataLenght = sizeof(data->data);
	this->_server.packetSend(reinterpret_cast<char *>(data));

	if (data->code == 22)
	{
		QString		address(ip);

		emit valueChanged(3);
		this->_client.socketConnection(address, 36693);
		this->_IOSound->playVoice();
	}
}

void						Babel::notifCallAccepted(DataServerPack* data)
{
	int	ip = (int)*(&(data->data[32]));
	QString		address(ip);

	emit valueChanged(3);
	this->_client.socketConnection(address, 36693);
	this->_IOSound->playVoice();
}

void						Babel::notifCallRefused(DataServerPack*) {}

void						Babel::notifCallEnded(DataServerPack*)
{
	this->endACall();
}

void						Babel::callMyself()
{
	//emit valueChanged(3);
	this->_client.socketConnection(QString(2130706433), 36693);
	this->_IOSound->playVoice();
	QMessageBox::information(NULL, "Test", "Teste de votre micro");
	this->endACall();
}