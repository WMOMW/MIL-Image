#pragma once

#include "ui_SVM_Trainer.h"
#include "stdafx.h"

class SVM_Trainer : public QMainWindow
{
	Q_OBJECT
public:
	SVM_Trainer(QWidget *parent = Q_NULLPTR);

private slots:
	void ttt();	//测试函数

	void open_Bags();	//打开正包示例
	void open_NBags();	//打开反包示例
	void save_SVM();

	void show_bagsView_menu(QPoint);	//显示正包table右键菜单
	void open_Image_from_bagsView_byAction();	//以右键菜单方式打开正包table中的图像
	void remove_Image_from_bagsView_byAction();	//以右键菜单方式移除正包table中的图像
	void remove_allImage_from_bagsView_byAction();	//以右键菜单方式移除正包table中的全部图像
	void copy_ImagePath_from_bagsView_byAction();	//以右键菜单方式复制正包table中的图片路径
	void show_NbagsView_menu(QPoint);	//显示反包table右键菜单
	void open_Image_from_NbagsView_byAction();	//以右键菜单方式打开反包table中的图像
	void remove_Image_from_NbagsView_byAction();	//以右键菜单方式移除反包table中的图像
	void remove_allImage_from_NbagsView_byAction();	//以右键菜单方式移除反包table中的全部图像
	void copy_ImagePath_from_NbagsView_byAction();	//以右键菜单方式复制反包table中的图片路径

	void open_Image_from_bagsView(QTableWidgetItem*);	//用双击的方式从正包中打开图片
	void open_Image_from_NbagsView(QTableWidgetItem*);	//用双击的方式从反包中打开图片
	void remove_Image_from_bagsView(QTableWidgetItem*);	//移除“预加载的图片”中的项
	void remove_Image_from_NbagsView(QTableWidgetItem*);	//移除“预加载的图片”中的项

	void begin_Algorithm();	//算法开始时调用此函数
	void end_Algorithm(QString, int = 2, QString = "");	//算法结束后调用此函数

signals:
	void output_to_main(QString, int = 2, QString = "");


private:
	QWidget *parent;

	Ui::SVM_TrainerClass ui;

	QSet<QString> opened_features;

	QString file_path;
	QString path_bagImage;
	QString path_NbagImage;

	QImage bag_QImage;
	QImage Nbag_QImage;
};