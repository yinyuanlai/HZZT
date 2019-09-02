#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <kfbreader_Dll.h>
using namespace std;
using namespace cv;
//读取kfb格式图像的roi
cv::Mat readRoi(std::string path,int roi_start_x, int roi_start_y,int roi_width,int roi_height)
{
	int w = 0, h = 0, scale = 10; //scale 放大倍数

	kfbreader reader;
	reader.ReadInfo(path, scale, w, h, 1);
	unsigned char *data = nullptr;
	reader.ReadRoi(roi_start_x, roi_start_y, roi_width,roi_height,scale, &data);

	Mat ROI(roi_width, roi_height, CV_8UC3, data);
	return ROI;
}

//显示ROI
void show(string winName,Mat image)
{
	imshow(winName,image);
	waitKey(0);
}

//laplacian
double isImageBlurry(cv::Mat img)
{
	cv::Mat matImageGray;
	cv::cvtColor(img, matImageGray, CV_BGR2GRAY);

	cv::Mat dst;
	cv::Laplacian(matImageGray, dst, CV_16S, 3);//3是高斯核大小

	cv::Mat tmp_m, tmp_sd; //均值  标准差
	cv::meanStdDev(dst, tmp_m, tmp_sd);
	double m = 0, sd = 0;
	m = tmp_m.at<double>(0, 0);
	sd = tmp_sd.at<double>(0, 0);

	int threshold = 900; //设置阈值 

	std::string result = (sd * sd > threshold) ? "清晰" : "模糊";
	std::cout << "Score: " << int(sd * sd) <<"\t"<<"结果："<<result <<std::endl;
	return sd * sd;
}

/*将检测模糊的视野画红框，清晰的视野画绿框*/
void drawBox(cv::Mat &img) 
{
	cv::Rect rect(0, 0, 2048, 2048);
	cv::rectangle(img, rect, cv::Scalar(0, 255, 0), 8, LINE_8, 0);
}

int main(void)
{
	std::string path = "E:/kfb/bad/5.kfb";
	
	//获取中间ROI start_x = 0,start_y=15000 height=2000,width=32000
	kfbreader kfb;
	int w = 0, h = 0;
	kfb.ReadInfo(path, 10, w, h, 1);

	double num = w / 2048; //视野个数 
	cout << "图像大小：" << w << "*" << h << endl;
	cout << "选取视野个数：" << " " << num << endl;

	clock_t startTime; //程序开始执行时间
	clock_t endTime;   //程序执行完的时间
	double costTime;   //识别程序耗时

	startTime = clock();
	for (int i = 0;i < num;i++)
	{
		cv::Mat roi = readRoi(path, i * 2048, w / 2 - 1024, 2048, 2048); //path,x,y,w,h
		double score = isImageBlurry(roi);
	}
	endTime = clock();

	costTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	cout << "识别程序用时：" << costTime << "s" << endl;
	cout << "每个视野识别用时：" << costTime / num * 1000 << "ms" << endl;

}



