#pragma once
#include "stdafx.h"

#pragma comment(lib,"ImageTools.lib")

class __declspec(dllimport) ImageTools_Interface {
public:
	static bool get_ImageInfo(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());
	static bool get_GrayscaleImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());
	static bool get_FeatureImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat(), cv::Vec3b &threshold = cv::Vec3b());
	static bool get_BinaryImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());

	static bool get_Features(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());

	static void particl_Segment(const cv::Mat inputImage_source, const cv::Mat inputImage_reference, cv::Mat &outputLabel, cv::Vec3b &out_color, unsigned int R_Threshold, unsigned int G_Threshold, unsigned int B_Threshold, unsigned part_BGR);
	static std::vector<cv::Mat> Segment(const cv::Mat image, const cv::Mat image_reference, unsigned int R_Threshold, unsigned int G_Threshold, unsigned int B_Threshold);
	static void remove_dot(cv::Mat inputImage, cv::Mat &outputImage, unsigned int min_area = -1);//去小点
	static void integrate_Image(cv::Mat &output, std::vector<cv::Mat> &outputs);//拼接图形
	static void my_inpaint(cv::Mat &input, cv::Mat &mask);//修复图像

private:
	ImageTools_Interface();
};

class GrayscaleImage_Thread :public QThread {
	Q_OBJECT
public:
	GrayscaleImage_Thread(MIL_Image* = Q_NULLPTR);
	~GrayscaleImage_Thread();
	void run();

signals:
	void end_Algorithm(QString, int = 2, QString = "");

private:
	bool is_normal;
};

class FeatureImage_Thread :public QThread {
	Q_OBJECT
public:
	FeatureImage_Thread(MIL_Image* = Q_NULLPTR);
	~FeatureImage_Thread();
	void run();

signals:
	void end_Algorithm(QString, int = 2, QString = "");

private:
	bool is_normal;
};

class BinaryImage_Thread :public QThread {
	Q_OBJECT
public:
	BinaryImage_Thread(MIL_Image* = Q_NULLPTR);
	~BinaryImage_Thread();
	void run();

signals:
	void end_Algorithm(QString, int = 2, QString = "");

private:
	bool is_normal;
};

class ImageInfo_Thread :public QThread {
	Q_OBJECT
public:
	ImageInfo_Thread(MIL_Image* = Q_NULLPTR);
	~ImageInfo_Thread();
	void run();

signals:
	void end_Algorithm(QString, int = 2, QString = "");
signals:
	void show_outImageView();

private:
	bool is_normal;
};