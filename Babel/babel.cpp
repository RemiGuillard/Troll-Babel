#include <QMessageBox>
#include "babel.h"
#include <String>

Babel::Babel(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	_server.createSocket();
	_client.createSocket(QAbstractSocket::UdpSocket);

	connect(this->ui.connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
	connect(this, SIGNAL(valueChanged(int)), this->ui.stackWindows, SLOT(setCurrentIndex(int)));
	connect(this->_server.getSocket(), SIGNAL(connected()), this, SLOT(changerPage()));
	connect(this->ui.loginButton, SIGNAL(clicked()), this, SLOT(login()));

	/*Appel*/
	connect(this->ui.callButton, SIGNAL(clicked()), this, SLOT(appeler()));
	connect(this->_client.getSocket(), SIGNAL(connected()), this, SLOT(startCalling()));
	connect(this->ui.bindButton, SIGNAL(clicked()), this, SLOT(startBinding()));
	connect(this->ui.stateButton, SIGNAL(clicked()), this, SLOT(getStatusSocket()));
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
	if (this->_server.getSocketStatus())
		emit valueChanged(1);
//	else
//		QMessageBox::critical(NULL, "Connection Error", "Error: Unable to connect to the specified server with these parameters");
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
	this->_client.getSocket()->connectToHost(this->ui.IpClientLine->text(), this->ui.PortClientLine->text().toUShort());
}

void		Babel::startCalling()
{
	QMessageBox::information(this, "Information", "You're Now Connected to the Client");
	emit valueChanged(3);
}

void		Babel::startBinding()
{
	dynamic_cast<QUdpSocket*>(this->_client.getSocket())->bind(QHostAddress(this->ui.IpClientLine->text()), this->ui.PortClientLine->text().toUShort());
}

void		Babel::getStatusSocket()
{
	QString	status(0);
	QMessageBox::information(this, "Information", status.setNum(_client.getSocketStatus()));
}