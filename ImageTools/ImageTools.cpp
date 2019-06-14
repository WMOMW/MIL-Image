#include "stdafx.h"
#include <qdebug.h>

#ifndef My_Channel
#define My_Channel_Blue 0
#define My_Channel_Green 1
#define My_Channel_Red 2
#endif // !My_Channel

#ifndef My_min_Variance
#define My_min_Variance 200
#endif // !My_min_Variance

#ifndef My_minDot_coefficient
#define My_minDot_coefficient (0.0025)
#endif // !My_minDot_coefficient


bool ImageTools_Interface::get_ImageInfo(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img) {
	return ImageTools::get_ImageInfo(input, output, out_text, out_img);
}

bool ImageTools_Interface::get_GrayscaleImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img) {
	return ImageTools::get_GrayscaleImage(input, output, out_text, out_img);
}

bool ImageTools_Interface::get_FeatureImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img, cv::Vec3b &threshold) {
	return ImageTools::get_FeatureImage(input, output, out_text, out_img, threshold);
}

bool ImageTools_Interface::get_BinaryImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img) {
	return ImageTools::get_BinaryImage(input, output, out_text, out_img);
}

bool ImageTools_Interface::get_Features(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img) {
	return ImageTools::get_Features(input, output, out_text, out_img);
}

void ImageTools_Interface::particl_Segment(const cv::Mat inputImage_source, const cv::Mat inputImage_reference,
	cv::Mat &outputLabel, cv::Vec3b &out_color,
	unsigned int R_Threshold, unsigned int G_Threshold, unsigned int B_Threshold,
	unsigned part_BGR) {
	ImageTools::particl_Segment(inputImage_source, inputImage_reference, outputLabel, out_color, R_Threshold, G_Threshold, B_Threshold, part_BGR);
}

std::vector<cv::Mat> ImageTools_Interface::Segment(const cv::Mat image, const cv::Mat image_reference, unsigned int R_Threshold, unsigned int G_Threshold, unsigned int B_Threshold) {
	return ImageTools::Segment(image, image_reference, R_Threshold, G_Threshold, B_Threshold);
}

void ImageTools_Interface::remove_dot(cv::Mat inputImage, cv::Mat &outputImage, unsigned int min_area) {
	ImageTools::remove_dot(inputImage, outputImage, min_area);
}

void ImageTools_Interface::integrate_Image(cv::Mat &output, std::vector<cv::Mat> &outputs) {
	ImageTools::integrate_Image(output, outputs);
}

void ImageTools_Interface::my_inpaint(cv::Mat &input, cv::Mat &mask) {
	ImageTools::my_inpaint(input, mask);
}




bool ImageTools::get_ImageInfo(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img) {
	if (input.empty())
	{
		out_text += QString::fromLocal8Bit("源图为空\n");
		return false;
	}
	if (input.type() == CV_8UC1)
	{
		cv::cvtColor(input, output, cv::COLOR_GRAY2BGR);
	}
	unsigned int rows = input.rows, cols = input.cols;
	out_text += QString::fromLocal8Bit("图片分辨率为 (") + QString::number(rows, 10) + QString::fromLocal8Bit(", ") + QString::number(cols, 10) + QString::fromLocal8Bit(")\n");
	out_img.release();
	out_img = cv::Mat(256, 256, CV_8UC3, cv::Scalar::all(0));
	unsigned int max = 0;
	unsigned int R[256], G[256], B[256];
	for (int i = 0; i < 256; ++i)
	{
		R[i] = 0;
		G[i] = 0;
		B[i] = 0;
	}
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			++R[input.at<cv::Vec3b>(i, j)[2]];
			++G[input.at<cv::Vec3b>(i, j)[1]];
			++B[input.at<cv::Vec3b>(i, j)[0]];
		}
	}
	for (int i = 0; i < 256; ++i)
	{
		max = max > R[i] ? max : R[i];
		max = max > G[i] ? max : G[i];
		max = max > B[i] ? max : B[i];
	}
	double n = (256 / static_cast<double>(max));
	for (int j = 0; j < 256; ++j)
	{
		for (int R_col = 256 - (n * R[j]); R_col < 256; ++R_col)
		{
			out_img.at<cv::Vec3b>(R_col, j)[2] = 255;
		}
		for (int G_col = 256 - (n * G[j]); G_col < 256; ++G_col)
		{
			out_img.at<cv::Vec3b>(G_col, j)[1] = 255;
		}
		for (int B_col = 256 - (n * B[j]); B_col < 256; ++B_col)
		{
			out_img.at<cv::Vec3b>(B_col, j)[0] = 255;
		}
	}
	for (int i = 0; i < 256; ++i)
	{
		for (int j = 0; j < 256; ++j)
		{
			if (out_img.at<cv::Vec3b>(i, j) == cv::Vec3b(0, 0, 0))
			{
				out_img.at<cv::Vec3b>(i, j) = cv::Vec3b(127, 127, 127);
			}
		}
	}
	return true;
}

