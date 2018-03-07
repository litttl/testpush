/************************************/
//	file_name :	img_proc.cpp
//	function  :	get_lens_gain - 基于均光下采样校正对象，基于该图生成图像对应位置的增益map
//				correct_lens  - 对采样的测试图，进行lens shading校正
//				get_color     - 获取各色块均值，并输出保存处理的结果
//  class	  : none
/************************************/
//	version : 0 by fh - set up functions
//
/************************************/

#include "stdafx.h"
#include "img_proc.h"

// get_lens_gain: 获取整图校正中对应各点的增益值
void get_lens_gain(const cv::Mat& img_ori, cv::Mat& gain_correct)
{
	std::cout << ">>> Get len shading gain... ";
	cv::Mat _img_ori = img_ori.clone();
	_img_ori.convertTo(_img_ori, CV_32FC3);

	int rows_img = _img_ori.rows;
	int cols_img = _img_ori.cols;

// 计算中心亮度均值
	cv::Mat img_center = _img_ori(cv::Rect(rows_img/2-30,cols_img/2-30,60,60));
	cv::medianBlur(img_center, img_center, 5);
	cv::Scalar tmpval = cv::mean(img_center);
	float mean_center_b = tmpval.val[0];
	float mean_center_g = tmpval.val[1];
	float mean_center_r = tmpval.val[2];

// 计算增益map-(不考虑效率，暂不使用指针)
	cv::Mat gain_map(rows_img, cols_img, CV_32FC3);
	for (int i = 0; i < rows_img; i++)
	{
		for (int j = 0; j < cols_img; j++)
		{
			gain_map.at<cv::Vec3f>(i, j)[0] = mean_center_b / _img_ori.at<cv::Vec3f>(i, j)[0];
			gain_map.at<cv::Vec3f>(i, j)[1] = mean_center_g / _img_ori.at<cv::Vec3f>(i, j)[1];
			gain_map.at<cv::Vec3f>(i, j)[2] = mean_center_r / _img_ori.at<cv::Vec3f>(i, j)[2];
		}
	}

// 输出结果
	gain_correct = gain_map.clone();

	std::cout << "completed!" << std::endl;
}


// correct_lens: 进行LSC校正
void correct_lens(const cv::Mat& img_ori, const cv::Mat& gain_correct, cv::Mat& img_correct)
{
	std::cout << ">>> len shading correction ...";
	cv::Mat _img_ori = img_ori.clone();
	_img_ori.convertTo(_img_ori, CV_32FC3);

	int rows_img = _img_ori.rows;
	int cols_img = _img_ori.cols;

	cv::Mat _img_correct(_img_ori.size(), CV_32FC3);
	for (int i = 0; i < rows_img; i++)
	{
		for (int j = 0; j < cols_img; j++)
		{
			_img_correct.at<cv::Vec3f>(i, j)[0] = _img_ori.at<cv::Vec3f>(i, j)[0] * gain_correct.at<cv::Vec3f>(i, j)[0];
			_img_correct.at<cv::Vec3f>(i, j)[1] = _img_ori.at<cv::Vec3f>(i, j)[1] * gain_correct.at<cv::Vec3f>(i, j)[1];
			_img_correct.at<cv::Vec3f>(i, j)[2] = _img_ori.at<cv::Vec3f>(i, j)[2] * gain_correct.at<cv::Vec3f>(i, j)[2];
		}
	}
	_img_correct.convertTo(_img_correct, CV_8UC3);
	img_correct = _img_correct.clone();

	std::cout << " completed!" << std::endl;
}


