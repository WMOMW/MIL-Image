#pragma once
#ifndef UI_DEMO1_H
#define UI_DEMO1_H

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

class Ui_MIL_Image
{
public:
	QMainWindow *MIL_Image;

	QIcon icon;
	QPalette background;

	QWidget *centralWidget;
	QWidget *gridLayoutWidget;
	QWidget *dock_outputImage_Contents;

	QGridLayout *mainLayout;
	QGroupBox *group_Source;
	QGroupBox *group_Destination;
	QGridLayout *group_Source_Layout;
	QGridLayout *group_Destination_Layout;
	QGridLayout *dockImage_Layout;

	QMenuBar *menuBar;
	QMenu *menu;
	QMenu *menu_Tools;
	QMenu *menu_View;
	QMenu *menu_About;
	QMenu *menu_ImageList;
	QMenu *menu_SVMs;

	QAction *action_OpenImage;
	QAction *action_LoadSVMs;
	QAction *action_SaveImage;
	QAction *action_SaveImageAs;
	QAction *action_Exit;
	QAction *action_AnalyzeImage;
	QAction *action_GetGrayScale;
	QAction *action_GetFeature;
	QAction *action_BinaryImage;
	QAction *action_createClassifier;
	QAction *action_RunSVM;
	QAction *action_about;
	QAction *action_ImageView;
	QAction *action_SVMView;
	QAction *action_outputView;
	QAction *action_outImageView;
	QAction *action_removeallImages;
	QAction *action_ImageList_open;
	QAction *action_ImageList_remove;
	QAction *action_ImageList_copyPath;
	QAction *action_SVMs_remove;
	QAction *action_SVMs_removeAll;
	QAction *action_SVMs_copyPath;

	QDockWidget *dock_SVMList;
	QDockWidget *dock_outputText;
	QDockWidget *dock_outputImage;
	QDockWidget *dock_ImageList;
	QTableWidget *tableWidget_SVMs;
	QTableWidget *tableWidget_Images;
	QTextEdit *text_output;
	QLabel *Image_1;
	QLabel *Image_2;
	QLabel *Image_dockImage;
	QPushButton *to_Right;
	QPushButton *to_Left;

