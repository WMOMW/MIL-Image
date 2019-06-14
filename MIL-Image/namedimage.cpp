#include "stdafx.h"

namedImage::namedImage(cv::Mat Image, QString Image_path, bool clone) {
	if (clone)
	{
		this->Image = Image.clone();
	}
	else
	{
		this->Image = Image;
	}
	this->Image_path = Image_path;
}

namedImage::namedImage(QString file_name) {
	open_Image(file_name);
}

namedImage::namedImage(const namedImage &p) {
	this->Image = p.Image.clone();
	this->Image_path = p.Image_path;
}

namedImage::~namedImage() {
	Image.release();
	Image_path.clear();
}

QString namedImage::get_imagePath() {
	return Image_path;
}

cv::Mat namedImage::get_image() {
	return Image;
}

cv::Mat namedImage::get_imageClone() {
	return Image.clone();
}

bool namedImage::open_Image(QString file_name) {
	Image.release();
	Image_path = file_name;
	Image = cv::imread(Image_path.toLocal8Bit().toStdString(), 1);
	if (Image.empty())
	{
		return false;
	}
	return true;
}

void namedImage::set_imagePath(QString Image_path) {
	this->Image_path.clear();
	this->Image_path = Image_path;
}

void namedImage::set_image(cv::Mat Image) {
	this->Image.release();
	this->Image = Image;
}

void namedImage::set_imageClone(cv::Mat Image) {
	this->Image.release();
	this->Image = Image.clone();
}

bool namedImage::isEmpty() {
	return Image.empty();
}

void namedImage::eraseImage() {
	Image.release();
	Image_path.clear();
}

namedImage &namedImage::operator=(const namedImage p) {
	if (this != &p)
	{
		eraseImage();
		this->Image = p.Image.clone();
		this->Image_path = p.Image_path;
	}
	return *this;
}