#pragma once
#include "stdafx.h"

#pragma comment(lib,"TrainingTools.lib")

class __declspec(dllimport) TrainingTools_Interface {
public:
	static bool Create_Classifier(QStringList bags_path, QStringList Nbags_path, QString save_path, QString &out_text, cv::Mat &out_image = cv::Mat());
	static bool do_Classifier(QString Image_path, QStringList SVMs_path, QStringList &resualt, QString &out_text, cv::Mat &out_image = cv::Mat());
	static void test();
private:
	TrainingTools_Interface();
};

class CreateClassifier_Thread :public QThread {
	Q_OBJECT
public:
	CreateClassifier_Thread(QStringList, QStringList, QString, SVM_Trainer* = Q_NULLPTR);
	~CreateClassifier_Thread();
	void run();

signals:
	void end_Algorithm(QString, int = 2, QString = "");
signals:
	void output_to_main(QString, int = 2, QString = "");

private:
	QStringList bags_path;
	QStringList Nbags_path;
	QString save_path;
	bool is_normal;
};

class ClassTest_Thread :public QThread {
	Q_OBJECT
public:
	ClassTest_Thread(QStringList, QStringList, MIL_Image* = Q_NULLPTR);
	~ClassTest_Thread();
	void run();

signals:
	void end_Algorithm(QString, int = 2, QString = "");
signals:
	void output_to_main(QString, int = 2, QString = "");
signals:
	void show_Resualt(bool, QString, QString = QString());

private:
	QStringList Images_path;
	QStringList SVMs_path;
	bool is_normal;
};