	void setupUi(QMainWindow *Demo1Class)
	{
		if (Demo1Class->objectName().isEmpty())
			Demo1Class->setObjectName(QStringLiteral("Demo1Class"));
		this->MIL_Image = Demo1Class;

		Demo1Class->setMouseTracking(true);

		Demo1Class->setMinimumSize(800, 600);

		//使dock能被插入到两个悬浮窗口中间
		Demo1Class->setDockNestingEnabled(true);

		//实例化
		action_OpenImage = new QAction(Demo1Class);
		action_LoadSVMs = new QAction(Demo1Class);
		action_SaveImage = new QAction(Demo1Class);
		action_SaveImageAs = new QAction(Demo1Class);
		action_Exit = new QAction(Demo1Class);
		action_AnalyzeImage = new QAction(Demo1Class);
		action_GetGrayScale = new QAction(Demo1Class);
		action_GetFeature = new QAction(Demo1Class);
		action_BinaryImage = new QAction(Demo1Class);
		action_createClassifier = new QAction(Demo1Class);
		action_RunSVM = new QAction(Demo1Class);
		action_about = new QAction(Demo1Class);
		menuBar = new QMenuBar(Demo1Class);
		menu = new QMenu(menuBar);
		menu_Tools = new QMenu(menuBar);
		menu_View = new QMenu(menuBar);
		menu_About = new QMenu(menuBar);
		action_ImageView = new QAction(Demo1Class);
		action_SVMView = new QAction(Demo1Class);
		action_outputView = new QAction(Demo1Class);
		action_outImageView = new QAction(Demo1Class);
		action_removeallImages = new QAction(Demo1Class);

		//实例化
		centralWidget = new QWidget(Demo1Class);
		gridLayoutWidget = new QWidget(centralWidget);

		//实例化
		mainLayout = new QGridLayout(centralWidget);
		group_Source = new QGroupBox(gridLayoutWidget);
		group_Destination = new QGroupBox(gridLayoutWidget);
		group_Source_Layout = new QGridLayout(new QWidget(group_Source));
		group_Destination_Layout = new QGridLayout(new QWidget(group_Destination));

		//实例化
		Image_1 = new QLabel(group_Source_Layout->widget());
		Image_2 = new QLabel(group_Destination_Layout->widget());
		to_Right = new QPushButton(gridLayoutWidget);
		to_Left = new QPushButton(gridLayoutWidget);

		//设置图标
		icon.addFile(QStringLiteral(":/Demo1/Demo1.ico"), QSize(), QIcon::Normal, QIcon::Off);
		Demo1Class->setWindowIcon(icon);

		//设置菜单栏
		Demo1Class->setMenuBar(menuBar);
		//设置菜单栏位置及大小
		menuBar->setGeometry(QRect(0, 0, Demo1Class->width(), 23));
		//绑定QMainWindow和QWidegt
		Demo1Class->setCentralWidget(centralWidget);

		//向菜单栏添加内容
		menuBar->addAction(menu->menuAction());
		menuBar->addAction(menu_Tools->menuAction());
		menuBar->addAction(menu_View->menuAction());
		menuBar->addAction(menu_About->menuAction());
		menu->addAction(action_OpenImage);
		menu->addAction(action_LoadSVMs);
		menu->addAction(action_SaveImage);
		menu->addAction(action_SaveImageAs);
		menu->addAction(action_removeallImages);
		menu->addSeparator();
		menu->addAction(action_Exit);
		menu_Tools->addAction(action_AnalyzeImage);
		menu_Tools->addAction(action_GetGrayScale);
		menu_Tools->addAction(action_BinaryImage);
		menu_Tools->addAction(action_GetFeature);
		menu_Tools->addAction(action_createClassifier);
		menu_Tools->addSeparator();
		menu_Tools->addAction(action_RunSVM);
		menu_View->addAction(action_ImageView);
		menu_View->addAction(action_SVMView);
		menu_View->addAction(action_outImageView);
		menu_View->addAction(action_outputView);
		menu_About->addAction(action_about);

		//设置控件属性
		Image_1->setAlignment(Qt::AlignCenter);	//居中显示
		Image_2->setAlignment(Qt::AlignCenter);	//居中显示

		//设置布局
		mainLayout->addWidget(group_Source, 0, 0, 4, 1);
		mainLayout->addWidget(group_Destination, 0, 2, 4, 1);
		mainLayout->addWidget(to_Right, 1, 1);
		mainLayout->addWidget(to_Left, 2, 1);
		mainLayout->setColumnStretch(0, 1);
		mainLayout->setColumnStretch(2, 1);
		mainLayout->setContentsMargins(10, 10, 10, 10);
		group_Source->setLayout(group_Source_Layout);
		group_Source_Layout->addWidget(Image_1, 0, 0, 1, 1);
		group_Source_Layout->setContentsMargins(15, 20, 20, 20);
		group_Destination->setLayout(group_Destination_Layout);
		group_Destination_Layout->addWidget(Image_2, 0, 0, 1, 1);
		group_Destination_Layout->setContentsMargins(15, 20, 20, 20);

		//设置布局
		group_Source->setFixedSize(240, 240);
		group_Destination->setFixedSize(240, 240);
		Image_1->setFixedSize(200, 180);
		Image_2->setFixedSize(200, 180);
		to_Right->setFixedSize(70, 50);
		to_Left->setFixedSize(70, 50);


		//添加背景图片
		/*background.setBrush(QPalette::Background, QBrush(QPixmap("1.jpg")));
		Demo1Class->setPalette(background);*/

		//设置浮动窗口
		setDocks_View();

		//显示控件标签
		setText();

	} // setupUi

