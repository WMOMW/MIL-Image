#pragma once
#ifndef UI_IMAGEREASULT_WIDGET_H
#define UI_IMAGEREASULT_WIDGET_H

#include <qstring.h>
#include <qlinkedlist.h>
#include <QtCore\qvariant.h>
#include <QtWidgets\qaction.h>
#include <QtWidgets\qapplication.h>
#include <QtWidgets\qbuttongroup.h>
#include <QtWidgets\qheaderview.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qmainwindow.h>
#include <QtWidgets\qmenu.h>
#include <QtWidgets\qmenubar.h>
#include <QtWidgets\qwidget.h>
#include <QtWidgets\qdockwidget.h>
#include <QtWidgets\qgridlayout.h>
#include <QtWidgets\qtreeview.h>
#include <QtWidgets\qlistwidget.h>
#include <QtWidgets\qtextedit.h>
#include <QtWidgets\qgroupbox.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qtablewidget.h>
#include <QtWidgets\qlineedit.h>
#include "Result_Info.h"
#include "namedImage.h"
#include "cvMatToQImage.h"

QT_BEGIN_NAMESPACE

class ui_ImageReasult_WidgetClass
{
public:
	ui_ImageReasult_WidgetClass(QString Title = "TempWigget", QString RealClass = "NULL", QLinkedList<Result_Info> info = QLinkedList<Result_Info>()) {
		this->Title = Title;
		this->info = info;
	}

	QMainWindow *ImageReasult_WidgetClass;

	QWidget *centralWidget;
	QWidget *gridLayoutWidget;

	QGridLayout *mainLayout;
	QGridLayout *ImageLayout;
	QSpacerItem *horizontalSpacer_1;
	QSpacerItem *horizontalSpacer_2;

	QLineEdit *LineEdit_ImageName;
	QLineEdit *LineEdit_RealClass;
	QLineEdit *LineEdit_outputClass;
	QLabel *Label_ImageName;
	QLabel *Label_RealClass;
	QLabel *Label_outputClass;
	QLabel *Image;
	QPushButton *button_Last;
	QPushButton *button_Next;

	void setupUi(QMainWindow *ImageReasult_WidgetClass)
	{
		if (ImageReasult_WidgetClass->objectName().isEmpty())
			ImageReasult_WidgetClass->setObjectName(QStringLiteral("ImageReasult_WidgetClass"));
		this->ImageReasult_WidgetClass = ImageReasult_WidgetClass;
		ImageReasult_WidgetClass->setMouseTracking(true);
		ImageReasult_WidgetClass->setFocusPolicy(Qt::StrongFocus);

		//固定窗口大小
		ImageReasult_WidgetClass->setFixedSize(430, 310);
		//ImageReasult_WidgetClass->setMinimumSize(800, 600);

		//实例化
		centralWidget = new QWidget(ImageReasult_WidgetClass);
		gridLayoutWidget = new QWidget(centralWidget);

		//绑定QMainWindow和QWidegt
		ImageReasult_WidgetClass->setCentralWidget(centralWidget);

		//实例化
		mainLayout = new QGridLayout(centralWidget);
		horizontalSpacer_1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

		//实例化
		LineEdit_ImageName = new QLineEdit(gridLayoutWidget);
		LineEdit_RealClass = new QLineEdit(gridLayoutWidget);
		LineEdit_outputClass = new QLineEdit(gridLayoutWidget);
		Label_ImageName = new QLabel(gridLayoutWidget);
		Label_RealClass = new QLabel(gridLayoutWidget);
		Label_outputClass = new QLabel(gridLayoutWidget);
		Image = new QLabel(gridLayoutWidget);
		button_Last = new QPushButton(gridLayoutWidget);
		button_Next = new QPushButton(gridLayoutWidget);

		//设置控件属性
		Image->setFixedSize(200, 180);
		Image->setAlignment(Qt::AlignCenter);	//居中显示
		Label_ImageName->setFixedSize(100, 20);
		Label_outputClass->setFixedSize(100, 20);
		Label_RealClass->setFixedSize(100, 20);
		LineEdit_ImageName->setReadOnly(true);
		LineEdit_outputClass->setReadOnly(true);
		LineEdit_RealClass->setReadOnly(true);
		button_Last->setFixedSize(100, 23);
		button_Last->setFocusPolicy(Qt::NoFocus);
		button_Next->setFixedSize(100, 23);
		button_Next->setFocusPolicy(Qt::NoFocus);

		//设置布局
		mainLayout->setAlignment(Qt::AlignCenter);
		mainLayout->setColumnStretch(0, 1);
		mainLayout->setColumnStretch(3, 1);
		mainLayout->addWidget(Label_ImageName, 0, 0, 1, 1);
		mainLayout->addWidget(Label_RealClass, 1, 0, 1, 1);
		mainLayout->addWidget(Label_outputClass, 2, 0, 1, 1);
		mainLayout->addWidget(LineEdit_ImageName, 0, 1, 1, 3);
		mainLayout->addWidget(LineEdit_RealClass, 1, 1, 1, 3);
		mainLayout->addWidget(LineEdit_outputClass, 2, 1, 1, 3);
		mainLayout->addItem(horizontalSpacer_1, 3, 0, 1, 1);
		mainLayout->addItem(horizontalSpacer_2, 3, 3, 1, 1);
		mainLayout->addWidget(Image, 3, 1, 1, 2);
		mainLayout->addWidget(button_Last, 4, 2, 1, 1);
		mainLayout->addWidget(button_Next, 4, 3, 1, 1);

		setInfo(info);

		setText();
	} // setupUi

