#pragma once

#include "ui_ImageReasult_Widget.h"
#include "stdafx.h"

//#include "ui_Demo1.h"

class ImageReasult_Widget : public QMainWindow
{
	Q_OBJECT

public:
	ImageReasult_Widget(QWidget *parent = Q_NULLPTR, QString Title = "TempWigget", QString RealClass = "NULL", QLinkedList<Result_Info> info = QLinkedList<Result_Info>());

	void setTitle(QString);
	void setRealClass(QString);
	void setInfo(QLinkedList<Result_Info>);

protected:
	void wheelEvent(QWheelEvent*);
	void keyPressEvent(QKeyEvent *event);

private slots:
	void ttt();
	void to_Last();
	void to_Next();

private:
	Ui::ImageReasult_WidgetClass ui;
};
