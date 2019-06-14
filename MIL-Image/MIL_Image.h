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
	bool update_Source();	//��cv::Mat�е����ݸ��¡�Դͼ��
	bool update_Destination();	//��cv::Mat�е����ݸ��¡�Ŀ��ͼ��
	bool update_DataImage();	//��cv::Mat�е����ݸ��¡�����ͼ��

protected:
	void resizeDock(QDockWidget*, bool);	//�ñ��������ڴ�С����֤���ϳ�֮����״����

private slots:
	void ttt();	//���Ժ���

	void output_Text(QString, int = 2, QString = "");	//����������������

	void show_Resualt(bool, QString, QString = QString());

	void begin_Algorithm();	//�㷨��ʼʱ���ô˺���
	void end_Algorithm(QString, int = 2, QString = "");	//�㷨��������ô˺���

	void open_Images();	//��ͼƬ��Ԥ���أ�
	void load_SVMs();	//����ѵ���õ�SVMģ�ͣ���ʽ����ͬ��ʾ���ռ䣩
	void save_Image();	//����ͼƬ��Ŀ��ͼ��
	void save_Image_as();	//���ΪͼƬ��Ŀ��ͼ��
	void remove_all_Images();	//�Ƴ��������ڡ�Ԥ���ص�ͼƬ���е�����ͼƬ

	void get_ImageInfo();	//��ȡͼ����Ϣ
	void get_GrayscaleImage();	//��ȡ�Ҷ�ͼ
	void get_FeatureImage();	//��ȡ�и�������ͼ
	void get_BinaryImage();	//��ȡ��ֵ��ͼ��
	void Create_Classifier();	//��ʾ�����·������Ľ���
	void Class_test();	//�������

	void show_ImageView();	//��ʾ��Ԥ���ص�ͼƬ��
	void show_SVMView();	//��ʾ��SVM��
	void show_outputView();	//��ʾ�������
	void show_outImageView();	//��ʾ������ͼ��

	void show_actionAbout();	//��ʾAbout�Ի���

	void Source_to_Destination();	//��Դͼ���Ƶ�Ŀ��ͼ��
	void Destination_to_Source();	//��Ŀ��ͼ���Ƶ�Դͼ��

	void show_ImageView_menu(QPoint);	//��ʾ��Ԥ���ص�ͼƬ���Ҽ��˵�
	void open_Image_from_table_byAction();	//���Ҽ��˵���ʽ�򿪡�Ԥ���ص�ͼƬ���е�ͼ��
	void remove_Image_from_table_byAction();	//���Ҽ��˵���ʽ�Ƴ���Ԥ���ص�ͼƬ���е�ͼ��
	void copy_ImagePath_from_table_byAction();	//���Ҽ��˵���ʽ���ơ�Ԥ���ص�ͼƬ���е�ͼƬ·��
	void show_SVMs_menu(QPoint);	//��ʾ��SVM���Ҽ��˵�
	void remove_SVM_from_table_byAction();	//���Ҽ��˵���ʽ�Ƴ���SVM���е���
	void remove_allSVM_from_table_byAction();	//���Ҽ��˵���ʽ�Ƴ���SVM���е�������
	void copy_SVMPath_from_table_byAction();	//���Ҽ��˵���ʽ���ơ�SVM���е���Ŀ·��
	void select_SVM(QTableWidgetItem*);	//ѡ��SVM����ѡ��򹳣�

	void open_Image_from_table(QTableWidgetItem*);	//��˫���ķ�ʽ�ӡ�Ԥ���ص�ͼƬ���д�ͼƬ
	void remove_Image_from_table(QTableWidgetItem*);	//�Ƴ���Ԥ���ص�ͼƬ���е���
	void remove_SVM_from_table(QTableWidgetItem*);	//�Ƴ���SVM���е���

private:
	Ui::MIL_Image ui;
	ImageReasult_Widget *Success_W;
	ImageReasult_Widget *Failed_W;
	bool s;	//�����жϴ����Ƿ�Ϊ��һ�δ�
	bool f;	//�����жϴ����Ƿ�Ϊ��һ�δ�

	QSet<QString> opened_Images;
	QSet<QString> opened_SVMs;
	QString file_path;
	QString SVM_path;

	QImage Source_QImage;
	QImage Destination_QImage;
	QImage Data_QImage;
};
