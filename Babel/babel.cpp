#include <QMessageBox>
#include "babel.h"

Babel::Babel(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	connect(ui.connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
	connect(this, SIGNAL(valueChanged(int)), ui.stackWindows, SLOT(setCurrentIndex(int)));

	_server.createSocket();
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
		//QMessageBox::critical(NULL, "Connection Error", "Error: Unable to connect to the specified server with these parameters");
}

void		Babel::changerPage()
{
	emit valueChanged(1);
}