bool ImageTools::get_GrayscaleImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img) {
	output.release();
	if (input.type() == CV_8UC3 && !input.empty())
	{
		cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);
		out_text += "";
		return true;
	}
	else
	{
		out_text += QString::fromLocal8Bit("源图为空 或 非八位三色图\n");
		return false;
	}
}

bool ImageTools::get_FeatureImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img, cv::Vec3b &threshold) {
	if (input.type() == CV_8UC3 && !input.empty())
	{
		cv::Mat _input = input.clone();
		std::vector<cv::Mat> outputs;
		//cv::Mat image_reference;
		//L_balance(input, image_reference);
		cv::GaussianBlur(_input, _input, cv::Size(3, 3), 0, 0);
		unsigned int B_Threshold = Get_Channle_Threshold(_input, My_Channel_Blue, My_min_Variance);
		unsigned int G_Threshold = Get_Channle_Threshold(_input, My_Channel_Green, My_min_Variance);
		unsigned int R_Threshold = Get_Channle_Threshold(_input, My_Channel_Red, My_min_Variance);
		threshold = cv::Vec3b(R_Threshold, G_Threshold, B_Threshold);
		outputs = Segment(_input, _input, R_Threshold, G_Threshold, B_Threshold);
		/*cv::GaussianBlur(image_reference, image_reference, cv::Size(3, 3), 0, 0);
		unsigned int B_Threshold = Get_Channle_Threshold(image_reference, My_Channel_Blue, My_min_Variance);
		unsigned int G_Threshold = Get_Channle_Threshold(image_reference, My_Channel_Green, My_min_Variance);
		unsigned int R_Threshold = Get_Channle_Threshold(image_reference, My_Channel_Red, My_min_Variance);
		outputs = Segment(input, image_reference, R_Threshold, G_Threshold, B_Threshold);*/
		for (auto &img : outputs)
		{
			remove_dot(img, img);
		}
		integrate_Image(output, outputs);
		cv::Mat inpaintLabel(_input.rows, _input.cols, CV_8UC1, cv::Scalar(0));
		for (unsigned int x = 0; x < _input.rows; ++x)
		{
			for (unsigned int y = 0; y < _input.cols; ++y)
			{
				if ((output.at<cv::Vec3b>(x, y) == cv::Vec3b(0, 0, 0)))
				{
					inpaintLabel.at<uchar>(x, y) = 1;
				}
			}
		}
		my_inpaint(output, inpaintLabel);
		out_text += "";
		return true;
	}
	else
	{
		out_text += QString::fromLocal8Bit("源图为空 或 非八位三色图\n");
		return false;
	}
}

