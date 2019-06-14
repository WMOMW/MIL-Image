#include "stdafx.h"
#include <qdebug.h>

void TrainingTools_Interface::test() {
	cv::Mat img = cv::imread("1.jpg", 1);
	if (img.empty())
	{
		qDebug() << "false." << endl;
		return;
	}
	ImageTools_Interface::get_FeatureImage(img, img, QString());
	cv::imshow("1", img);
	cv::waitKey(10000);
}

bool TrainingTools_Interface::Create_Classifier(QStringList bags, QStringList Nbags, QString save_path, QString &out_text, cv::Mat &out_image) {
	return TrainingTools::Create_Classifier(bags, Nbags, save_path, out_text, out_image);
}

bool TrainingTools_Interface::do_Classifier(QString Image_path, QStringList SVMs_path, QStringList &resualt, QString &out_text, cv::Mat &out_image) {
	return TrainingTools::do_Classifier(Image_path, SVMs_path, resualt, out_text, out_image);
}

TrainingTools::TrainingTools()
{
}

bool TrainingTools::Create_Classifier(QStringList bags_path, QStringList Nbags_path, QString save_path, QString &out_text, cv::Mat &out_image) {
	cv::Mat img, Features_space;
	std::vector<cv::Mat> bags, Nbags;
	//获得特征空间Features_space
	for (auto p : bags_path)
	{
		img = cv::imread(p.toLocal8Bit().toStdString(), 1);
		if (!img.empty())
		{
			cv::Mat temp;
			if (!ImageTools_Interface::get_Features(img, temp, out_text, out_image))
			{
				return false;
			}
			bags.push_back(temp);
			Features_space.push_back(temp);
		}
	}
	for (auto p : Nbags_path)
	{
		img = cv::imread(p.toLocal8Bit().toStdString(), 1);
		if (!img.empty())
		{
			cv::Mat temp;
			if (!ImageTools_Interface::get_Features(img, temp, out_text, out_image))
			{
				return false;
			}
			Nbags.push_back(temp);
			Features_space.push_back(temp);
		}
	}

	//做映射获得每个包的特征向量和标记
	cv::Mat data, label(0, 0, CV_32SC1);
	for (auto p : bags)
	{
		data.push_back(get_package_feature(p, Features_space));
		label.push_back(1);
	}
	for (auto p : Nbags)
	{
		data.push_back(get_package_feature(p, Features_space));
		label.push_back(-1);
	}

	//训练并保存模型
	cv::Ptr<cv::ml::SVM> svm = get_SVM(data, label);
	svm->save(save_path.toLocal8Bit().toStdString());
	cv::FileStorage f(save_path.toLocal8Bit().toStdString(), cv::FileStorage::APPEND);
	f << "Feature_space" << Features_space;

	return true;
}

bool TrainingTools::do_Classifier(QString Image_path, QStringList SVMs_path, QStringList &resualt, QString &out_text, cv::Mat &out_image) {
	resualt.clear();
	cv::Mat img_feature;
	cv::Mat img = cv::imread(Image_path.toLocal8Bit().toStdString(), 1);
	if (img.empty())
	{
		out_text += QString::fromLocal8Bit("\n") + Image_path + QString::fromLocal8Bit("读取失败或为空。\n");
		return false;
	}
	if (!ImageTools_Interface::get_Features(img, img_feature, out_text))
	{
		return false;
	}
	for (auto p : SVMs_path)
	{
		std::string path = p.toLocal8Bit().toStdString();
		cv::Ptr<cv::ml::SVM> svm;
		cv::FileStorage f;
		try
		{
			svm = cv::ml::SVM::load(path);
			f.open(path, cv::FileStorage::READ);
		}
		catch (...)
		{
			out_text += QString::fromLocal8Bit("Error.\n");
			out_text += p + QString::fromLocal8Bit("读取失败或文件为空\n");
			return false;
		}
		cv::Mat Feature_space;
		f["Feature_space"] >> Feature_space;
		if (svm->empty() || Feature_space.empty())
		{
			out_text += QString::fromLocal8Bit("Error.\n");
			if (svm->empty())
			{
				out_text += p + QString::fromLocal8Bit("读取失败或SVM为空\n");
			}
			if (Feature_space.empty())
			{
				out_text += p + QString::fromLocal8Bit("读取失败或特征空间为空。\n");
			}
			resualt.clear();
			return false;
		}
		cv::Mat package = get_package_feature(img_feature, Feature_space);
		float respose = svm->predict(package);
		if (respose == 1)
		{
			QFileInfo f(p);
			resualt.push_back(f.fileName());
		}
	}
	return true;
}

cv::Mat TrainingTools::get_package_feature(cv::Mat package, cv::Mat Feature_space) {
	if (package.cols != Feature_space.cols)
	{
		return cv::Mat(1, Feature_space.cols, CV_32SC1, cv::Scalar::all(0));
	}
	std::vector<std::vector<double> > package_vector;
	std::vector<std::vector<double> > Feature_space_vector;
	for (int i = 0; i < package.rows; ++i)
	{
		std::vector<double> temp;
		for (int j = 0; j < package.cols; ++j)
		{
			temp.push_back(package.at<double>(i, j));
		}
		package_vector.push_back(temp);
	}
	for (int i = 0; i < Feature_space.rows; ++i)
	{
		std::vector<double> temp;
		for (int j = 0; j < Feature_space.cols; ++j)
		{
			temp.push_back(Feature_space.at<double>(i, j));
		}
		Feature_space_vector.push_back(temp);
	}
	std::vector<double> feature;
	for (auto p : Feature_space_vector)
	{
		std::vector<double> temp;
		for (auto q : package_vector)
		{
			temp.push_back(get_distance(q, p, p.size()));
		}
		std::vector<double>::iterator min = std::min_element(std::begin(temp), std::end(temp));
		feature.push_back(*min);
	}
	cv::Mat data(feature);
	data.convertTo(data, CV_32FC1);
	return data.t();
}

double TrainingTools::get_distance(std::vector<double> p1, std::vector<double> p2, int length) {
	if (p1.size() < length || p2.size() < length)
	{
		return 0;
	}
	if (p1.size() != p2.size())
	{
		return 0;
	}
	double sum = 0;
	for (int i = 0; i < length; ++i)
	{
		sum += pow((p1[i] - p2[i]), 2);
	}
	return sqrt(sum);
}

cv::Ptr<cv::ml::SVM> TrainingTools::get_SVM(cv::Mat data, cv::Mat label) {
	cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
	svm->setType(cv::ml::SVM::Types::C_SVC);
	svm->setKernel(cv::ml::SVM::KernelTypes::INTER);
	svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 1000, FLT_EPSILON));

	svm->train(data, cv::ml::SampleTypes::ROW_SAMPLE, label);

	return svm;
}