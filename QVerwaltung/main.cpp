#include "QVerwaltung.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QVerwaltung w;
	w.show();
	return a.exec();
}