bool ImageTools::get_BinaryImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img) {
	output.release();
	if (input.type() == CV_8UC3 && !input.empty())
	{
		if (get_GrayscaleImage(input, input, QString()))
		{
			cv::threshold(input, output, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
			out_text += "";
			return true;
		}
	}
	out_text += QString::fromLocal8Bit("源图为空 或 非八位三色图\n");
	return false;
}

bool ImageTools::get_Features(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img) {
	const unsigned int rows = input.rows, cols = input.cols;
	if (cols < 4 || rows < 4)
	{
		out_text += QString::fromLocal8Bit("源图过小，无法计算。\n");
		return false;
	}

	//初步切割
	cv::Mat temp_1;
	cv::Vec3b threshold;
	if (!get_FeatureImage(input, temp_1, out_text, out_img, threshold))
	{
		return false;
	}

	output.release();

	//取得4×4不重叠快的小波变换结果
	cv::Mat temp_wavelet((rows / 4 * 4), (cols / 4 * 4), CV_64F, cv::Scalar::all(0));
	for (int i = 0; i < rows / 4; ++i)
	{
		for (int j = 0; j < cols / 4; ++j)
		{
			cv::Rect rect(j * 4, i * 4, 4, 4);
			cv::Mat wavelet_part = input(rect);
			cv::Mat wavelet_resualt = WDT(wavelet_part, "sym2");
			for (int x = 0; x < 4; ++x)
			{
				for (int y = 0; y < 4; ++y)
				{
					temp_wavelet.at<double>(i * 4 + x, j * 4 + y) = wavelet_resualt.at<float>(x, y);
				}
			}
			wavelet_part.release();
			wavelet_resualt.release();
		}
	}
	//二次切割
	unsigned int B_Threshold = threshold[0];
	unsigned int G_Threshold = threshold[1];
	unsigned int R_Threshold = threshold[2];
	std::vector<cv::Mat> outputs;
	outputs = Segment(temp_1, temp_1, R_Threshold, G_Threshold, B_Threshold);
	//获取特征向量
	for (auto img : outputs)
	{
		///获得Hu不变矩
		std::vector<double> Hu = get_HuMoments(img);
		bool flag = true;	//用来判断图片是否为空的标记
		for (auto p : Hu)
		{
			if (p != 0)
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			continue;
		}
		///获取标记图
		cv::Mat mask(rows / 4, cols / 4, CV_8UC1, cv::Scalar::all(0));
		for (int i = 0; i < rows - rows % 4; ++i)
		{
			for (int j = 0; j < cols - cols % 4; ++j)
			{
				if (img.at<cv::Vec3b>(i, j) != cv::Vec3b(0, 0, 0))
				{
					mask.at<uchar>(i / 4, j / 4) = 1;
				}
			}
		}

		///获取小波变换结果
		double area_1 = 0, area_2 = 0, area_3 = 0;
		unsigned int count = 0;
		for (int i = 0; i < mask.rows; ++i)
		{
			for (int j = 0; j < mask.cols; ++j)
			{
				if (mask.at<uchar>(i, j) == 1)
				{
					++count;
					area_1 += sqrt((pow(temp_wavelet.at<double>(i, j + 2), 2) + pow(temp_wavelet.at<double>(i, j + 3), 2) + pow(temp_wavelet.at<double>(i + 1, j + 2), 2) + pow(temp_wavelet.at<double>(i + 1, j + 2), 2)) / 4);
					area_2 += sqrt((pow(temp_wavelet.at<double>(i + 2, j), 2) + pow(temp_wavelet.at<double>(i + 2, j + 1), 2) + pow(temp_wavelet.at<double>(i + 3, j), 2) + pow(temp_wavelet.at<double>(i + 3, j + 1), 2)) / 4);
					area_3 += sqrt((pow(temp_wavelet.at<double>(i + 2, j + 2), 2) + pow(temp_wavelet.at<double>(i + 2, j + 3), 2) + pow(temp_wavelet.at<double>(i + 1 + 3, j + 2), 2) + pow(temp_wavelet.at<double>(i + 3, j + 3), 2)) / 4);
				}
			}
		}
		area_1 = area_1 / count;
		area_2 = area_2 / count;
		area_3 = area_3 / count;

		///获取LUV信息
		cv::Mat temp_2;
		cv::cvtColor(img, temp_2, cv::COLOR_BGR2Luv);
		unsigned int L = 0, U = 0, V = 0;
		for (int i = 0; i < img.rows; ++i)
		{
			bool flag_2 = false;
			for (int j = 0; j < img.cols; ++j)
			{
				if (img.at<cv::Vec3b>(i, j) != cv::Vec3b(0, 0, 0))
				{
					flag_2 = true;
					L = temp_2.at<cv::Vec3b>(i, j)[0];
					U = temp_2.at<cv::Vec3b>(i, j)[1];
					V = temp_2.at<cv::Vec3b>(i, j)[2];
					break;
				}
			}
			if (flag_2)
			{
				break;
			}
		}

		///生成特征向量
		cv::Mat temp_3(1, 13, CV_64F);
		temp_3.at<double>(0, 0) = L;
		temp_3.at<double>(0, 1) = U;
		temp_3.at<double>(0, 2) = V;
		temp_3.at<double>(0, 3) = area_1;
		temp_3.at<double>(0, 4) = area_2;
		temp_3.at<double>(0, 5) = area_3;
		temp_3.at<double>(0, 6) = Hu[0];
		temp_3.at<double>(0, 7) = Hu[1];
		temp_3.at<double>(0, 8) = Hu[2];
		temp_3.at<double>(0, 9) = Hu[3];
		temp_3.at<double>(0, 10) = Hu[4];
		temp_3.at<double>(0, 11) = Hu[5];
		temp_3.at<double>(0, 12) = Hu[6];
		output.push_back(temp_3);

		//释放内存
		temp_3.release();
		temp_2.release();
		mask.release();
	}
	return true;
}

std::vector<double> ImageTools::get_HuMoments(cv::Mat input) {
	if (input.type() != CV_8UC3 && input.type() != CV_8UC1)
	{
		return std::vector<double>();
	}
	if (input.type() == CV_8UC3)
	{
		cv::cvtColor(input, input, cv::COLOR_BGR2GRAY);
	}
	cv::threshold(input, input, 0, 255, cv::THRESH_BINARY);
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(input, contours, cv::noArray(), cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
	input = cv::Scalar::all(0);
	cv::drawContours(input, contours, -1, cv::Scalar::all(255));
	double Hu[7];
	cv::HuMoments(cv::moments(input, true), Hu);
	return std::vector<double>(Hu, Hu + 7);
}

unsigned int ImageTools::Otsu_Threshold(cv::Mat temp, unsigned int min_Variance) {
	if (temp.type() != CV_8UC1)
	{
		return 0;
	}

	unsigned int rows = temp.rows, cols = temp.cols;
	unsigned int pixelCount[256];
	double pixelPro[256];
	unsigned int pixelSum = rows * cols, threshold = 0;

	//初始化
	for (unsigned int i = 0; i < 256; ++i)
	{
		pixelCount[i] = 0;
		pixelPro[i] = 0;
	}

	//统计灰度级中每个像素在整幅图像中的个数
	for (unsigned int i = 0; i < rows; ++i)
	{
		for (unsigned int j = 0; j < cols; ++j)
		{
			pixelCount[temp.at<uchar>(i, j)]++;
		}
	}

	//计算每个像素在整幅图像中的比例
	for (int i = 0; i < 256; ++i)
	{
		pixelPro[i] = static_cast<double>(pixelCount[i]) / static_cast<double>(pixelSum);
	}

	//经典ostu算法,得到前景和背景的分割
	//遍历灰度级[0,255],计算出方差最大的灰度值,为最佳阈值
	double w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
	for (int i = 0; i < 256; ++i)
	{
		w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;

		for (int j = 0; j < 256; ++j)
		{
			if (j <= i) //背景部分
			{
				//以i为阈值分类，第一类总的概率
				w0 += pixelPro[j];
				u0tmp += j * pixelPro[j];
			}
			else       //前景部分
			{
				//以i为阈值分类，第二类总的概率
				w1 += pixelPro[j];
				u1tmp += j * pixelPro[j];
			}
		}

		u0 = u0tmp / w0;        //第一类的平均灰度
		u1 = u1tmp / w1;        //第二类的平均灰度
		u = u0tmp + u1tmp;        //整幅图像的平均灰度
		//计算类间方差
		deltaTmp = w0 * (u0 - u)*(u0 - u) + w1 * (u1 - u)*(u1 - u);
		//找出最大类间方差以及对应的阈值
		if (deltaTmp > deltaMax)
		{
			deltaMax = deltaTmp;
			threshold = i;
		}
	}
	//返回最佳阈值;
	if (deltaMax < min_Variance)
	{
		return 0;
	}
	return threshold;
}

unsigned int ImageTools::Get_Channle_Threshold(cv::Mat image, unsigned int channel, unsigned int min_Variance) {
	if (channel > 2 || channel < 0)
	{
		return -1;
	}
	unsigned int rows = image.rows, cols = image.cols;
	cv::Mat temp(rows, cols, CV_8UC1);
	for (unsigned int i = 0; i < rows; ++i)
	{
		for (unsigned int j = 0; j < cols; ++j)
		{
			temp.at<uchar>(i, j) = image.at<cv::Vec3b>(i, j)[channel];
		}
	}
	return Otsu_Threshold(temp, min_Variance);
}

/*
inputImage_source 源图
inputImage_reference 参考图
outputLabel 标记图
out_color 区域RGB均色
part_BGR RGB空间的部分
*/
void ImageTools::particl_Segment(const cv::Mat inputImage_source, const cv::Mat inputImage_reference,
	cv::Mat &outputLabel, cv::Vec3b &out_color,
	unsigned int R_Threshold, unsigned int G_Threshold, unsigned int B_Threshold,
	unsigned part_BGR) {
	unsigned int rows = inputImage_reference.rows, cols = inputImage_reference.cols;
	unsigned long long Red_sum = 0, Green_sum = 0, Blue_sum = 0, sum = 0;

	outputLabel.release();
	outputLabel = cv::Mat(rows, cols, CV_8UC1, cv::Scalar(0));
	for (unsigned int i = 0; i < rows; ++i)
	{
		for (unsigned int j = 0; j < cols; ++j)
		{
			if (inputImage_reference.at<cv::Vec3b>(i, j)[2] < R_Threshold)
			{
				if (part_BGR & 0x1)
				{
					continue;
				}
			}
			else
			{
				if (!(part_BGR & 0x1))
				{
					continue;
				}
			}
			if (inputImage_reference.at<cv::Vec3b>(i, j)[1] < G_Threshold)
			{
				if ((part_BGR >> 1) & 0x1)
				{
					continue;
				}
			}
			else
			{
				if (!((part_BGR >> 1) & 0x1))
				{
					continue;
				}
			}
			if (inputImage_reference.at<cv::Vec3b>(i, j)[0] < B_Threshold)
			{
				if ((part_BGR >> 2) & 0x1)
				{
					continue;
				}
			}
			else
			{
				if (!((part_BGR >> 2) & 0x1))
				{
					continue;
				}
			}
			outputLabel.at<uchar>(i, j) = static_cast<uchar>(1);
			Red_sum += inputImage_source.at<cv::Vec3b>(i, j)[2];
			Green_sum += inputImage_source.at<cv::Vec3b>(i, j)[1];
			Blue_sum += inputImage_source.at<cv::Vec3b>(i, j)[0];
			++sum;
		}
	}
	if (sum != 0)
	{
		out_color[0] = static_cast<uchar>(Blue_sum / sum);
		out_color[1] = static_cast<uchar>(Green_sum / sum);
		out_color[2] = static_cast<uchar>(Red_sum / sum);
	}
}

/*
image 源图
image_reference 参考图
根据参考图切割源图，返回切割后并以RGB均值填充完的各个部分
*/
std::vector<cv::Mat> ImageTools::Segment(const cv::Mat image, const cv::Mat image_reference, unsigned int R_Threshold, unsigned int G_Threshold, unsigned int B_Threshold) {
	std::vector<cv::Mat> output;
	unsigned int rows = image.rows;
	unsigned int cols = image.cols;
	cv::Vec3b out_color;
	cv::Mat outputLabel;
	cv::Mat temp_image;
	for (unsigned int i = 0; i < 8; ++i)
	{
		temp_image.release();
		temp_image = cv::Mat(rows, cols, CV_8UC3, cv::Scalar(0));
		particl_Segment(image, image_reference, outputLabel, out_color, R_Threshold, G_Threshold, B_Threshold, i);
		for (unsigned int x = 0; x < rows; ++x)
		{
			for (unsigned int y = 0; y < cols; ++y)
			{

				if (outputLabel.at<uchar>(x, y) == static_cast<uchar>(1))
				{
					temp_image.at<cv::Vec3b>(x, y) = out_color;
				}
			}
		}
		output.push_back(temp_image.clone());
	}
	return output;
}

void ImageTools::remove_dot(cv::Mat inputImage, cv::Mat &outputImage, unsigned int min_area) {
	unsigned int rows = inputImage.rows, cols = inputImage.cols;
	if (min_area == -1)
	{
		min_area = (rows*cols)*My_minDot_coefficient;
	}

	cv::Mat img, img_edge, labels, stats, temp;
	cv::cvtColor(inputImage, img, cv::COLOR_BGR2GRAY);
	cv::threshold(img, img_edge, 1, 255, cv::THRESH_BINARY);
	int nccomps = cv::connectedComponentsWithStats(img_edge, labels, stats, temp);

	outputImage.release();
	outputImage = cv::Mat(rows, cols, CV_8UC3, cv::Scalar::all(0));

	std::vector<bool> is_dot(nccomps);
	for (unsigned int i = 0; i < nccomps; ++i)
	{
		if (stats.at<int>(i, cv::CC_STAT_AREA) < min_area)
		{
			is_dot[i] = true;
		}
		else
		{
			is_dot[i] = false;
		}
	}
	for (unsigned int x = 0; x < rows; ++x)
	{
		for (unsigned int y = 0; y < cols; ++y)
		{
			int label = labels.at<int>(x, y);
			if (label<0 || label>nccomps)
			{
				continue;
			}
			if (!is_dot[label])
			{
				outputImage.at<cv::Vec3b>(x, y) = inputImage.at<cv::Vec3b>(x, y);
			}
		}
	}
}

void ImageTools::integrate_Image(cv::Mat &output, std::vector<cv::Mat> &outputs) {
	output.release();
	output = cv::Mat((*(outputs.begin())).rows, (*(outputs.begin())).cols, CV_8UC3, cv::Scalar::all(0));
	for (auto i : outputs)
	{
		if (i.type() == CV_8UC3)
		{
			for (unsigned int x = 0; x < output.rows; ++x)
			{
				for (unsigned int y = 0; y < output.cols; ++y)
				{
					if ((i.at<cv::Vec3b>(x, y)[0] != 0) || (i.at<cv::Vec3b>(x, y)[1] != 0) || (i.at<cv::Vec3b>(x, y)[2] != 0))
					{
						output.at<cv::Vec3b>(x, y)[0] = i.at<cv::Vec3b>(x, y)[0];
						output.at<cv::Vec3b>(x, y)[1] = i.at<cv::Vec3b>(x, y)[1];
						output.at<cv::Vec3b>(x, y)[2] = i.at<cv::Vec3b>(x, y)[2];
					}
				}
			}
		}
	}
}

void ImageTools::my_inpaint(cv::Mat &input, cv::Mat &mask) {
	if (input.type() != CV_8UC3 && mask.type() != CV_8UC1)
	{
		return;
	}
	cv::Mat Image, Label;
	get_extendImage(input, Image);
	get_extendImage(mask, Label);
	if (input.size() == mask.size() && !input.empty() && !mask.empty())
	{
		unsigned int rows = input.rows + 1, cols = input.cols + 1;
		for (unsigned int i = 1; i < rows; ++i)
		{
			for (unsigned int j = 1; j < cols; ++j)
			{
				if (Label.at<uchar>(i, j) == 1)
				{
					std::vector<cv::Vec3b> temp;
					if (i - 1 != 0 && j - 1 != 0 && Label.at<uchar>(i - 1, j - 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(i - 1, j - 1));
					}
					if (i - 1 != 0 && Label.at<uchar>(i - 1, j) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(i - 1, j));
					}
					if (i - 1 != 0 && j + 1 != cols && Label.at<uchar>(i - 1, j + 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(i - 1, j + 1));
					}
					if (j - 1 != 0 && Label.at<uchar>(i, j - 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(i, j - 1));
					}
					if (j + 1 != cols && Label.at<uchar>(i, j + 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(i, j + 1));
					}
					if (i + 1 != rows && j - 1 != 0 && Label.at<uchar>(i + 1, j - 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(i + 1, j - 1));
					}
					if (i + 1 != rows && Label.at<uchar>(i + 1, j) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(i + 1, j));
					}
					if (i + 1 != rows && j + 1 != cols && Label.at<uchar>(i + 1, j + 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(i + 1, j + 1));
					}
					cv::Vec3b color = find_inpaint_color(temp);
					Image.at<cv::Vec3b>(i, j) = color;
					input.at<cv::Vec3b>(i - 1, j - 1) = color;
					if (!temp.empty())
					{
						Label.at<uchar>(i, j) = 0;
					}
				}
			}
		}
		cols -= 1;
		rows -= 1;
		for (unsigned int x = rows; x > 0; --x)
		{
			for (unsigned int y = cols; y > 0; --y)
			{
				if (Label.at<uchar>(x, y) == 1)
				{
					std::vector<cv::Vec3b> temp;
					if (x - 1 != 0 && y - 1 != 0 && Label.at<uchar>(x - 1, y - 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(x - 1, y - 1));
					}
					if (x - 1 != 0 && Label.at<uchar>(x - 1, y) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(x - 1, y));
					}
					if (x - 1 != 0 && y != cols && Label.at<uchar>(x - 1, y + 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(x - 1, y + 1));
					}
					if (y - 1 != 0 && Label.at<uchar>(x, y - 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(x, y - 1));
					}
					if (y != cols && Label.at<uchar>(x, y + 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(x, y + 1));
					}
					if (x != rows && y - 1 != 0 && Label.at<uchar>(x + 1, y - 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(x + 1, y - 1));
					}
					if (x != rows && Label.at<uchar>(x + 1, y) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(x + 1, y));
					}
					if (x != rows && y != cols && Label.at<uchar>(x + 1, y + 1) != 1)
					{
						temp.push_back(Image.at<cv::Vec3b>(x + 1, y + 1));
					}
					cv::Vec3b color = find_inpaint_color(temp);
					Image.at<cv::Vec3b>(x, y) = color;
					input.at<cv::Vec3b>(x - 1, y - 1) = color;
					if (!temp.empty())
					{
						Label.at<uchar>(x, y) = 0;
					}
				}
			}
		}
	}
}

