#ifndef _FILE_IO_H
#define _FILE_IO_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>

void mattoexcel(const cv::Mat& img_write, std::string filename);
void mattotxt(const cv::Mat& img_write, std::string filename, int no_block);
void mattobmp(const cv::Mat& img_write, std::string file_road);

#endif