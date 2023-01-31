#include "CMyLoadingFunc.hpp"

using namespace cv;
using namespace std;
CMyLoadingFunc* CMyLoadingFunc::p = nullptr;

CMyLoadingFunc* CMyLoadingFunc::getInstance()
{
	if (p == nullptr)
		p = new CMyLoadingFunc;

	return p;
}

void CMyLoadingFunc::load_image(const std::string& strpath)
{
	
	cv::Mat img = imread(strpath);  //matrix矩阵
	imshow("Image", img);
	waitKey(0);

}

void CMyLoadingFunc::load_video(const std::string& strpath,int delay)
{
	VideoCapture cap(strpath);
	Mat img;
	while (true)
	{
		cap.read(img);
		imshow("Image", img);
		waitKey(delay);
	}
	
	
	return;
}

void CMyLoadingFunc::load_camera(int camera_id)
{
	VideoCapture cap(camera_id);
	Mat img;

	while (true)
	{
		cap.read(img);
		imshow("Image", img);
		waitKey(1);
	}

}

cv::Mat CMyLoadingFunc::resize_image(cv::Mat& img, cv::Size sizetemp)
{
	Mat imgResize;

	cv::resize(img, imgResize, sizetemp);
	return imgResize;
}

cv::Mat CMyLoadingFunc::resize_image(cv::Mat& img, double fx, double fy)
{
	Mat imgResize;

	cv::resize(img, imgResize, cv::Size(), fx, fy);
	return imgResize;
}

cv::Mat CMyLoadingFunc::crop_image(const cv::Mat& img, RectIreaStruct RectSize)
{
	Mat ret_img;
	Rect roi(RectSize.forward_x, RectSize.forward_y, RectSize.scaled_x, RectSize.scaled_y);
	ret_img = img(roi);

	return ret_img;
}

void CMyLoadingFunc::drawSLine(cv::Mat& img, cv::Point p,const int Hor_position,Scalar rgb,int pix_wide, bool ishorizontal)
{
	Point firstPix;
	Point secondPix;

	if (ishorizontal)
	{
		firstPix.y = secondPix.y = Hor_position;
		firstPix.x = p.x;
		secondPix.x = p.y;
	}
	else {
		firstPix.x = secondPix.x = Hor_position;
		firstPix.y = p.x;
		secondPix.y = p.y;
	}

	
	line(img,firstPix,secondPix,rgb,pix_wide);

}


void demo::BlankImageDemo(void)
{
    using namespace cv;
   

    //CV_8UC3 unsigned channel 3 = RGB
    //背景图的制作
    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));    //rgb每个都是2的8次


    //point是为了确定圆心的位置,radius 155是半径
    //circle(img, Point(256, 256), 155, Scalar(0,135,255),10);    //画圆，圆的颜色，10是厚度
    circle(img, Point(256, 256), 155, Scalar(0, 0, 10), FILLED); //实心圆
    //imshow("Image crop", img);

    //矩形
    //rectangle(img, Point(130, 226), Point(382,286), Scalar(255,255,255), 3);
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);


    //直线
    line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

    putText(img, "test string", Point(137, 162), FONT_HERSHEY_DUPLEX, 2, Scalar(0, 69, 255), 2);



    //staticUsage
    //CMyLoadingFunc::getInstance()->drawSLine(img,Point(328,603),200,Scalar(0,63,28),3,false);

    string str = __FUNCTION__;
    imshow(str, img); //图层不断叠加
    waitKey(0);
}

void demo::imageDemoFunc(void)
{
    using namespace cv;
    using namespace std;
    string path = "Resources/pic/sb.jpg";
    cv::Mat img = imread(path);  //matrix矩阵
    cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(3, 3), 5, 0);
    Canny(imgBlur, imgCanny, 50, 150);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgCanny, imgDil, kernel);

    erode(imgDil, imgErode, kernel);

    imshow("Image", img);
    imshow("Image Gray", imgGray);    //灰度图像
    imshow("Image blur", imgBlur);      //模糊处理
    imshow("Image Canny", imgCanny);  //轮廓
    imshow("Image Dilation", imgDil); //轮廓
    imshow("Image Erode", imgErode);    //轮廓
    waitKey(0);
}


