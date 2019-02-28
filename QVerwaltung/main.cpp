#include "QVerwaltung.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCoreApplication::setOrganizationName("BJ");
	QCoreApplication::setOrganizationDomain("https://github.com/seppy87/QVerwaltung");
	QCoreApplication::setApplicationName("QVerwaltung");
	QCoreApplication::setApplicationVersion("0.0.1 Build 02/28/2019");
	QVerwaltung w;
	w.show();
	return a.exec();
}
