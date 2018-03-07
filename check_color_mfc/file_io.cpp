/************************************/
//	file_name :	file_io.cpp
//	function  :	mattoexcel	- mat数据写入excel中
//				mattotxt	- mat数据写成json 格式，保存在txt中
//				mattobmp	- mat数据写成bmp图片，图片名保留获取日期
//	class	  : none
/************************************/
//	version : 0 by fh - set up functions
//
/************************************/


#include "file_io.h"
#include "stdafx.h"

// mat数据写入excel中
void mattoexcel(const cv::Mat& img_write, std::string filename)
{
	std::ofstream Fs(filename);
	if (!Fs.is_open())
	{
		std::cout << "error to open excelfile!" << std::endl;
		return;
	}

	int channels = img_write.channels();
	int imgrows = img_write.rows;
	int imgcols = img_write.cols*channels;

	for (int i = 0; i < imgrows; i++)
	{
		for (int j = 0; j < imgcols; j++)
		{
			Fs << (float)img_write.ptr<float>(i)[j] << '\t';
		}
		Fs << std::endl;
	}

	Fs.close();
}

// mat数据写成json 格式，保存在txt中
void mattotxt(const cv::Mat& img_write, std::string filename, int no_block)
{
	std::cout << "---> mat save as json... ";
	std::ofstream Fs(filename, std::ios::app);
	if (!Fs.is_open())
	{
		std::cout << "error to open txt!" << std::endl;
		return;
	}

	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	char char_phno[64];
	sprintf_s(char_phno, "gettime:%d%02d%02d%02d%02d%02d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	std::string str_jsonstart = "[\n", str_jsonend = "\n]\n";
	std::string str_objstart = "{", str_objend = "}", str_objmid = "},";
	char str_coment[64];
	sprintf_s(str_coment, "\"index\":\"%d_%d\",\"color\":[%.2f,%.2f,%.2f]", no_block / 6, no_block % 6, img_write.at<cv::Vec3f>(no_block, 0)[0], img_write.at<cv::Vec3f>(no_block, 0)[1], img_write.at<cv::Vec3f>(no_block, 0)[2]);
	std::string str_outtofile;

	if (no_block == 0)
	{
		str_outtofile = char_phno + str_jsonstart + str_objstart + str_coment + str_objmid;
	}
	else if (no_block == 11)
	{
		str_outtofile = str_objstart + str_coment + str_objend + str_jsonend;
	}
	else
	{
		str_outtofile = str_objstart + str_coment + str_objmid;
	}
	Fs << str_outtofile << '\n';

	Fs.close();
	std::cout << "completed!" << std::endl;
}


// mat数据写成bmp图片，图片名保留获取日期
void mattobmp(const cv::Mat& img_write, std::string file_road)
{
	std::cout << "---> mat save as bmp... ";
	std::string file_style = ".bmp";
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	char char_phno[64];
	sprintf_s(char_phno, "%d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	cv::imwrite(file_road+char_phno+file_style,img_write);
	std::cout << "completed!" << std::endl;

}