//扭曲图像的投影转换
void demo::warpImageDemo(void)
{
    using namespace cv;
    using namespace std;
    string path = "Resources/pic/joker.jpg";
    cv::Mat img = imread(path);  //matrix矩阵

    Point2f joker_j[4] = { {779,108},{1017,82},{845,354},{1113,331} };
    Point2f joker_k[4] = { {528,144},{767,189},{408,395}, {671,457} };


    float w = 250, h = 350;
    Point2f joker_j_dest[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
    cv::Mat matrix, imgwarp;

    //透视变换/投影变换
    matrix = getPerspectiveTransform(joker_j, joker_j_dest);
    warpPerspective(img, imgwarp, matrix, Point(w, h));//

    for (int i = 0; i < 4; ++i)
    {
        circle(img, joker_j[i], 10, Scalar(0, 0, 255), FILLED);    //从原图中圈出所选择的基准点s
    }

    imshow("Image", img);
    imshow("Image warp", imgwarp);
    waitKey(0);
}

void demo::colordetachDemo(void)
{
    using namespace cv;
    using namespace std;

    int hmin = 0, smin = 110, vmin = 153;
    int hmax = 19, smax = 240, vmax = 255;
    string path = "Resources/pic/shade.jpeg";
    cv::Mat img = imread(path);  //matrix矩阵
    cv::Mat imgHSV,mask;

    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    
    namedWindow("TrackBars", (640, 200));
    createTrackbar("Hue Min", "TrackBars", &hmin, 255);
    createTrackbar("Hue Max", "TrackBars", &hmax, 255);
    createTrackbar("sat Min", "TrackBars", &smin, 255);
    createTrackbar("sat Max", "TrackBars", &smax, 255);
    createTrackbar("val Min", "TrackBars", &vmin, 255);
    createTrackbar("val Max", "TrackBars", &vmax, 255);
    while (true)
    {
        Scalar lower(hmin, smin, vmin); //色相最小值，饱和度最小值,明度
        Scalar upper(hmax, smax, vmax);

        inRange(imgHSV, lower, upper, mask);  //筛选出你需要的颜色的一个范围
        imshow("Image", img);
        imshow("ImageHSV", imgHSV);
        imshow("mask", mask);
        waitKey(1);
    }
    

}

void demo::ActualColorDetach(int camera_id)
{

    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;
    
    VideoCapture cap(0);
    Mat img;

    cv::Mat imgHSV, mask, imgColor;

    namedWindow("TrackBars", (640, 200));
    createTrackbar("Hue Min", "TrackBars", &hmin, 255);
    createTrackbar("Hue Max", "TrackBars", &hmax, 255);
    createTrackbar("sat Min", "TrackBars", &smin, 255);
    createTrackbar("sat Max", "TrackBars", &smax, 255);
    createTrackbar("val Min", "TrackBars", &vmin, 255);
    createTrackbar("val Max", "TrackBars", &vmax, 255);

    while (true)
    {
        cap.read(img);

        cvtColor(img, imgHSV, COLOR_BGR2HSV);

        Scalar lower(hmin, smin, vmin); //色相最小值，饱和度最小值,明度
        Scalar upper(hmax, smax, vmax);

        inRange(imgHSV, lower, upper, mask);  //筛选出你需要的颜色的一个范围
        imshow("Image", img);
        imshow("ImageHSV", imgHSV);
        imshow("mask", mask);
        waitKey(1);
    }

}

void demo::shadedetachDemo(void)
{
    //Canny usage: 前提是先进行高斯模糊
    using namespace cv;
    using namespace std;
    string path = "Resources/pic/shade.jpeg";
    cv::Mat img = imread(path);  //matrix矩阵
    cv::Mat imgGray, imgBlur, imgCanny, imgDil;
    string objectType;
    auto getContours = [&] {
        //捕获Dil膨胀和原始img
        
        //图片包含了好几个contour，每一个contour又包含了很多点
        vector<vector<Point>>contours; 
        vector<Vec4i>hierarchy; //层级
        

        findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
        
        vector<vector<Point>>conPoly(contours.size());
        vector<Rect> boundRect(contours.size());
        //遍历所有轮廓，筛选出噪音
        for (int i = 0; i < contours.size(); ++i)
        {
            auto area = contourArea(contours[i]);
            cout << area << endl;
            if (area > 1000)    //最小的过滤范围
            {
                auto peri = arcLength(contours[i], true);
                //approxPolyDP()函数是opencv中对指定的点集进行多边形逼近的函数，其逼近的精度可通过参数设置。
                //第三个参数double epsilon：指定的精度，也即是原始曲线与近似曲线之间的最大距离。第三个参数double epsilon：指定的精度，也即是原始曲线与近似曲线之间的最大距离。
                //第四个参数bool closed：若为true，则说明近似曲线是闭合的；反之，若为false，则断开
                //这个是计算每个轮廓的周长 再次用一个方法估计轮廓点的个数，但是规则就是以轮廓的周长*0.02判定的 应该是这样吧=-=
                approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
                
                cout << conPoly[i].size() << endl;
                
                //根据轮廓画矩形
                boundRect[i] = boundingRect(conPoly[i]);
                

                int objCor = (int)conPoly[i].size();
                switch (objCor)
                {
                case 3:
                    objectType = "Tri";
                    break;
                case 4:
                {
                    float aspRadio = (float)boundRect[i].width / (float)boundRect[i].height;
                    cout << aspRadio << endl;
                    if (aspRadio > 0.95 && aspRadio < 1.05) { objectType = "Square"; }
                    else { objectType = "Rect"; }

                    objectType = "Rect";
                }
                    
                    break;
                default:
                    objectType = "Circle";
                    break;
                }
				drawContours(img, conPoly, i, Scalar(255, 0, 255), 6);
				rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

				putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0,69,255),1);
            }
        }
    };

    
    //preprocessing
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 5, 0);
    Canny(imgBlur, imgCanny, 50, 150);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgCanny, imgDil, kernel);

    getContours();


    imshow("Image", img); //此时原始图像上的轮廓已被勾勒出
    //imshow("Image Gray", imgGray);    //灰度图像
    //imshow("Image blur", imgBlur);      //模糊处理
    //imshow("Image Canny", imgCanny);  //轮廓
    //imshow("Image Dilation", imgDil); //轮廓
}

