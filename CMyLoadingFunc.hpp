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
	double forward_x;	//ǰ�� x
	double forward_y;
	double scaled_x;	//ѡȡ�����С
	double scaled_y;
}RectIreaStruct;

class CMyLoadingFunc
{
	//��ʾͼƬ����
public:
	static CMyLoadingFunc* getInstance();
	void load_image(const std::string& strpath);
	void load_video(const std::string& strpath,int delay);
	void load_camera(int camera_id = 0);	//Ĭ��Ϊ0��ֹ����Խ��
	cv::Mat resize_image(cv::Mat& img, cv::Size sizetemp);	//ָ����С����
	cv::Mat resize_image(cv::Mat& img, double fx,double fy);	//��������
	cv::Mat crop_image(const cv::Mat& img, RectIreaStruct RectSize);		//ͼ��ü�
public:
	//��άԪ�صĻ���
	void drawSLine(cv::Mat& img, cv::Point p, const int Hor_position,cv::Scalar rgb, int pix_wide, bool ishorizontal = true);	//ֱ��,Ĭ��ˮƽ��

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
	void facedetachDemo(void);	//��̬ͼƬʶ��
	void ActualFaceDetachDemo(int camera_id);	//����ͷʵʱ���
	void virtualpainter(int camera_id);
};



#endif // !__CMYLOADAINGFUNC_H__