cv::Vec3b ImageTools::find_inpaint_color(std::vector<cv::Vec3b> examples) {
	int size = examples.size();
	if (size > 0)
	{
		int max = 0;
		int *temp = new int[size];
		for (int i = 0; i < size; ++i)
		{
			temp[i] = 0;
		}
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (examples[i] == examples[j])
				{
					++temp[j];
					goto con;
				}
			}
			++temp[i];
		con:
			continue;
		}
		for (int i = 1; i < size; ++i)
		{
			if (temp[i] > temp[max])
			{
				max = i;
			}
		}
		delete[] temp;
		return examples[max];
	}
	else
	{
		return cv::Vec3b(0, 0, 0);
	}
}

void ImageTools::get_extendImage(cv::Mat input, cv::Mat &output) {
	output.release();
	int rows = input.rows + 1, cols = input.cols + 1;
	output = cv::Mat(rows + 1, cols + 1, input.type(), cv::Scalar::all(0));
	if (input.type() == CV_8UC1)
	{
		for (int i = 1; i < rows; ++i)
		{
			for (int j = 1; j < cols; ++j)
			{
				output.at<uchar>(i, j) = input.at<uchar>(i - 1, j - 1);
			}
		}
	}
	if (input.type() == CV_8UC3)
	{
		for (int i = 1; i < rows; ++i)
		{
			for (int j = 1; j < cols; ++j)
			{
				output.at<cv::Vec3b>(i, j) = input.at<cv::Vec3b>(i - 1, j - 1);
			}
		}
	}
}

