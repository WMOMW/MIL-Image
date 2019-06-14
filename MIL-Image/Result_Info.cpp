#include "stdafx.h"

Result_Info::Result_Info(QString Image_path, QStringList outputClass) {
	this->Image_path = Image_path;
	this->outputClass = outputClass;
}

Result_Info::~Result_Info() {
	outputClass.clear();
	Image_path.clear();
}

QStringList Result_Info::get_outputClass() {
	return outputClass;
}

QString Result_Info::get_Image_path() {
	return Image_path;
}

void Result_Info::set_outputClass(QStringList outputClass) {
	this->outputClass = outputClass;
}

void Result_Info::set_Image_path(QString Image_path) {
	this->Image_path = Image_path;
}

void Result_Info::clear() {
	outputClass.clear();
	Image_path.clear();
}

Result_Info &Result_Info::operator=(const Result_Info info) {
	if (this != &info)
	{
		clear();
		this->Image_path = info.Image_path;
		this->outputClass = info.outputClass;
	}
	return *this;
}