// get_color: 获取色块的色彩均值，并输出处理结果的bmp和txt文本
int get_color(const cv::Mat& img_testbar, cv::Mat& img_rotate, cv::Mat& value_meanblock)
{
	std::cout << ">>> Get color block ...";

	cv::Mat _img_testbar = img_testbar;

	// 图像二值化
	cv::Mat gray_testbar, bit_testbar;
	cv::cvtColor(_img_testbar, gray_testbar, cv::COLOR_RGB2GRAY);
	cv::threshold(gray_testbar, bit_testbar, 40, 255, 0);


	// 形态学整形
	cv::Mat dila_testbar;
	int ele_size = 2;
	cv::Mat element1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * ele_size + 1, 2 * ele_size + 1), cv::Point(-1, -1));
	int ele_size2 = 4;
	cv::Mat element2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * ele_size2 + 1, 2 * ele_size2 + 1), cv::Point(-1, -1));
	dilate(bit_testbar, dila_testbar, element1);
	erode(dila_testbar, dila_testbar, element2);

	// canny检测边沿，提取标记黑块中心
	cv::Mat canny_testbar;
	cv::Canny(dila_testbar, canny_testbar, 50, 50 * 3, 3);
	std::vector<std::vector<cv::Point>> contours_testbar;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(canny_testbar, contours_testbar, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cv::Point(0, 0));
	std::vector<cv::Moments> mu(contours_testbar.size());
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		mu[i] = cv::moments(contours_testbar[i], false);
	}
	std::vector<cv::Point2f> mc(contours_testbar.size());
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		mc[i] = cv::Point2d(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		cv::circle(_img_testbar, mc[i], 1, cv::Scalar(50 * i, 255, 50 * i), 1, 8, 0);
	}

	if (contours_testbar.size() != 4)
	{
		return 0;
	}

	// 调整黑色标记块序号，以0-右下/1-左下/2-右上/3-左上为序号
	std::vector<cv::Point2f> mc_adjusted(contours_testbar.size());

	float tmp1 = 0.0, tmp2 = 0.0, tmp3 = 1280.0;
	int right1 = 0, right2 = 0, left1 = 0, left2 = 0;
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (mc[i].x>tmp1)
		{
			right1 = i;
			tmp1 = mc[i].x;
		}
	}

	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (i == right1){}
		else
		{

			if (mc[i].x>tmp2)
			{
				right2 = i;
				tmp2 = mc[i].x;
			}
		}
	}

	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (mc[i].x<tmp3)
		{
			left1 = i;
			tmp3 = mc[i].x;
		}
	}

	tmp3 = 1280.0;
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (i == left1){}
		else
		{

			if (mc[i].x<tmp3)
			{
				left2 = i;
				tmp3 = mc[i].x;
			}
		}
	}

	if (mc[right1].y > mc[right2].y)
	{
		mc_adjusted[0] = mc[right1];
		mc_adjusted[2] = mc[right2];
	}
	else
	{
		mc_adjusted[0] = mc[right2];
		mc_adjusted[2] = mc[right1];
	}

	if (mc[left1].y > mc[left2].y)
	{
		mc_adjusted[1] = mc[left1];
		mc_adjusted[3] = mc[left2];
	}
	else
	{
		mc_adjusted[1] = mc[left2];
		mc_adjusted[3] = mc[left1];
	}


	std::vector<cv::Point2f> mc_trans(4);
	mc_trans[3].x = 100; mc_trans[3].y = 300;
	mc_trans[2].x = 1100; mc_trans[2].y = 300;
	mc_trans[1].x = 100; mc_trans[1].y = 500;
	mc_trans[0].x = 1100; mc_trans[0].y = 500;

	cv::Mat mat_trans = cv::getPerspectiveTransform(mc_adjusted, mc_trans);

	cv::Mat img_trans, img_mean; // img_trans 用于并生成标点图片，img_mean 用于后续图像部分计算
	cv::warpPerspective(_img_testbar, img_trans, mat_trans, cv::Size(1280, 720));
	img_mean = img_trans.clone();

	// 依据黑色标记中心，计算各色块近似中心值
	std::vector<cv::Point2f> block_center(12);
	float dx = ((mc_trans[0].x - mc_trans[1].x) + (mc_trans[2].x - mc_trans[3].x)) / 2.0;
	float dy = ((mc_trans[1].y - mc_trans[3].y) + (mc_trans[0].y - mc_trans[2].y)) / 2.0;

	float ddx = ((mc_trans[3].x - mc_trans[1].x) + (mc_trans[2].x - mc_trans[0].x)) / 2.0;
	float ddy = ((mc_trans[0].y - mc_trans[1].y) + (mc_trans[2].y - mc_trans[3].y)) / 2.0;

	for (int i = 0; i < 6; i++)
	{
		block_center[i].x = mc_trans[1].x + (6.25 + 6.8 * i) / 46.0*dx;
		block_center[i].y = mc_trans[1].y - 1.5 / 8.5*dy;

		block_center[i + 6].x = mc_trans[1].x + (6.25 + 6.8 * i) / 46.0*dx;
		block_center[i + 6].y = mc_trans[3].y + 1.5 / 8.5*dy;

		cv::circle(img_trans, block_center[i], 1, cv::Scalar(0, 0, 0), 1, 8, 0);
		cv::circle(img_trans, block_center[i + 6], 1, cv::Scalar(0, 0, 0), 1, 8, 0);
	}

	// 计算图像各块均值
	cv::Mat value_roimean(12, 1, CV_32FC3);
	for (int i = 0; i < 12; i++)
	{
		cv::Mat roi_block = img_mean(cv::Rect(block_center[i].x - 15, block_center[i].y - 15, 30, 30));
		//		cv::Mat roi_block = img_mean(cv::Rect(block_center[i].x - 1, block_center[i].y - 1, 3, 3));
		cv::medianBlur(roi_block, roi_block, 5);
		cv::Scalar tmpval = cv::mean(roi_block);
		float mean_b = tmpval.val[0];
		float mean_g = tmpval.val[1];
		float mean_r = tmpval.val[2];

		value_roimean.at<cv::Vec3f>(i, 0)[0] = mean_b;
		value_roimean.at<cv::Vec3f>(i, 0)[1] = mean_g;
		value_roimean.at<cv::Vec3f>(i, 0)[2] = mean_r;

		//		std::cout << "here" << std::endl;
	}

	// 在保存图像中，添加各块获取的参考均值
	for (int i = 0; i < 12; i++)
	{
		std::vector<cv::Point2f> loca_puttext(3);
		loca_puttext[0] = block_center[i];
		loca_puttext[1].x = loca_puttext[0].x; loca_puttext[1].y = loca_puttext[0].y + 20;
		loca_puttext[2].x = loca_puttext[0].x; loca_puttext[2].y = loca_puttext[0].y + 40;

		cv::putText(img_trans, cv::format("%.2f", value_roimean.at<cv::Vec3f>(i, 0)[0]), loca_puttext[0], cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 2, 8, false);
		cv::putText(img_trans, cv::format("%.2f", value_roimean.at<cv::Vec3f>(i, 0)[1]), loca_puttext[1], cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2, 8, false);
		cv::putText(img_trans, cv::format("%.2f", value_roimean.at<cv::Vec3f>(i, 0)[2]), loca_puttext[2], cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2, 8, false);
	}

	// 数据存储部分
	std::string filename = "D:\\codes\\vc\\test\\test_opencv\\photos\\test.txt";

	for (int i = 0; i < 12; i++)
	{
		mattotxt(value_roimean, filename, i);
	}
	img_rotate = img_trans.clone();
	value_meanblock = value_roimean;
	std::cout << " completed!" << std::endl;
	return 1;
}


