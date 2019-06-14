#pragma once

#include <qstring.h>
#include <opencv2\opencv.hpp>
class namedImage {
public:
	namedImage(cv::Mat = cv::Mat(), QString = QString(), bool = false);
	namedImage(QString);
	namedImage(const namedImage&);
	~namedImage();

	QString get_imagePath();
	cv::Mat get_image();
	cv::Mat get_imageClone();

	bool open_Image(QString);

	void set_imagePath(QString);
	void set_image(cv::Mat);
	void set_imageClone(cv::Mat);

	bool isEmpty();

	void eraseImage();

	namedImage &operator=(const namedImage);

private:
	cv::Mat Image;
	QString Image_path;
};