#include "stdafx.h"

GrayscaleImage_Thread::GrayscaleImage_Thread(MIL_Image *parent) {
	this->is_normal = false;
}

GrayscaleImage_Thread::~GrayscaleImage_Thread() {
	if (!is_normal)
	{
		emit end_Algorithm(QString::fromLocal8Bit("��ȡ�Ҷ�ͼ"), 2, QString::fromLocal8Bit("�߳��˳���\n"));
	}
}

void GrayscaleImage_Thread::run() {
	cv::Mat temp_Image;
	QString out_text;
	if (ImageTools_Interface::get_GrayscaleImage(Source_Image.get_image(), temp_Image, out_text))
	{
		Destination_Image.set_imageClone(temp_Image);
		Destination_Image.set_imagePath("");
		emit end_Algorithm(QString::fromLocal8Bit("��ȡ�Ҷ�ͼ"), 1, out_text);
		this->is_normal = true;
	}
	else
	{
		emit end_Algorithm(QString::fromLocal8Bit("��ȡ�Ҷ�ͼ"), 0, out_text);
		this->is_normal = true;
	}
}

FeatureImage_Thread::FeatureImage_Thread(MIL_Image *parent) {
	this->is_normal = false;
}

FeatureImage_Thread::~FeatureImage_Thread() {
	if (!is_normal)
	{
		emit end_Algorithm(QString::fromLocal8Bit("��ȡ������ͼ��"), 2, QString::fromLocal8Bit("�߳��˳���\n"));
	}
}

void FeatureImage_Thread::run() {
	cv::Mat temp_Image;
	QString out_text;
	if (ImageTools_Interface::get_FeatureImage(Source_Image.get_image(), temp_Image, out_text))
	{
		Destination_Image.set_imageClone(temp_Image);
		Destination_Image.set_imagePath("");
		emit end_Algorithm(QString::fromLocal8Bit("��ȡ������ͼ��"), 1, out_text);
		this->is_normal = true;
	}
	else
	{
		emit end_Algorithm(QString::fromLocal8Bit("��ȡ������ͼ��"), 0, out_text);
		this->is_normal = true;
	}
}

BinaryImage_Thread::BinaryImage_Thread(MIL_Image *parent) {
	this->is_normal = false;
}

BinaryImage_Thread::~BinaryImage_Thread() {
	if (!is_normal)
	{
		emit end_Algorithm(QString::fromLocal8Bit("��ȡ��ֵ��ͼ��"), 2, QString::fromLocal8Bit("�߳��˳���\n"));
	}
}

void BinaryImage_Thread::run() {
	cv::Mat temp_Image;
	QString out_text;
	if (ImageTools_Interface::get_BinaryImage(Source_Image.get_image(), temp_Image, out_text))
	{
		Destination_Image.set_imageClone(temp_Image);
		Destination_Image.set_imagePath("");
		emit end_Algorithm(QString::fromLocal8Bit("��ȡ��ֵ��ͼ��"), 1, out_text);
		this->is_normal = true;
	}
	else
	{
		emit end_Algorithm(QString::fromLocal8Bit("��ȡ��ֵ��ͼ��"), 0, out_text);
		this->is_normal = true;
	}
}

ImageInfo_Thread::ImageInfo_Thread(MIL_Image *parent) {
	this->is_normal = false;
}

ImageInfo_Thread::~ImageInfo_Thread() {
	if (!is_normal)
	{
		emit end_Algorithm(QString::fromLocal8Bit("��ȡ��ֵ��ͼ��"), 2, QString::fromLocal8Bit("�߳��˳���\n"));
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
		emit end_Algorithm(QString::fromLocal8Bit("��ȡͼ����Ϣ"), 1, out_text);
		this->is_normal = true;
	}
	else
	{
		emit end_Algorithm(QString::fromLocal8Bit("��ȡͼ����Ϣ"), 0, out_text);
		this->is_normal = true;
	}
}