void ImageTools::L_balance(cv::Mat input, cv::Mat &output) {
	output.release();
	if (input.type() != CV_8UC3)
	{
		return;
	}
	unsigned int rows = input.rows;
	unsigned int cols = input.cols;
	cv::cvtColor(input, output, cv::COLOR_BGR2Luv);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			output.at<cv::Vec3b>(i, j)[0] = (output.at<cv::Vec3b>(i, j)[0] / 2) + 64;
		}
	}
	cv::cvtColor(output, output, cv::COLOR_Luv2BGR);
}

cv::Mat ImageTools::WDT(const cv::Mat &_src, const std::string _wname, const int _level) {
	cv::Mat src;
	if (_src.type() != CV_8UC1)
	{
		cv::cvtColor(_src, src, cv::COLOR_BGR2GRAY);
	}
	src = cv::Mat_<float>(src);
	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, src.type());
	int N = src.rows;
	int D = src.cols;

	// 高通低通滤波器
	cv::Mat lowFilter;
	cv::Mat highFilter;
	wavelet(_wname, lowFilter, highFilter);

	// 小波变换
	int t = 1;
	int row = N;
	int col = D;

	while (t <= _level)
	{
		//先进行行小波变换
		for (int i = 0; i < row; ++i)
		{
			// 取出src中要处理的数据的一行
			cv::Mat oneRow = cv::Mat::zeros(1, col, src.type());
			for (int j = 0; j < col; ++j)
			{
				oneRow.at<float>(0, j) = src.at<float>(i, j);
			}
			oneRow = waveletDecompose(oneRow, lowFilter, highFilter);
			// 将src这一行置为oneRow中的数据
			for (int j = 0; j < col; ++j)
			{
				dst.at<float>(i, j) = oneRow.at<float>(0, j);
			}
		}
		// 小波列变换
		for (int j = 0; j < col; ++j)
		{
			// 取出src数据的一行输入
			cv::Mat oneCol = cv::Mat::zeros(row, 1, src.type());
			for (int i = 0; i < row; ++i)
			{
				oneCol.at<float>(i, 0) = dst.at<float>(i, j);
			}
			oneCol = (waveletDecompose(oneCol.t(), lowFilter, highFilter)).t();
			for (int i = 0; i < row; ++i)
			{
				dst.at<float>(i, j) = oneCol.at<float>(i, 0);
			}
		}

		// 更新
		row /= 2;
		col /= 2;
		++t;
		src = dst;
	}
	return dst;
}

