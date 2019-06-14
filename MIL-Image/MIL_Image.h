#pragma once

#include "ui_MIL_Image.h"
#include "ImageReasult_Widget.h"
#include "SVM_Trainer.h"
#include "stdafx.h"

class MIL_Image : public QMainWindow
{
	Q_OBJECT

public:
	MIL_Image(QWidget *parent = Q_NULLPTR);
	bool update_Source();	//用cv::Mat中的数据更新“源图像”
	bool update_Destination();	//用cv::Mat中的数据更新“目的图像”
	bool update_DataImage();	//用cv::Mat中的数据更新“数据图”

protected:
	void resizeDock(QDockWidget*, bool);	//该边悬浮窗口大小，保证被拖出之后形状正常

private slots:
	void ttt();	//测试函数

	void output_Text(QString, int = 2, QString = "");	//用于输出到“输出”

	void show_Resualt(bool, QString, QString = QString());

	void begin_Algorithm();	//算法开始时调用此函数
	void end_Algorithm(QString, int = 2, QString = "");	//算法结束后调用此函数

	void open_Images();	//打开图片（预加载）
	void load_SVMs();	//载入训练好的SVM模型（隐式加载同名示例空间）
	void save_Image();	//保存图片（目的图像）
	void save_Image_as();	//另存为图片（目的图像）
	void remove_all_Images();	//移除悬浮窗口“预加载的图片”中的所有图片

	void get_ImageInfo();	//获取图像信息
	void get_GrayscaleImage();	//获取灰度图
	void get_FeatureImage();	//获取切割后的特征图
	void get_BinaryImage();	//获取二值化图像
	void Create_Classifier();	//显示创建新分类器的界面
	void Class_test();	//分类测试

	void show_ImageView();	//显示“预加载的图片”
	void show_SVMView();	//显示“SVM”
	void show_outputView();	//显示“输出”
	void show_outImageView();	//显示“数据图”

	void show_actionAbout();	//显示About对话框

	void Source_to_Destination();	//将源图像复制到目的图像
	void Destination_to_Source();	//将目的图像复制到源图像

	void show_ImageView_menu(QPoint);	//显示“预加载的图片”右键菜单
	void open_Image_from_table_byAction();	//以右键菜单方式打开“预加载的图片”中的图像
	void remove_Image_from_table_byAction();	//以右键菜单方式移除“预加载的图片”中的图像
	void copy_ImagePath_from_table_byAction();	//以右键菜单方式复制“预加载的图片”中的图片路径
	void show_SVMs_menu(QPoint);	//显示“SVM”右键菜单
	void remove_SVM_from_table_byAction();	//以右键菜单方式移除“SVM”中的项
	void remove_allSVM_from_table_byAction();	//以右键菜单方式移除“SVM”中的所有项
	void copy_SVMPath_from_table_byAction();	//以右键菜单方式复制“SVM”中的项目路径
	void select_SVM(QTableWidgetItem*);	//选择SVM（复选框打钩）

	void open_Image_from_table(QTableWidgetItem*);	//用双击的方式从“预加载的图片”中打开图片
	void remove_Image_from_table(QTableWidgetItem*);	//移除“预加载的图片”中的项
	void remove_SVM_from_table(QTableWidgetItem*);	//移除“SVM”中的项

private:
	Ui::MIL_Image ui;
	ImageReasult_Widget *Success_W;
	ImageReasult_Widget *Failed_W;
	bool s;	//用于判断窗口是否为第一次打开
	bool f;	//用于判断窗口是否为第一次打开

	QSet<QString> opened_Images;
	QSet<QString> opened_SVMs;
	QString file_path;
	QString SVM_path;

	QImage Source_QImage;
	QImage Destination_QImage;
	QImage Data_QImage;
};
