#include "stdafx.h"

CreateClassifier_Thread::CreateClassifier_Thread(QStringList bags_path, QStringList Nbags_path, QString save_path, SVM_Trainer *parent) {
	this->bags_path = bags_path;
	this->Nbags_path = Nbags_path;
	this->save_path = save_path;
	this->is_normal = false;
}

CreateClassifier_Thread::~CreateClassifier_Thread() {
	if (!is_normal)
	{
		emit end_Algorithm(QString::fromLocal8Bit("训练并保存SVM模型"), 2, QString::fromLocal8Bit("线程退出。\n"));
	}
}

void CreateClassifier_Thread::run() {
	QString out_text;
	if (TrainingTools_Interface::Create_Classifier(bags_path, Nbags_path, save_path, out_text, cv::Mat()))
	{
		emit end_Algorithm(QString::fromLocal8Bit("训练并保存SVM模型至\t") + save_path, 1, out_text);
		is_normal = true;
	}
	else
	{
		emit end_Algorithm(QString::fromLocal8Bit("训练SVM模型"), 0, out_text);
		is_normal = true;
	}
}


ClassTest_Thread::ClassTest_Thread(QStringList Images_path, QStringList SVMs_path, MIL_Image *parent) {
	this->Images_path = Images_path;
	this->SVMs_path = SVMs_path;
	this->is_normal = false;
}

ClassTest_Thread::~ClassTest_Thread() {
	if (!is_normal)
	{
		emit end_Algorithm(QString::fromLocal8Bit("分类测试"), 2, QString::fromLocal8Bit("线程退出。\n"));
	}
}

void ClassTest_Thread::run() {
	QString out_text;
	QLinkedList<Result_Info> s_results;
	QLinkedList<Result_Info> f_results;
	for (auto p : Images_path)
	{
		QStringList temp;
		emit output_to_main(QString::fromLocal8Bit("正在分类") + p + QString::fromLocal8Bit("......"));
		if (!TrainingTools_Interface::do_Classifier(p, SVMs_path, temp, out_text))
		{
			emit end_Algorithm(QString::fromLocal8Bit("分类") + p, 0, out_text);
			is_normal = true;
			continue;
		}
		Result_Info r;
		r.set_Image_path(p);
		r.set_outputClass(temp);
		if (temp.isEmpty())
		{
			f_results.push_back(r);
		}
		else
		{
			s_results.push_back(r);
		}

	}
	s_Info = s_results;
	f_Info = f_results;

	emit show_Resualt(true, QString::fromLocal8Bit("分类结果(") + QString::number(s_results.size()).toLocal8Bit() + QString::fromLocal8Bit(")"), QString::fromLocal8Bit("NULL"));
	emit show_Resualt(false, QString::fromLocal8Bit("未分类结果(") + QString::number(f_results.size()).toLocal8Bit() + QString::fromLocal8Bit(")"), QString::fromLocal8Bit("NULL"));
	emit end_Algorithm(QString::fromLocal8Bit("分类测试"), 1, out_text);
	is_normal = true;
}