cv::Mat ImageTools::IWDT(const cv::Mat &_src, const std::string _wname, const int _level) {
	cv::Mat src = cv::Mat_<float>(_src);
	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, src.type());
	int N = src.rows;
	int D = src.cols;

	// 高通低通滤波器
	cv::Mat lowFilter;
	cv::Mat highFilter;
	wavelet(_wname, lowFilter, highFilter);

	// 小波变换
	int t = 1;
	int row = N / std::pow(2., _level - 1);
	int col = D / std::pow(2., _level - 1);

	while (row <= N && col <= D)
	{
		// 小波列逆变换
		for (int j = 0; j < col; j++)
		{
			// 取出src数据的一行输入
			cv::Mat oneCol = cv::Mat::zeros(row, 1, src.type());
			for (int i = 0; i < row; i++)
			{
				oneCol.at<float>(i, 0) = src.at<float>(i, j);
			}
			oneCol = waveletReconstruct(oneCol.t(), lowFilter, highFilter);

			for (int i = 0; i < row; i++)
			{
				dst.at<float>(i, j) = oneCol.at<float>(i, 0);
			}
		}

		//行小波逆变换
		for (int i = 0; i < row; i++)
		{
			// 取出src中要处理的数据的一行
			cv::Mat oneRow = cv::Mat::zeros(1, col, src.type());
			for (int j = 0; j < col; j++)
			{
				oneRow.at<float>(0, j) = dst.at<float>(i, j);
			}
			oneRow = waveletReconstruct(oneRow, lowFilter, highFilter);
			// 将src这一行置为oneRow中的数据
			for (int j = 0; j < col; j++)
			{
				dst.at<float>(i, j) = oneRow.at<float>(0, j);
			}
		}

		row *= 2;
		col *= 2;
		src = dst;
	}

	return dst;
}

