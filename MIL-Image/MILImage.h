#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MILImage.h"

class MILImage : public QMainWindow
{
	Q_OBJECT

public:
	MILImage(QWidget *parent = Q_NULLPTR);

private:
	Ui::MILImageClass ui;
};
