#pragma once
#include "stdafx.h"

class __declspec(dllexport) ImageTools_Interface {
public:
	static bool get_ImageInfo(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());
	static bool get_GrayscaleImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());
	static bool get_FeatureImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat(), cv::Vec3b &threshold = cv::Vec3b());
	static bool get_BinaryImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());

	static bool get_Features(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());

	static void particl_Segment(const cv::Mat inputImage_source, const cv::Mat inputImage_reference, cv::Mat &outputLabel, cv::Vec3b &out_color, unsigned int R_Threshold, unsigned int G_Threshold, unsigned int B_Threshold, unsigned part_BGR);
	static std::vector<cv::Mat> Segment(const cv::Mat image, const cv::Mat image_reference, unsigned int R_Threshold, unsigned int G_Threshold, unsigned int B_Threshold);
	static void remove_dot(cv::Mat inputImage, cv::Mat &outputImage, unsigned int min_area = -1);//ȥС��
	static void integrate_Image(cv::Mat &output, std::vector<cv::Mat> &outputs);//ƴ��ͼ��
	static void my_inpaint(cv::Mat &input, cv::Mat &mask);//�޸�ͼ��

private:
	ImageTools_Interface();
};

class ImageTools {
public:
	ImageTools();
	static bool get_ImageInfo(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());
	static bool get_GrayscaleImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());
	static bool get_FeatureImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat(), cv::Vec3b &threshold = cv::Vec3b());
	static bool get_BinaryImage(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());

	static bool get_Features(cv::Mat input, cv::Mat &output, QString &out_text, cv::Mat &out_img = cv::Mat());

	static void particl_Segment(const cv::Mat inputImage_source, const cv::Mat inputImage_reference, cv::Mat &outputLabel, cv::Vec3b &out_color, unsigned int R_Threshold, unsigned int G_Threshold, unsigned int B_Threshold, unsigned part_BGR);
	static std::vector<cv::Mat> Segment(const cv::Mat image, const cv::Mat image_reference, unsigned int R_Threshold, unsigned int G_Threshold, unsigned int B_Threshold);
	static void remove_dot(cv::Mat inputImage, cv::Mat &outputImage, unsigned int min_area = -1);//ȥС��
	static void integrate_Image(cv::Mat &output, std::vector<cv::Mat> &outputs);//ƴ��ͼ��
	static void my_inpaint(cv::Mat &input, cv::Mat &mask);//�޸�ͼ��
	static std::vector<double> get_HuMoments(cv::Mat input);	//����Hu�����

	static unsigned int Otsu_Threshold(cv::Mat temp, unsigned int min_Variance = 0);
	static unsigned int Get_Channle_Threshold(cv::Mat image, unsigned int channel, unsigned int min_Variance = 0);

	static cv::Vec3b find_inpaint_color(std::vector<cv::Vec3b> examples);
	static void get_extendImage(cv::Mat input, cv::Mat &output);//����������һȦ
	static void L_balance(cv::Mat input, cv::Mat &output);//���Ⱦ���

	static cv::Mat WDT(const cv::Mat &_src, const std::string _wname, const int _level = 1);	//С���任
	static cv::Mat IWDT(const cv::Mat &_src, const std::string _wname, const int _level = 1);	//С����任
	static void wavelet(const std::string _wname, cv::Mat &_lowFilter, cv::Mat &_highFilter);	//���ɲ�ͬ���͵�С��
	static cv::Mat waveletDecompose(const cv::Mat &_src, const cv::Mat &_lowFilter, const cv::Mat &_highFilter);	//С���ֽ�
	static cv::Mat waveletReconstruct(const cv::Mat &_src, const cv::Mat &_lowFilter, const cv::Mat &_highFilter);	//С���ؽ�
};