void ImageTools::wavelet(const std::string _wname, cv::Mat &_lowFilter, cv::Mat &_highFilter)
{
	if (_wname == "haar" || _wname == "db1")
	{
		int N = 2;
		_lowFilter = cv::Mat::zeros(1, N, CV_32F);
		_highFilter = cv::Mat::zeros(1, N, CV_32F);

		_lowFilter.at<float>(0, 0) = 1 / sqrtf(N);
		_lowFilter.at<float>(0, 1) = 1 / sqrtf(N);

		_highFilter.at<float>(0, 0) = -1 / sqrtf(N);
		_highFilter.at<float>(0, 1) = 1 / sqrtf(N);
	}
	if (_wname == "sym2")
	{
		int N = 4;
		float h[] = { -0.483, 0.836, -0.224, -0.129 };
		float l[] = { -0.129, 0.224, 0.837, 0.483 };

		_lowFilter = cv::Mat::zeros(1, N, CV_32F);
		_highFilter = cv::Mat::zeros(1, N, CV_32F);

		for (int i = 0; i < N; i++)
		{
			_lowFilter.at<float>(0, i) = l[i];
			_highFilter.at<float>(0, i) = h[i];
		}
	}
}

cv::Mat ImageTools::waveletDecompose(const cv::Mat &_src, const cv::Mat &_lowFilter, const cv::Mat &_highFilter)
{
	assert(_src.rows == 1 && _lowFilter.rows == 1 && _highFilter.rows == 1);
	assert(_src.cols >= _lowFilter.cols && _src.cols >= _highFilter.cols);
	cv::Mat src = cv::Mat_<float>(_src);

	int D = src.cols;

	cv::Mat lowFilter = cv::Mat_<float>(_lowFilter);
	cv::Mat highFilter = cv::Mat_<float>(_highFilter);

	// 频域滤波，或时域卷积；ifft( fft(x) * fft(filter)) = cov(x,filter) 
	cv::Mat dst1 = cv::Mat::zeros(1, D, src.type());
	cv::Mat dst2 = cv::Mat::zeros(1, D, src.type());
	filter2D(src, dst1, -1, lowFilter);
	filter2D(src, dst2, -1, highFilter);

	// 下采样
	cv::Mat downDst1 = cv::Mat::zeros(1, D / 2, src.type());
	cv::Mat downDst2 = cv::Mat::zeros(1, D / 2, src.type());
	resize(dst1, downDst1, downDst1.size());
	resize(dst2, downDst2, downDst2.size());

	// 数据拼接
	for (int i = 0; i < D / 2; i++)
	{
		src.at<float>(0, i) = downDst1.at<float>(0, i);
		src.at<float>(0, i + D / 2) = downDst2.at<float>(0, i);
	}

	return src;
}

