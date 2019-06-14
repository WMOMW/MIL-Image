#include "stdafx.h"
#include "MILImage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MILImage w;
	w.show();
	return a.exec();
}
