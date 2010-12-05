#ifndef BABEL_H
#define BABEL_H

#include <QtGui/QMainWindow>
#include "ui_babel.h"
#include "UdpNetwork.h"
#include "TcpNetwork.h"
#include "AbsIOSound.hpp"
#include "PaIOSound.h"

class Babel : public QMainWindow
{
	Q_OBJECT

public:
	Babel(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Babel();

public slots:
	void			changerPage();
	void			connectToServer();
	void			login();
	void			appeler();
	void			endACall();
	void			dataReceived();
//	void			disconnectedFromServer();
//	void			sendData();
//	void			bindMyPort();

signals:
	void			valueChanged(int);

private:
	Ui::BabelClass	ui;
	TcpNetwork		_server;
	UdpNetwork		_client;
	AbsIOSound<SAMPLE>* _IOSound;
};

#endif // BABEL_H