void demo::facedetachDemo(void)
{
    string path = "Resources/pic/bjarny.jpeg";
    Mat img = imread(path);

    CascadeClassifier faceCascade;
    //可自行更换haarcascades_cuda文件夹/CUDA主要争对NVIDIA的显卡
    faceCascade.load("Resources/data/haarcascades_cuda/haarcascade_frontalface_default.xml");

    if (faceCascade.empty())
        cout << "XML file not loaded" << endl;

    //创建面部的矩形向量
    vector<Rect>faces;
    faceCascade.detectMultiScale(img, faces,1.1,10);    //1.1是比例因子,10是相邻矩形的最小间隔
    
    //检测到所有的faces后遍历
    for (int iLoop = 0; iLoop < faces.size(); ++iLoop)
    {
        rectangle(img, faces[iLoop].tl(), faces[iLoop].br(), Scalar(255, 0, 255), 3);
        putText(img, to_string(iLoop), faces[iLoop].tl(), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 69, 255), 2);
    }
    
    imshow("Image", img);
    waitKey(0);
}

void demo::ActualFaceDetachDemo(int camera_id)
{
    VideoCapture cap(camera_id);
    Mat img;

    while (true)
    {
        cap.read(img);

        CascadeClassifier faceCascade;
        //可自行更换haarcascades_cuda文件夹/CUDA主要争对NVIDIA的显卡
        faceCascade.load("Resources/data/haarcascades/haarcascade_frontalface_default.xml");

        if (faceCascade.empty())
            cout << "XML file not loaded" << endl;

        //创建面部的矩形向量
        vector<Rect>faces;
        faceCascade.detectMultiScale(img, faces, 1.1, 10);    //1.1是比例因子,10是相邻矩形的最小间隔
        //检测到所有的faces后遍历
        for (int iLoop = 0; iLoop < faces.size(); ++iLoop)
        {
            rectangle(img, faces[iLoop].tl(), faces[iLoop].br(), Scalar(255, 0, 255), 3);
            putText(img, to_string(iLoop), faces[iLoop].tl(), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 69, 255), 2);
            imshow("Image", img);
        }


        imshow("Image", img);
        waitKey(1);
    }
        
    
}

void demo::virtualpainter(int camera_id)
{
    

    VideoCapture cap(camera_id);
    Mat img;

    while (true)
    {
        cap.read(img);
        //findColor(img);
        imshow("Image", img);
        waitKey(1);
    }
}
