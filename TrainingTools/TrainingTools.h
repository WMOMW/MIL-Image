#pragma once
#include "stdafx.h"

class __declspec(dllexport) TrainingTools_Interface {
public:
	static bool Create_Classifier(QStringList bags_path, QStringList Nbags_path, QString save_path, QString &out_text, cv::Mat &out_image = cv::Mat());
	static bool do_Classifier(QString Image_path, QStringList SVMs_path, QStringList &resualt, QString &out_text, cv::Mat &out_image = cv::Mat());
	static void test();
private:
	TrainingTools_Interface();
};

class TrainingTools {
public:
	TrainingTools();
	static bool Create_Classifier(QStringList bags_path, QStringList Nbags_path, QString save_path, QString &out_text, cv::Mat &out_image = cv::Mat());
	static bool do_Classifier(QString Image_path, QStringList SVMs_path, QStringList &resualt, QString &out_text, cv::Mat &out_image = cv::Mat());

	static cv::Mat get_package_feature(cv::Mat package, cv::Mat Feature_space);
	static double get_distance(std::vector<double> p1, std::vector<double> p2, int length);	//计算欧氏距离
	static cv::Ptr<cv::ml::SVM> get_SVM(cv::Mat data, cv::Mat label);	//训练得到分类器
};
