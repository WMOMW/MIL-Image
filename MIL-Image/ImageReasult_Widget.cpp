#include "stdafx.h"
#include "ImageReasult_Widget.h"

ImageReasult_Widget::ImageReasult_Widget(QWidget *parent, QString Title, QString RealClass, QLinkedList<Result_Info> info)
	:QMainWindow(parent)
{
	ui.setupUi(this);
	ui.setTitle(Title);
	ui.setRealClass(RealClass);
	ui.setInfo(info);

	ui.Label_RealClass->setVisible(false);
	ui.LineEdit_RealClass->setVisible(false);

	connect(ui.button_Last, SIGNAL(clicked()), this, SLOT(to_Last()));
	connect(ui.button_Next, SIGNAL(clicked()), this, SLOT(to_Next()));


	connect(ui.button_Next, SIGNAL(clicked()), this, SLOT(ttt()));
}

void ImageReasult_Widget::wheelEvent(QWheelEvent *event) {
	if (event->delta() > 0)
	{
		to_Last();
	}
	else
	{
		to_Next();
	}
}

void ImageReasult_Widget::keyPressEvent(QKeyEvent *event) {
	switch (event->key())
	{
	case Qt::Key_Left:
	case Qt::Key_Up:
		to_Last();
		break;
	case Qt::Key_Right:
	case Qt::Key_Down:
		to_Next();
		break;
	}
}

void ImageReasult_Widget::setTitle(QString Title) {
	ui.setTitle(Title);
}

void ImageReasult_Widget::setRealClass(QString RealClass) {
	ui.setRealClass(RealClass);
}

void ImageReasult_Widget::setInfo(QLinkedList<Result_Info> Info) {
	ui.setInfo(Info);
}

void ImageReasult_Widget::ttt() {

}

void ImageReasult_Widget::to_Last() {
	if (!ui.info.isEmpty())
	{
		if (ui.temp == ui.info.begin())
		{
			ui.temp = ui.info.end() - 1;
		}
		else
		{
			--ui.temp;
		}
		ui.path = (*ui.temp).get_Image_path();
		ui.LineEdit_ImageName->setText(ui.path);
		ui.LineEdit_outputClass->setText((*ui.temp).get_outputClass().join(','));
		if (ui.img.open_Image(ui.path))
		{
			ui.Q_img = cvMatToQImage(ui.img.get_image());
			ui.Image->setPixmap((QPixmap(QPixmap::fromImage(ui.Q_img)).scaled(ui.Image->size(), Qt::KeepAspectRatio)));
		}
		else
		{
			ui.Image->setText(QString::fromLocal8Bit("无法打开图像"));
		}
	}
	this->setFocus();
}

void ImageReasult_Widget::to_Next() {
	if (!ui.info.isEmpty())
	{
		if ((++ui.temp) == ui.info.end())
		{
			ui.temp = ui.info.begin();
		}
		ui.path = (*ui.temp).get_Image_path();
		ui.LineEdit_ImageName->setText(ui.path);
		ui.LineEdit_outputClass->setText((*ui.temp).get_outputClass().join(','));
		if (ui.img.open_Image(ui.path))
		{
			ui.Q_img = cvMatToQImage(ui.img.get_image());
			ui.Image->setPixmap((QPixmap(QPixmap::fromImage(ui.Q_img)).scaled(ui.Image->size(), Qt::KeepAspectRatio)));
		}
		else
		{
			ui.Image->setText(QString::fromLocal8Bit("无法打开图像"));
		}
	}
	this->setFocus();
}