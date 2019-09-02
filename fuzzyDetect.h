#pragma once
#ifdef DLL_API
#else
#define DLL_API_declspec(dllexport)
#endif
#include <opencv2/opencv.hpp>
#include<string>
/*读取kfb格式图像的roi*/
cv::Mat readRoi(std::string path, int roi_start_x, int roi_start_y, int roi_width, int roi_height);
/*显示roi*/
void show(std::string winName, cv::Mat image);
/*拉普拉斯方法算方差*/
double isImageValid(cv::Mat img)
