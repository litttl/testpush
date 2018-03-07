#ifndef _IMG_PROC_H
#define _IMG_PROC_H

#include <opencv2/opencv.hpp>
#include <iostream>

#include "file_io.h"


void get_lens_gain(const cv::Mat& img_ori, cv::Mat& gain_correct);

void correct_lens(const cv::Mat& img_ori, const cv::Mat& gain_correct, cv::Mat& img_correct);

int get_color(const cv::Mat& img_testbar, cv::Mat& img_rotate, cv::Mat& value_meanblock);

int get_color_imshow(const cv::Mat& img_testbar, const cv::Mat& ref_value_meanblock, cv::Mat& img_rotate, cv::Mat& value_meanblock);

int get_color_noout(const cv::Mat& img_testbar, cv::Mat& img_rotate, cv::Mat& value_meanblock);

#endif