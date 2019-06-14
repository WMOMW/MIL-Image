#pragma once
#ifndef UI_SVM_TRAINER_H
#define UI_SVM_TRAINER_H

#include <qstring.h>
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

QT_BEGIN_NAMESPACE

class ui_SVM_TrainerClass
{
public:
	QMainWindow *SVM_TrainerClass;

	QWidget *centralWidget;

	QGridLayout *group_bagsView_Layout;
	QGridLayout *group_NbagsView_Layout;

	QMenu *menu_bagsTable;
	QMenu *menu_NbagsTable;

	QAction *action_bagsView_open;
	QAction *action_bagsView_remove;
	QAction *action_bagsView_removeAll;
	QAction *action_bagsView_copyPath;
	QAction *action_NbagsView_open;
	QAction *action_NbagsView_remove;
	QAction *action_NbagsView_removeAll;
	QAction *action_NbagsView_copyPath;

	QGroupBox *group_bagsView;
	QGroupBox *group_NbagsView;

	QTableWidget *tableWidget_bags;
	QTableWidget *tableWidget_Nbags;

	QLabel *Image_bag;
	QLabel *Image_Nbag;

	QPushButton *add_bags;
	QPushButton *add_Nbags;
	QPushButton *training_and_save;

	void setupUi(QMainWindow *SVM_TrainerClass)
	{
		if (SVM_TrainerClass->objectName().isEmpty())
			SVM_TrainerClass->setObjectName(QStringLiteral("SVM_TrainerClass"));
		this->SVM_TrainerClass = SVM_TrainerClass;

		SVM_TrainerClass->setFixedSize(580, 500);

		//实例化
		centralWidget = new QWidget(SVM_TrainerClass);

		//实例化
		menu_bagsTable = new QMenu(SVM_TrainerClass);
		menu_NbagsTable = new QMenu(SVM_TrainerClass);
		action_bagsView_open = new QAction(SVM_TrainerClass);
		action_bagsView_remove = new QAction(SVM_TrainerClass);
		action_bagsView_removeAll = new QAction(SVM_TrainerClass);
		action_bagsView_copyPath = new QAction(SVM_TrainerClass);
		action_NbagsView_open = new QAction(SVM_TrainerClass);
		action_NbagsView_remove = new QAction(SVM_TrainerClass);
		action_NbagsView_removeAll = new QAction(SVM_TrainerClass);
		action_NbagsView_copyPath = new QAction(SVM_TrainerClass);

		//实例化
		group_bagsView = new QGroupBox(centralWidget);
		group_NbagsView = new QGroupBox(centralWidget);
		group_bagsView_Layout = new QGridLayout(new QWidget(group_bagsView));
		group_NbagsView_Layout = new QGridLayout(new QWidget(group_NbagsView));

		//实例化
		tableWidget_bags = new QTableWidget(centralWidget);
		tableWidget_Nbags = new QTableWidget(centralWidget);
		Image_bag = new QLabel(group_bagsView_Layout->widget());
		Image_Nbag = new QLabel(group_NbagsView_Layout->widget());
		add_bags = new QPushButton(centralWidget);
		add_Nbags = new QPushButton(centralWidget);
		training_and_save = new QPushButton(centralWidget);

		//绑定SVM_TrainerClass和QWidegt
		SVM_TrainerClass->setCentralWidget(centralWidget);

		//向菜单中添加内容
		menu_bagsTable->addAction(action_bagsView_open);
		menu_bagsTable->addAction(action_bagsView_remove);
		menu_bagsTable->addAction(action_bagsView_removeAll);
		menu_bagsTable->addAction(action_bagsView_copyPath);
		menu_NbagsTable->addAction(action_NbagsView_open);
		menu_NbagsTable->addAction(action_NbagsView_remove);
		menu_NbagsTable->addAction(action_NbagsView_removeAll);
		menu_NbagsTable->addAction(action_NbagsView_copyPath);

		//设置控件属性
		tableWidget_bags->setMouseTracking(true);
		tableWidget_bags->setColumnCount(2);
		tableWidget_bags->setHorizontalHeaderLabels({ QString::fromLocal8Bit("文件名"),QString::fromLocal8Bit("路径") });
		tableWidget_bags->verticalHeader()->setDefaultSectionSize(20);
		tableWidget_bags->horizontalHeader()->setFixedHeight(20);
		tableWidget_bags->verticalHeader()->setHidden(true);
		tableWidget_bags->horizontalHeader()->setStretchLastSection(true);
		tableWidget_bags->setSelectionBehavior(QAbstractItemView::SelectRows);
		tableWidget_bags->setEditTriggers(QAbstractItemView::NoEditTriggers);
		tableWidget_bags->setSelectionMode(QAbstractItemView::SingleSelection);
		tableWidget_bags->setContextMenuPolicy(Qt::CustomContextMenu);
		tableWidget_Nbags->setMouseTracking(true);
		tableWidget_Nbags->setColumnCount(2);
		tableWidget_Nbags->setHorizontalHeaderLabels({ QString::fromLocal8Bit("文件名"),QString::fromLocal8Bit("路径") });
		tableWidget_Nbags->verticalHeader()->setDefaultSectionSize(20);
		tableWidget_Nbags->horizontalHeader()->setFixedHeight(20);
		tableWidget_Nbags->verticalHeader()->setHidden(true);
		tableWidget_Nbags->horizontalHeader()->setStretchLastSection(true);
		tableWidget_Nbags->setSelectionBehavior(QAbstractItemView::SelectRows);
		tableWidget_Nbags->setEditTriggers(QAbstractItemView::NoEditTriggers);
		tableWidget_Nbags->setSelectionMode(QAbstractItemView::SingleSelection);
		tableWidget_Nbags->setContextMenuPolicy(Qt::CustomContextMenu);

		//设置控件属性
		Image_bag->setFixedSize(160, 80);
		Image_bag->setAlignment(Qt::AlignCenter);	//居中显示
		Image_Nbag->setFixedSize(160, 80);
		Image_Nbag->setAlignment(Qt::AlignCenter);	//居中显示

		//设置布局
		group_bagsView->setLayout(group_bagsView_Layout);
		group_bagsView_Layout->addWidget(Image_bag, 0, 0, 1, 1);
		group_bagsView_Layout->setContentsMargins(0, 0, 0, 0);
		group_NbagsView->setLayout(group_NbagsView_Layout);
		group_NbagsView_Layout->addWidget(Image_Nbag, 0, 0, 1, 1);
		group_NbagsView_Layout->setContentsMargins(0, 0, 0, 0);

		//设置布局
		group_bagsView->setGeometry(QRect(30, 30, 200, 130));
		group_NbagsView->setGeometry(QRect(30, 210, 200, 130));
		tableWidget_bags->setGeometry(QRect(280, 30, 250, 130));
		tableWidget_Nbags->setGeometry(QRect(280, 210, 250, 130));
		add_bags->setGeometry(QRect(440, 170, 110, 25));
		add_Nbags->setGeometry(QRect(440, 350, 110, 25));
		training_and_save->setGeometry(QRect(390, 430, 160, 30));

		//显示控件标签
		setText();

	} // setupUi