// get_color_noout: 获取色块的色彩均值，并输出处理结果的bmp和txt文本
int get_color_imshow(const cv::Mat& img_testbar, const cv::Mat& ref_value_meanblock,cv::Mat& img_rotate, cv::Mat& value_meanblock)
{
	std::cout << ">>> Get color block ...";

	cv::Mat _img_testbar = img_testbar;

	// 图像二值化
	cv::Mat gray_testbar, bit_testbar;
	cv::cvtColor(_img_testbar, gray_testbar, cv::COLOR_RGB2GRAY);
	cv::threshold(gray_testbar, bit_testbar, 40, 255, 0);


	// 形态学整形
	cv::Mat dila_testbar;
	int ele_size = 2;
	cv::Mat element1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * ele_size + 1, 2 * ele_size + 1), cv::Point(-1, -1));
	int ele_size2 = 4;
	cv::Mat element2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * ele_size2 + 1, 2 * ele_size2 + 1), cv::Point(-1, -1));
	dilate(bit_testbar, dila_testbar, element1);
	erode(dila_testbar, dila_testbar, element2);

	// canny检测边沿，提取标记黑块中心
	cv::Mat canny_testbar;
	cv::Canny(dila_testbar, canny_testbar, 50, 50 * 3, 3);
	std::vector<std::vector<cv::Point>> contours_testbar;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(canny_testbar, contours_testbar, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cv::Point(0, 0));
	std::vector<cv::Moments> mu(contours_testbar.size());
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		mu[i] = cv::moments(contours_testbar[i], false);
	}
	std::vector<cv::Point2f> mc(contours_testbar.size());
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		mc[i] = cv::Point2d(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		cv::circle(_img_testbar, mc[i], 1, cv::Scalar(50 * i, 255, 50 * i), 1, 8, 0);
	}

	if (contours_testbar.size() != 4)
	{
		cv::Mat img_tmp = cv::imread("D:\\codes\\vc\\check_color_mfc\\check_color_mfc\\check_color_mfc\\x64\\Release\\check_color_mfc.tlog\\nofig.bmp");
		img_rotate = img_tmp.clone();
		return 0;
	}

	// 调整黑色标记块序号，以0-右下/1-左下/2-右上/3-左上为序号
	std::vector<cv::Point2f> mc_adjusted(contours_testbar.size());

	float tmp1 = 0.0, tmp2 = 0.0, tmp3 = 1280.0;
	int right1 = 0, right2 = 0, left1 = 0, left2 = 0;
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (mc[i].x>tmp1)
		{
			right1 = i;
			tmp1 = mc[i].x;
		}
	}

	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (i == right1){}
		else
		{

			if (mc[i].x>tmp2)
			{
				right2 = i;
				tmp2 = mc[i].x;
			}
		}
	}

	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (mc[i].x<tmp3)
		{
			left1 = i;
			tmp3 = mc[i].x;
		}
	}

	tmp3 = 1280.0;
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (i == left1){}
		else
		{

			if (mc[i].x<tmp3)
			{
				left2 = i;
				tmp3 = mc[i].x;
			}
		}
	}

	if (mc[right1].y > mc[right2].y)
	{
		mc_adjusted[0] = mc[right1];
		mc_adjusted[2] = mc[right2];
	}
	else
	{
		mc_adjusted[0] = mc[right2];
		mc_adjusted[2] = mc[right1];
	}

	if (mc[left1].y > mc[left2].y)
	{
		mc_adjusted[1] = mc[left1];
		mc_adjusted[3] = mc[left2];
	}
	else
	{
		mc_adjusted[1] = mc[left2];
		mc_adjusted[3] = mc[left1];
	}


	std::vector<cv::Point2f> mc_trans(4);
	mc_trans[3].x = 100; mc_trans[3].y = 300;
	mc_trans[2].x = 1100; mc_trans[2].y = 300;
	mc_trans[1].x = 100; mc_trans[1].y = 500;
	mc_trans[0].x = 1100; mc_trans[0].y = 500;

	cv::Mat mat_trans = cv::getPerspectiveTransform(mc_adjusted, mc_trans);

	cv::Mat img_trans, img_mean; // img_trans 用于并生成标点图片，img_mean 用于后续图像部分计算
	cv::warpPerspective(_img_testbar, img_trans, mat_trans, cv::Size(1280, 720));
	img_mean = img_trans.clone();

	// 依据黑色标记中心，计算各色块近似中心值
	std::vector<cv::Point2f> block_center(12);
	float dx = ((mc_trans[0].x - mc_trans[1].x) + (mc_trans[2].x - mc_trans[3].x)) / 2.0;
	float dy = ((mc_trans[1].y - mc_trans[3].y) + (mc_trans[0].y - mc_trans[2].y)) / 2.0;

	float ddx = ((mc_trans[3].x - mc_trans[1].x) + (mc_trans[2].x - mc_trans[0].x)) / 2.0;
	float ddy = ((mc_trans[0].y - mc_trans[1].y) + (mc_trans[2].y - mc_trans[3].y)) / 2.0;

	for (int i = 0; i < 6; i++)
	{
		block_center[i].x = mc_trans[1].x + (6.25 + 6.8 * i) / 46.0*dx;
		block_center[i].y = mc_trans[1].y - 1.5 / 8.5*dy;

		block_center[i + 6].x = mc_trans[1].x + (6.25 + 6.8 * i) / 46.0*dx;
		block_center[i + 6].y = mc_trans[3].y + 1.5 / 8.5*dy;

		cv::circle(img_trans, block_center[i], 1, cv::Scalar(0, 0, 0), 1, 8, 0);
		cv::circle(img_trans, block_center[i + 6], 1, cv::Scalar(0, 0, 0), 1, 8, 0);
	}

	// 计算图像各块均值
	cv::Mat value_roimean(12, 1, CV_32FC3);
	for (int i = 0; i < 12; i++)
	{
		cv::Mat roi_block = img_mean(cv::Rect(block_center[i].x - 15, block_center[i].y - 15, 30, 30));
		//		cv::Mat roi_block = img_mean(cv::Rect(block_center[i].x - 1, block_center[i].y - 1, 3, 3));
		cv::medianBlur(roi_block, roi_block, 5);
		cv::Scalar tmpval = cv::mean(roi_block);
		float mean_b = tmpval.val[0];
		float mean_g = tmpval.val[1];
		float mean_r = tmpval.val[2];

		value_roimean.at<cv::Vec3f>(i, 0)[0] = mean_b;
		value_roimean.at<cv::Vec3f>(i, 0)[1] = mean_g;
		value_roimean.at<cv::Vec3f>(i, 0)[2] = mean_r;

		//		std::cout << "here" << std::endl;
	}

	// 在保存图像中，添加各块获取的参考均值
	for (int i = 0; i < 12; i++)
	{
		std::vector<cv::Point2f> loca_puttext(3);
		loca_puttext[0] = block_center[i];
		loca_puttext[1].x = loca_puttext[0].x; loca_puttext[1].y = loca_puttext[0].y + 20;
		loca_puttext[2].x = loca_puttext[0].x; loca_puttext[2].y = loca_puttext[0].y + 40;

		cv::putText(img_trans, cv::format("%.2f", value_roimean.at<cv::Vec3f>(i, 0)[0] - ref_value_meanblock.at<cv::Vec3f>(i, 0)[0]), loca_puttext[0], cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 2, 8, false);
		cv::putText(img_trans, cv::format("%.2f", value_roimean.at<cv::Vec3f>(i, 0)[1] - ref_value_meanblock.at<cv::Vec3f>(i, 0)[1]), loca_puttext[1], cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2, 8, false);
		cv::putText(img_trans, cv::format("%.2f", value_roimean.at<cv::Vec3f>(i, 0)[2] - ref_value_meanblock.at<cv::Vec3f>(i, 0)[2]), loca_puttext[2], cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2, 8, false);
	}

	img_rotate = img_trans.clone();
	value_meanblock = value_roimean;
	std::cout << " completed!" << std::endl;
	return 1;
}