	void setText()
	{
		MIL_Image->setWindowTitle(QString::fromLocal8Bit("Demo1"));
		action_OpenImage->setText(QString::fromLocal8Bit("预加载图片"));
		action_LoadSVMs->setText(QString::fromLocal8Bit("加载SVM"));
		action_SaveImage->setText(QString::fromLocal8Bit("保存至源图"));
		action_SaveImageAs->setText(QString::fromLocal8Bit("图像另存为"));
		action_removeallImages->setText(QString::fromLocal8Bit("移除全部图像"));
		action_Exit->setText(QString::fromLocal8Bit("退出"));
		action_AnalyzeImage->setText(QString::fromLocal8Bit("分析图片信息"));
		action_GetGrayScale->setText(QString::fromLocal8Bit("获取灰度图"));
		action_GetFeature->setText(QString::fromLocal8Bit("特征化图像（基于BGR）"));
		action_BinaryImage->setText(QString::fromLocal8Bit("二值化图像"));
		action_createClassifier->setText(QString::fromLocal8Bit("新建分类器"));
		action_RunSVM->setText(QString::fromLocal8Bit("分类测试"));
		action_about->setText(QString::fromLocal8Bit("about"));
		action_ImageList_open->setText(QString::fromLocal8Bit("打开"));
		action_ImageList_remove->setText(QString::fromLocal8Bit("移除"));
		action_ImageList_copyPath->setText(QString::fromLocal8Bit("复制路径"));
		action_SVMs_copyPath->setText(QString::fromLocal8Bit("复制路径"));
		action_SVMs_remove->setText(QString::fromLocal8Bit("移除"));
		action_SVMs_removeAll->setText(QString::fromLocal8Bit("移除全部"));
		menu->setTitle(QString::fromLocal8Bit("文件"));
		menu_Tools->setTitle(QString::fromLocal8Bit("工具"));
		menu_View->setTitle(QString::fromLocal8Bit("视图"));
		menu_About->setTitle(QString::fromLocal8Bit("关于"));
		dock_SVMList->setWindowTitle(QString::fromLocal8Bit("SVM"));
		dock_ImageList->setWindowTitle(QString::fromLocal8Bit("预加载的图片"));
		dock_outputText->setWindowTitle(QString::fromLocal8Bit("输出"));
		action_ImageView->setText(QString::fromLocal8Bit("预加载的图片"));
		action_SVMView->setText(QString::fromLocal8Bit("SVM"));
		action_outputView->setText(QString::fromLocal8Bit("Output"));
		action_outImageView->setText(QString::fromLocal8Bit("数据图"));
		to_Right->setText(QString::fromLocal8Bit(">>"));
		to_Left->setText(QString::fromLocal8Bit("<<"));
		group_Source->setTitle(QString::fromLocal8Bit("源图像"));
		group_Destination->setTitle(QString::fromLocal8Bit("目的图像"));
		dock_outputImage->setWindowTitle(QString::fromLocal8Bit("数据图"));
	}

	void setDocks_View() {
		setDock_SVMList_View();
		setDock_ImageList_View();
		setDock_outputImage_View();
		setDock_outputText_View();

		//布局
		MIL_Image->addDockWidget(Qt::RightDockWidgetArea, dock_ImageList);
		MIL_Image->addDockWidget(Qt::RightDockWidgetArea, dock_SVMList);
		MIL_Image->tabifyDockWidget(dock_ImageList, dock_SVMList);
		MIL_Image->addDockWidget(Qt::RightDockWidgetArea, dock_outputImage);
		MIL_Image->addDockWidget(Qt::BottomDockWidgetArea, dock_outputText);
		dock_ImageList->raise();
	}

