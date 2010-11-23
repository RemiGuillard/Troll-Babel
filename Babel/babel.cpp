#include <QMessageBox>
#include "babel.h"
#include <String>

Babel::Babel(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	_server.createSocket();
	_client.createSocket();

	connect(this->ui.connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
	connect(this, SIGNAL(valueChanged(int)), this->ui.stackWindows, SLOT(setCurrentIndex(int)));
	connect(this->_server.getSocket(), SIGNAL(connected()), this, SLOT(changerPage()));
	connect(this->_server.getSocket(), SIGNAL(disconnected()), this, SLOT(disconnetedFromServer()));
	connect(this->ui.loginButton, SIGNAL(clicked()), this, SLOT(login()));

	/*Appel*/
	connect(this->ui.callButton, SIGNAL(clicked()), this, SLOT(appeler()));

	connect(this->ui.endCallButton, SIGNAL(clicked()), this, SLOT(endACall()));
	connect(this->_client.getSocket(), SIGNAL(readyRead()), this, SLOT(dataReceived()));

	/*Test d'envoi de donnée en Udp*/
	connect(this->ui.sendDataButton, SIGNAL(clicked()), this, SLOT(sendData()));
}

Babel::~Babel()
{

}

void		Babel::connectToServer()
{
	quint16	port = 0;
	QString	server;

	server = ui.serverField->displayText();
	port = ui.portField->displayText().toUShort();

	this->_server.socketConnection(server, port);
}

void		Babel::changerPage()
{
	emit valueChanged(1);
}

void		Babel::login()
{
	std::string	login = ui.loginField->text().toStdString();	
	std::string	pwd = ui.passwordField->text().toStdString();	
	
	QString toto;
	toto = "Login: ";
	toto += ui.loginField->text();
	toto += "\nPwd:  ";
	toto += ui.passwordField->text();
	QMessageBox::information(this, "Information", toto);

	emit valueChanged(2);
}

void		Babel::appeler()
{
	QUdpSocket* socket = reinterpret_cast<QUdpSocket *>(this->_client.getSocket());

	if (socket->bind(QHostAddress(this->ui.IpClientLine->text()), this->ui.PortClientLine->text().toUShort(), QUdpSocket::ShareAddress) == false)
		QMessageBox::information(this, "Information", "Bind failed");
	emit valueChanged(3);
	//Integrer ICI la partie sound Recording/Playing => QThread + PA
}

void		Babel::endACall()
{
	_client.disconnect();
	emit valueChanged(2);
}

void		Babel::sendData()
{
	char*	buffer = "Coucou les copains";

	reinterpret_cast<QUdpSocket*>(this->_client.getSocket())->writeDatagram(buffer, 19, QHostAddress(this->ui.IpClientLine->text()), this->ui.PortClientLine->text().toUShort());
}

void		Babel::dataReceived()
{
	char	buffer[512];
	buffer[reinterpret_cast<QUdpSocket*>(this->_client.getSocket())->readDatagram(buffer, 512)] = '\0';
	QString	toto = buffer;
	QMessageBox::information(this, "Data Received", toto);
}

void		Babel::disconnectedFromServer()
{
	QMessageBox::information(this, "Server information", "You've been disconnected form the server");
}