// get_color: 获取色块的色彩均值，并输出处理结果的bmp和txt文本
int get_color_noout(const cv::Mat& img_testbar, cv::Mat& img_rotate, cv::Mat& value_meanblock)
{
	std::cout << ">>> Get color block ...";

	cv::Mat _img_testbar = img_testbar;

	// 图像二值化
	cv::Mat gray_testbar, bit_testbar;
	cv::cvtColor(_img_testbar, gray_testbar, cv::COLOR_RGB2GRAY);
	cv::threshold(gray_testbar, bit_testbar, 40, 255, 0);


	// 形态学整形
	cv::Mat dila_testbar;
	int ele_size = 2;
	cv::Mat element1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * ele_size + 1, 2 * ele_size + 1), cv::Point(-1, -1));
	int ele_size2 = 4;
	cv::Mat element2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * ele_size2 + 1, 2 * ele_size2 + 1), cv::Point(-1, -1));
	dilate(bit_testbar, dila_testbar, element1);
	erode(dila_testbar, dila_testbar, element2);

	// canny检测边沿，提取标记黑块中心
	cv::Mat canny_testbar;
	cv::Canny(dila_testbar, canny_testbar, 50, 50 * 3, 3);
	std::vector<std::vector<cv::Point>> contours_testbar;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(canny_testbar, contours_testbar, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cv::Point(0, 0));
	std::vector<cv::Moments> mu(contours_testbar.size());
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		mu[i] = cv::moments(contours_testbar[i], false);
	}
	std::vector<cv::Point2f> mc(contours_testbar.size());
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		mc[i] = cv::Point2d(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		cv::circle(_img_testbar, mc[i], 1, cv::Scalar(50 * i, 255, 50 * i), 1, 8, 0);
	}

	if (contours_testbar.size() != 4)
	{
		return 0;
	}

	// 调整黑色标记块序号，以0-右下/1-左下/2-右上/3-左上为序号
	std::vector<cv::Point2f> mc_adjusted(contours_testbar.size());

	float tmp1 = 0.0, tmp2 = 0.0, tmp3 = 1280.0;
	int right1 = 0, right2 = 0, left1 = 0, left2 = 0;
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (mc[i].x>tmp1)
		{
			right1 = i;
			tmp1 = mc[i].x;
		}
	}

	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (i == right1){}
		else
		{

			if (mc[i].x>tmp2)
			{
				right2 = i;
				tmp2 = mc[i].x;
			}
		}
	}

	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (mc[i].x<tmp3)
		{
			left1 = i;
			tmp3 = mc[i].x;
		}
	}

	tmp3 = 1280.0;
	for (int i = 0; i < contours_testbar.size(); i++)
	{
		if (i == left1){}
		else
		{

			if (mc[i].x<tmp3)
			{
				left2 = i;
				tmp3 = mc[i].x;
			}
		}
	}

	if (mc[right1].y > mc[right2].y)
	{
		mc_adjusted[0] = mc[right1];
		mc_adjusted[2] = mc[right2];
	}
	else
	{
		mc_adjusted[0] = mc[right2];
		mc_adjusted[2] = mc[right1];
	}

	if (mc[left1].y > mc[left2].y)
	{
		mc_adjusted[1] = mc[left1];
		mc_adjusted[3] = mc[left2];
	}
	else
	{
		mc_adjusted[1] = mc[left2];
		mc_adjusted[3] = mc[left1];
	}


	std::vector<cv::Point2f> mc_trans(4);
	mc_trans[3].x = 100; mc_trans[3].y = 300;
	mc_trans[2].x = 1100; mc_trans[2].y = 300;
	mc_trans[1].x = 100; mc_trans[1].y = 500;
	mc_trans[0].x = 1100; mc_trans[0].y = 500;

	cv::Mat mat_trans = cv::getPerspectiveTransform(mc_adjusted, mc_trans);

	cv::Mat img_trans, img_mean; // img_trans 用于并生成标点图片，img_mean 用于后续图像部分计算
	cv::warpPerspective(_img_testbar, img_trans, mat_trans, cv::Size(1280, 720));
	img_mean = img_trans.clone();

	// 依据黑色标记中心，计算各色块近似中心值
	std::vector<cv::Point2f> block_center(12);
	float dx = ((mc_trans[0].x - mc_trans[1].x) + (mc_trans[2].x - mc_trans[3].x)) / 2.0;
	float dy = ((mc_trans[1].y - mc_trans[3].y) + (mc_trans[0].y - mc_trans[2].y)) / 2.0;

	float ddx = ((mc_trans[3].x - mc_trans[1].x) + (mc_trans[2].x - mc_trans[0].x)) / 2.0;
	float ddy = ((mc_trans[0].y - mc_trans[1].y) + (mc_trans[2].y - mc_trans[3].y)) / 2.0;

	for (int i = 0; i < 6; i++)
	{
		block_center[i].x = mc_trans[1].x + (6.25 + 6.8 * i) / 46.0*dx;
		block_center[i].y = mc_trans[1].y - 1.5 / 8.5*dy;

		block_center[i + 6].x = mc_trans[1].x + (6.25 + 6.8 * i) / 46.0*dx;
		block_center[i + 6].y = mc_trans[3].y + 1.5 / 8.5*dy;

		cv::circle(img_trans, block_center[i], 1, cv::Scalar(0, 0, 0), 1, 8, 0);
		cv::circle(img_trans, block_center[i + 6], 1, cv::Scalar(0, 0, 0), 1, 8, 0);
	}

	// 计算图像各块均值
	cv::Mat value_roimean(12, 1, CV_32FC3);
	for (int i = 0; i < 12; i++)
	{
		cv::Mat roi_block = img_mean(cv::Rect(block_center[i].x - 15, block_center[i].y - 15, 30, 30));
		//		cv::Mat roi_block = img_mean(cv::Rect(block_center[i].x - 1, block_center[i].y - 1, 3, 3));
		cv::medianBlur(roi_block, roi_block, 5);
		cv::Scalar tmpval = cv::mean(roi_block);
		float mean_b = tmpval.val[0];
		float mean_g = tmpval.val[1];
		float mean_r = tmpval.val[2];

		value_roimean.at<cv::Vec3f>(i, 0)[0] = mean_b;
		value_roimean.at<cv::Vec3f>(i, 0)[1] = mean_g;
		value_roimean.at<cv::Vec3f>(i, 0)[2] = mean_r;

		//		std::cout << "here" << std::endl;
	}

	// 在保存图像中，添加各块获取的参考均值
	for (int i = 0; i < 12; i++)
	{
		std::vector<cv::Point2f> loca_puttext(3);
		loca_puttext[0] = block_center[i];
		loca_puttext[1].x = loca_puttext[0].x; loca_puttext[1].y = loca_puttext[0].y + 20;
		loca_puttext[2].x = loca_puttext[0].x; loca_puttext[2].y = loca_puttext[0].y + 40;

		cv::putText(img_trans, cv::format("%.2f", value_roimean.at<cv::Vec3f>(i, 0)[0]), loca_puttext[0], cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 2, 8, false);
		cv::putText(img_trans, cv::format("%.2f", value_roimean.at<cv::Vec3f>(i, 0)[1]), loca_puttext[1], cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2, 8, false);
		cv::putText(img_trans, cv::format("%.2f", value_roimean.at<cv::Vec3f>(i, 0)[2]), loca_puttext[2], cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2, 8, false);
	}

	// 数据存储部分
	//std::string filename = "D:\\codes\\vc\\test\\test_opencv\\photos1\\test.txt";

	//for (int i = 0; i < 12; i++)
	//{
	//	mattotxt(value_roimean, filename, i);
	//}
	//img_rotate = img_trans.clone();
	//value_meanblock = value_roimean;
	//std::cout << " completed!" << std::endl;


	// 
	img_rotate = img_trans.clone();
	value_meanblock = value_roimean;
	std::cout << " completed!" << std::endl;
	return 1;
}