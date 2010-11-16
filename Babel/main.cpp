#include "babel.h"
#include <QtGui/QApplication>

#include "QNetwork.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Babel w;
//	QNetwork	net;
//	quint16		port = 20701;
	
//	net.socketConnection("127.0.0.1", port);
	w.show();

//	if (net.getSocketStatus())
//		net.disconnect();
	return a.exec();
}
