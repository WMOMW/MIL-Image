#pragma once

#include "ui_SVM_Trainer.h"
#include "stdafx.h"

class SVM_Trainer : public QMainWindow
{
	Q_OBJECT
public:
	SVM_Trainer(QWidget *parent = Q_NULLPTR);

private slots:
	void ttt();	//���Ժ���

	void open_Bags();	//������ʾ��
	void open_NBags();	//�򿪷���ʾ��
	void save_SVM();

	void show_bagsView_menu(QPoint);	//��ʾ����table�Ҽ��˵�
	void open_Image_from_bagsView_byAction();	//���Ҽ��˵���ʽ������table�е�ͼ��
	void remove_Image_from_bagsView_byAction();	//���Ҽ��˵���ʽ�Ƴ�����table�е�ͼ��
	void remove_allImage_from_bagsView_byAction();	//���Ҽ��˵���ʽ�Ƴ�����table�е�ȫ��ͼ��
	void copy_ImagePath_from_bagsView_byAction();	//���Ҽ��˵���ʽ��������table�е�ͼƬ·��
	void show_NbagsView_menu(QPoint);	//��ʾ����table�Ҽ��˵�
	void open_Image_from_NbagsView_byAction();	//���Ҽ��˵���ʽ�򿪷���table�е�ͼ��
	void remove_Image_from_NbagsView_byAction();	//���Ҽ��˵���ʽ�Ƴ�����table�е�ͼ��
	void remove_allImage_from_NbagsView_byAction();	//���Ҽ��˵���ʽ�Ƴ�����table�е�ȫ��ͼ��
	void copy_ImagePath_from_NbagsView_byAction();	//���Ҽ��˵���ʽ���Ʒ���table�е�ͼƬ·��

	void open_Image_from_bagsView(QTableWidgetItem*);	//��˫���ķ�ʽ�������д�ͼƬ
	void open_Image_from_NbagsView(QTableWidgetItem*);	//��˫���ķ�ʽ�ӷ����д�ͼƬ
	void remove_Image_from_bagsView(QTableWidgetItem*);	//�Ƴ���Ԥ���ص�ͼƬ���е���
	void remove_Image_from_NbagsView(QTableWidgetItem*);	//�Ƴ���Ԥ���ص�ͼƬ���е���

	void begin_Algorithm();	//�㷨��ʼʱ���ô˺���
	void end_Algorithm(QString, int = 2, QString = "");	//�㷨��������ô˺���

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