	void setInfo(QLinkedList<Result_Info> info)
	{
		this->info = info;
		temp = this->info.begin();
		if (this->info.isEmpty())
		{
			LineEdit_ImageName->setText(QString::fromLocal8Bit("NULL"));
			LineEdit_outputClass->setText(QString::fromLocal8Bit("NULL"));
			LineEdit_RealClass->setText(QString::fromLocal8Bit("NULL"));
			Image->setText(QString::fromLocal8Bit("无可显示图片"));
		}
		else
		{
			path = (*temp).get_Image_path();
			LineEdit_ImageName->setText(path);
			LineEdit_outputClass->setText((*temp).get_outputClass().join(','));
			if (img.open_Image(path))
			{
				Q_img = cvMatToQImage(img.get_image());
				Image->setPixmap((QPixmap(QPixmap::fromImage(Q_img)).scaled(Image->size(), Qt::KeepAspectRatio)));
			}
			else
			{
				Image->setText(QString::fromLocal8Bit("无法打开图像"));
			}
		}
	}

	void setTitle(QString title)
	{
		this->Title = title;
		ImageReasult_WidgetClass->setWindowTitle(title);
	}

	void setRealClass(QString RealClass)
	{
		this->RealClass = RealClass;
		LineEdit_RealClass->setText(RealClass.toLocal8Bit());
	}

	void setText()
	{
		ImageReasult_WidgetClass->setWindowTitle(Title);
		Label_ImageName->setText(QString::fromLocal8Bit("图片路径："));
		Label_RealClass->setText(QString::fromLocal8Bit("实际类："));
		Label_outputClass->setText(QString::fromLocal8Bit("输出类："));
		button_Last->setText(QString::fromLocal8Bit("<<"));
		button_Next->setText(QString::fromLocal8Bit(">>"));
		LineEdit_RealClass->setText(RealClass.toLocal8Bit());
	}

	QString Title;
	QString RealClass;
	QLinkedList<Result_Info> info;
	QLinkedList<Result_Info>::iterator temp;

	QString path;
	namedImage img;
	QImage Q_img;
};

namespace Ui {
	class ImageReasult_WidgetClass : public ui_ImageReasult_WidgetClass {
	public:
		ImageReasult_WidgetClass(QString Title = "TempWigget", QString RealClass = "NULL", QLinkedList<Result_Info> info = QLinkedList<Result_Info>())
			:ui_ImageReasult_WidgetClass(Title, RealClass, info) {}
	};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEREASULT_WIDGET_H
