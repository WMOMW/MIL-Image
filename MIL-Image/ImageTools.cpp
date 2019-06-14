#include "stdafx.h"

GrayscaleImage_Thread::GrayscaleImage_Thread(MIL_Image *parent) {
	this->is_normal = false;
}

GrayscaleImage_Thread::~GrayscaleImage_Thread() {
	if (!is_normal)
	{
		emit end_Algorithm(QString::fromLocal8Bit("获取灰度图"), 2, QString::fromLocal8Bit("线程退出。\n"));
	}
}

void GrayscaleImage_Thread::run() {
	cv::Mat temp_Image;
	QString out_text;
	if (ImageTools_Interface::get_GrayscaleImage(Source_Image.get_image(), temp_Image, out_text))
	{
		Destination_Image.set_imageClone(temp_Image);
		Destination_Image.set_imagePath("");
		emit end_Algorithm(QString::fromLocal8Bit("获取灰度图"), 1, out_text);
		this->is_normal = true;
	}
	else
	{
		emit end_Algorithm(QString::fromLocal8Bit("获取灰度图"), 0, out_text);
		this->is_normal = true;
	}
}

FeatureImage_Thread::FeatureImage_Thread(MIL_Image *parent) {
	this->is_normal = false;
}

FeatureImage_Thread::~FeatureImage_Thread() {
	if (!is_normal)
	{
		emit end_Algorithm(QString::fromLocal8Bit("获取特征化图像"), 2, QString::fromLocal8Bit("线程退出。\n"));
	}
}

void FeatureImage_Thread::run() {
	cv::Mat temp_Image;
	QString out_text;
	if (ImageTools_Interface::get_FeatureImage(Source_Image.get_image(), temp_Image, out_text))
	{
		Destination_Image.set_imageClone(temp_Image);
		Destination_Image.set_imagePath("");
		emit end_Algorithm(QString::fromLocal8Bit("获取特征化图像"), 1, out_text);
		this->is_normal = true;
	}
	else
	{
		emit end_Algorithm(QString::fromLocal8Bit("获取特征化图像"), 0, out_text);
		this->is_normal = true;
	}
}

BinaryImage_Thread::BinaryImage_Thread(MIL_Image *parent) {
	this->is_normal = false;
}

BinaryImage_Thread::~BinaryImage_Thread() {
	if (!is_normal)
	{
		emit end_Algorithm(QString::fromLocal8Bit("获取二值化图像"), 2, QString::fromLocal8Bit("线程退出。\n"));
	}
}

void BinaryImage_Thread::run() {
	cv::Mat temp_Image;
	QString out_text;
	if (ImageTools_Interface::get_BinaryImage(Source_Image.get_image(), temp_Image, out_text))
	{
		Destination_Image.set_imageClone(temp_Image);
		Destination_Image.set_imagePath("");
		emit end_Algorithm(QString::fromLocal8Bit("获取二值化图像"), 1, out_text);
		this->is_normal = true;
	}
	else
	{
		emit end_Algorithm(QString::fromLocal8Bit("获取二值化图像"), 0, out_text);
		this->is_normal = true;
	}
}

ImageInfo_Thread::ImageInfo_Thread(MIL_Image *parent) {
	this->is_normal = false;
}

ImageInfo_Thread::~ImageInfo_Thread() {
	if (!is_normal)
	{
		emit end_Algorithm(QString::fromLocal8Bit("获取二值化图像"), 2, QString::fromLocal8Bit("线程退出。\n"));
	}
}

void ImageInfo_Thread::run() {
	cv::Mat temp_DataImage;
	QString out_text;
	if (ImageTools_Interface::get_ImageInfo(Source_Image.get_image(), cv::Mat(), out_text, temp_DataImage))
	{
		Destination_Image.set_imagePath("");
		Data_Image.set_image(temp_DataImage);
		Data_Image.set_imagePath("");
		show_outImageView();
		emit end_Algorithm(QString::fromLocal8Bit("获取图像信息"), 1, out_text);
		this->is_normal = true;
	}
	else
	{
		emit end_Algorithm(QString::fromLocal8Bit("获取图像信息"), 0, out_text);
		this->is_normal = true;
	}
}