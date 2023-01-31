#ifndef __CMYLOADINGFUNC_H__
#define __CMYLOADINGFUNC_H__



#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

class CMyLoadingFunc
{
public:
	static CMyLoadingFunc* getInstance();
	void load_image(const std::string& strpath);
	void load_video(const std::string& strpath,int delay);
private:
	CMyLoadingFunc();
	static CMyLoadingFunc* p;
};



#endif // !__CMYLOADAINGFUNC_H__