	void setDock_SVMList_View() {
		//实例化
		menu_SVMs = new QMenu(MIL_Image);
		action_SVMs_remove = new QAction(MIL_Image);
		action_SVMs_removeAll = new QAction(MIL_Image);
		action_SVMs_copyPath = new QAction(MIL_Image);

		//向菜单栏添加内容
		menu_SVMs->addAction(action_SVMs_remove);
		menu_SVMs->addAction(action_SVMs_copyPath);
		menu_SVMs->addAction(action_SVMs_removeAll);

		//实例化
		dock_SVMList = new QDockWidget(centralWidget);
		tableWidget_SVMs = new QTableWidget(dock_SVMList);

		//设置停靠窗口属性
		dock_SVMList->setFeatures(QDockWidget::AllDockWidgetFeatures);
		dock_SVMList->setAllowedAreas(Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
		dock_SVMList->setMinimumSize(200, 180);
		dock_SVMList->setWidget(tableWidget_SVMs);

		//设置控件属性
		tableWidget_SVMs->setColumnCount(2);
		tableWidget_SVMs->setHorizontalHeaderLabels({ QString::fromLocal8Bit("SVM"),QString::fromLocal8Bit("路径") });
		tableWidget_SVMs->verticalHeader()->setDefaultSectionSize(20);
		tableWidget_SVMs->horizontalHeader()->setFixedHeight(20);
		tableWidget_SVMs->verticalHeader()->setHidden(true);
		tableWidget_SVMs->horizontalHeader()->setStretchLastSection(true);
		tableWidget_SVMs->setSelectionBehavior(QAbstractItemView::SelectRows);
		tableWidget_SVMs->setEditTriggers(QAbstractItemView::NoEditTriggers);
		tableWidget_SVMs->setSelectionMode(QAbstractItemView::SingleSelection);
		tableWidget_SVMs->setContextMenuPolicy(Qt::CustomContextMenu);
		tableWidget_SVMs->setMouseTracking(true);
	}

	void setDock_outputText_View() {
		//实例化
		dock_outputText = new QDockWidget(centralWidget);
		text_output = new QTextEdit(dock_outputText);

		//设置停靠窗口属性
		dock_outputText->setFeatures(QDockWidget::AllDockWidgetFeatures);
		dock_outputText->setAllowedAreas(Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
		dock_outputText->setMinimumSize(200, 180);
		dock_outputText->setWidget(text_output);

		//设置控件属性
		text_output->setReadOnly(true);
	}

	void setDock_outputImage_View() {
		//实例化
		dock_outputImage = new QDockWidget(centralWidget);
		dock_outputImage_Contents = new QWidget(dock_outputImage);
		dockImage_Layout = new QGridLayout(dock_outputImage_Contents);
		Image_dockImage = new QLabel(dockImage_Layout->widget());

		//设置停靠窗口属性
		dock_outputImage->setFeatures(QDockWidget::AllDockWidgetFeatures);
		dock_outputImage->setAllowedAreas(Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
		dock_outputImage->setMinimumSize(200, 180);
		dock_outputImage->setWidget(dock_outputImage_Contents);

		//设置控件属性
		Image_dockImage->setFixedSize(150, 150);

		//设置布局
		dockImage_Layout->addWidget(Image_dockImage);
		dockImage_Layout->setContentsMargins(10, 10, 10, 10);
	}

	void setDock_ImageList_View() {
		//实例化
		menu_ImageList = new QMenu(MIL_Image);
		action_ImageList_open = new QAction(MIL_Image);
		action_ImageList_remove = new QAction(MIL_Image);
		action_ImageList_copyPath = new QAction(MIL_Image);

		//向菜单栏添加内容
		menu_ImageList->addAction(action_ImageList_open);
		menu_ImageList->addAction(action_ImageList_remove);
		menu_ImageList->addAction(action_ImageList_copyPath);

		//实例化
		dock_ImageList = new QDockWidget(centralWidget);
		tableWidget_Images = new QTableWidget(dock_ImageList);

		//设置停靠窗口属性
		dock_ImageList->setFeatures(QDockWidget::AllDockWidgetFeatures);
		dock_ImageList->setAllowedAreas(Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
		dock_ImageList->setMinimumSize(200, 180);
		dock_ImageList->setWidget(tableWidget_Images);
		//dock_ImageList->setMouseTracking(true);
		//dock_ImageList->setWidget();

		//设置控件属性
		tableWidget_Images->setColumnCount(2);
		tableWidget_Images->setHorizontalHeaderLabels({ QString::fromLocal8Bit("文件名"),QString::fromLocal8Bit("路径") });
		tableWidget_Images->verticalHeader()->setDefaultSectionSize(20);
		tableWidget_Images->horizontalHeader()->setFixedHeight(20);
		tableWidget_Images->verticalHeader()->setHidden(true);
		tableWidget_Images->horizontalHeader()->setStretchLastSection(true);
		tableWidget_Images->setSelectionBehavior(QAbstractItemView::SelectRows);
		tableWidget_Images->setEditTriggers(QAbstractItemView::NoEditTriggers);
		tableWidget_Images->setSelectionMode(QAbstractItemView::SingleSelection);
		tableWidget_Images->setContextMenuPolicy(Qt::CustomContextMenu);
		tableWidget_Images->setMouseTracking(true);
	}
};

namespace Ui {
	class MIL_Image : public Ui_MIL_Image {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMO1_H