	void setText()
	{
		SVM_TrainerClass->setWindowTitle(QString::fromLocal8Bit("训练新分类器"));
		group_bagsView->setTitle(QString::fromLocal8Bit("预览正包"));
		group_NbagsView->setTitle(QString::fromLocal8Bit("预览反包"));
		add_bags->setText(QString::fromLocal8Bit("添加"));
		add_Nbags->setText(QString::fromLocal8Bit("添加"));
		training_and_save->setText(QString::fromLocal8Bit("训练并保存"));
		action_bagsView_open->setText(QString::fromLocal8Bit("打开"));
		action_bagsView_remove->setText(QString::fromLocal8Bit("移除"));
		action_bagsView_removeAll->setText(QString::fromLocal8Bit("移除全部"));
		action_bagsView_copyPath->setText(QString::fromLocal8Bit("复制路径"));
		action_NbagsView_open->setText(QString::fromLocal8Bit("打开"));
		action_NbagsView_remove->setText(QString::fromLocal8Bit("移除"));
		action_NbagsView_removeAll->setText(QString::fromLocal8Bit("移除全部"));
		action_NbagsView_copyPath->setText(QString::fromLocal8Bit("复制路径"));
	}
};

namespace Ui {
	class SVM_TrainerClass : public ui_SVM_TrainerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVM_TRAINER_H
