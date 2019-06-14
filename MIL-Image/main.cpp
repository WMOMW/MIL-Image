#include "stdafx.h"
#include "MIL_Image.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MIL_Image w;
	w.show();
	return a.exec();
}