cv::Mat ImageTools::waveletReconstruct(const cv::Mat &_src, const cv::Mat &_lowFilter, const cv::Mat &_highFilter)
{
	assert(_src.rows == 1 && _lowFilter.rows == 1 && _highFilter.rows == 1);
	assert(_src.cols >= _lowFilter.cols && _src.cols >= _highFilter.cols);
	cv::Mat src = cv::Mat_<float>(_src);

	int D = src.cols;

	cv::Mat lowFilter = cv::Mat_<float>(_lowFilter);
	cv::Mat highFilter = cv::Mat_<float>(_highFilter);

	// 插值;
	cv::Mat Up1 = cv::Mat::zeros(1, D, src.type());
	cv::Mat Up2 = cv::Mat::zeros(1, D, src.type());

	/// 插值为0
	//for ( int i=0, cnt=1; i<D/2; i++,cnt+=2 )
	//{
	//    Up1.at<float>( 0, cnt ) = src.at<float>( 0, i );     ///< 前一半
	//    Up2.at<float>( 0, cnt ) = src.at<float>( 0, i+D/2 ); ///< 后一半
	//}

	// 线性插值
	cv::Mat roi1(src, cv::Rect(0, 0, D / 2, 1));
	cv::Mat roi2(src, cv::Rect(D / 2, 0, D / 2, 1));
	resize(roi1, Up1, Up1.size(), 0, 0, cv::INTER_CUBIC);
	resize(roi2, Up2, Up2.size(), 0, 0, cv::INTER_CUBIC);

	// 前一半低通，后一半高通
	cv::Mat dst1 = cv::Mat::zeros(1, D, src.type());
	cv::Mat dst2 = cv::Mat::zeros(1, D, src.type());
	filter2D(Up1, dst1, -1, lowFilter);
	filter2D(Up2, dst2, -1, highFilter);

	// 结果相加
	dst1 = dst1 + dst2;

	return dst1;
}

ImageTools::ImageTools()
{
}
