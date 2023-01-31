#ifndef _CMYLOADINGFUNC_H_
#define _CMYLOADINGFUNC_H_

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <string>
#include <Windows.h>

typedef struct RectIreaStruct {
	double forward_x;	//前进 x
	double forward_y;
	double scaled_x;	//选取区域大小
	double scaled_y;
}RectIreaStruct;

class CMyLoadingFunc
{
	//显示图片加载
public:
	static CMyLoadingFunc* getInstance();
	void load_image(const std::string& strpath);
	void load_video(const std::string& strpath,int delay);
	void load_camera(int camera_id = 0);	//默认为0防止数组越界
	cv::Mat resize_image(cv::Mat& img, cv::Size sizetemp);	//指定大小缩放
	cv::Mat resize_image(cv::Mat& img, double fx,double fy);	//比例缩放
	cv::Mat crop_image(const cv::Mat& img, RectIreaStruct RectSize);		//图像裁剪
public:
	//二维元素的绘制
	void drawSLine(cv::Mat& img, cv::Point p, const int Hor_position,cv::Scalar rgb, int pix_wide, bool ishorizontal = true);	//直线,默认水平线

private:
	CMyLoadingFunc() {}
	static CMyLoadingFunc* p;
};


namespace demo {
	void BlankImageDemo(void);
	void imageDemoFunc(void);
	void warpImageDemo(void);


	void colordetachDemo(void);
	void ActualColorDetach(int camera_id);
	
	void shadedetachDemo(void);
	void facedetachDemo(void);	//静态图片识别
	void ActualFaceDetachDemo(int camera_id);	//摄像头实时检测
	void virtualpainter(int camera_id);
};



#endif // !__CMYLOADAINGFUNC_H__
