#include "RGraphicsLibTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RGraphicsLibTest w;
	w.show();
	return a.exec();
}
