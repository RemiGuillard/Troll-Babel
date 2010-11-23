#include "babel.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Babel w;
	w.show();

	return a.exec();
}
