#include "stdafx.h"

QImage cvMatToQImage(const cv::Mat mat) {
	const unsigned char* data = mat.data;
	int width = mat.cols;
	int height = mat.rows;
	int bytesPerLine = static_cast<int>(mat.step);
	switch (mat.type())
	{
		// 8bit, ARGB
	case CV_8UC4:
		return QImage(data, width, height, bytesPerLine, QImage::Format_ARGB32).rgbSwapped();
		// 8bit, BGR
	case CV_8UC3:
		return QImage(data, width, height, bytesPerLine, QImage::Format_RGB888).rgbSwapped();

		//swap blue and red channel
	// 8bit, Grayshale
	case CV_8UC1:
		return QImage(data, width, height, bytesPerLine, QImage::Format_Grayscale8);
	default:
		// Unsupported format
		return QImage();
	}
}