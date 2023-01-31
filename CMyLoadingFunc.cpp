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
	
	cv::Mat img = imread(strpath);  //matrix����
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
    //����ͼ������
    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));    //rgbÿ������2��8��


    //point��Ϊ��ȷ��Բ�ĵ�λ��,radius 155�ǰ뾶
    //circle(img, Point(256, 256), 155, Scalar(0,135,255),10);    //��Բ��Բ����ɫ��10�Ǻ��
    circle(img, Point(256, 256), 155, Scalar(0, 0, 10), FILLED); //ʵ��Բ
    //imshow("Image crop", img);

    //����
    //rectangle(img, Point(130, 226), Point(382,286), Scalar(255,255,255), 3);
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);


    //ֱ��
    line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

    putText(img, "test string", Point(137, 162), FONT_HERSHEY_DUPLEX, 2, Scalar(0, 69, 255), 2);



    //staticUsage
    //CMyLoadingFunc::getInstance()->drawSLine(img,Point(328,603),200,Scalar(0,63,28),3,false);

    string str = __FUNCTION__;
    imshow(str, img); //ͼ�㲻�ϵ���
    waitKey(0);
}

void demo::imageDemoFunc(void)
{
    using namespace cv;
    using namespace std;
    string path = "Resources/pic/sb.jpg";
    cv::Mat img = imread(path);  //matrix����
    cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(3, 3), 5, 0);
    Canny(imgBlur, imgCanny, 50, 150);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgCanny, imgDil, kernel);

    erode(imgDil, imgErode, kernel);

    imshow("Image", img);
    imshow("Image Gray", imgGray);    //�Ҷ�ͼ��
    imshow("Image blur", imgBlur);      //ģ������
    imshow("Image Canny", imgCanny);  //����
    imshow("Image Dilation", imgDil); //����
    imshow("Image Erode", imgErode);    //����
    waitKey(0);
}


//Ť��ͼ���ͶӰת��
void demo::warpImageDemo(void)
{
    using namespace cv;
    using namespace std;
    string path = "Resources/pic/joker.jpg";
    cv::Mat img = imread(path);  //matrix����

    Point2f joker_j[4] = { {779,108},{1017,82},{845,354},{1113,331} };
    Point2f joker_k[4] = { {528,144},{767,189},{408,395}, {671,457} };


    float w = 250, h = 350;
    Point2f joker_j_dest[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
    cv::Mat matrix, imgwarp;

    //͸�ӱ任/ͶӰ�任
    matrix = getPerspectiveTransform(joker_j, joker_j_dest);
    warpPerspective(img, imgwarp, matrix, Point(w, h));//

    for (int i = 0; i < 4; ++i)
    {
        circle(img, joker_j[i], 10, Scalar(0, 0, 255), FILLED);    //��ԭͼ��Ȧ����ѡ��Ļ�׼��s
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
    cv::Mat img = imread(path);  //matrix����
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
        Scalar lower(hmin, smin, vmin); //ɫ����Сֵ�����Ͷ���Сֵ,����
        Scalar upper(hmax, smax, vmax);

        inRange(imgHSV, lower, upper, mask);  //ɸѡ������Ҫ����ɫ��һ����Χ
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

        Scalar lower(hmin, smin, vmin); //ɫ����Сֵ�����Ͷ���Сֵ,����
        Scalar upper(hmax, smax, vmax);

        inRange(imgHSV, lower, upper, mask);  //ɸѡ������Ҫ����ɫ��һ����Χ
        imshow("Image", img);
        imshow("ImageHSV", imgHSV);
        imshow("mask", mask);
        waitKey(1);
    }

}

void demo::shadedetachDemo(void)
{
    //Canny usage: ǰ�����Ƚ��и�˹ģ��
    using namespace cv;
    using namespace std;
    string path = "Resources/pic/shade.jpeg";
    cv::Mat img = imread(path);  //matrix����
    cv::Mat imgGray, imgBlur, imgCanny, imgDil;
    string objectType;
    auto getContours = [&] {
        //����Dil���ͺ�ԭʼimg
        
        //ͼƬ�����˺ü���contour��ÿһ��contour�ְ����˺ܶ��
        vector<vector<Point>>contours; 
        vector<Vec4i>hierarchy; //�㼶
        

        findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
        
        vector<vector<Point>>conPoly(contours.size());
        vector<Rect> boundRect(contours.size());
        //��������������ɸѡ������
        for (int i = 0; i < contours.size(); ++i)
        {
            auto area = contourArea(contours[i]);
            cout << area << endl;
            if (area > 1000)    //��С�Ĺ��˷�Χ
            {
                auto peri = arcLength(contours[i], true);
                //approxPolyDP()������opencv�ж�ָ���ĵ㼯���ж���αƽ��ĺ�������ƽ��ľ��ȿ�ͨ���������á�
                //����������double epsilon��ָ���ľ��ȣ�Ҳ����ԭʼ�������������֮��������롣����������double epsilon��ָ���ľ��ȣ�Ҳ����ԭʼ�������������֮��������롣
                //���ĸ�����bool closed����Ϊtrue����˵�����������Ǳպϵģ���֮����Ϊfalse����Ͽ�
                //����Ǽ���ÿ���������ܳ� �ٴ���һ����������������ĸ��������ǹ���������������ܳ�*0.02�ж��� Ӧ����������=-=
                approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
                
                cout << conPoly[i].size() << endl;
                
                //��������������
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


    imshow("Image", img); //��ʱԭʼͼ���ϵ������ѱ����ճ�
    //imshow("Image Gray", imgGray);    //�Ҷ�ͼ��
    //imshow("Image blur", imgBlur);      //ģ������
    //imshow("Image Canny", imgCanny);  //����
    //imshow("Image Dilation", imgDil); //����
}

void demo::facedetachDemo(void)
{
    string path = "Resources/pic/bjarny.jpeg";
    Mat img = imread(path);

    CascadeClassifier faceCascade;
    //�����и���haarcascades_cuda�ļ���/CUDA��Ҫ����NVIDIA���Կ�
    faceCascade.load("Resources/data/haarcascades_cuda/haarcascade_frontalface_default.xml");

    if (faceCascade.empty())
        cout << "XML file not loaded" << endl;

    //�����沿�ľ�������
    vector<Rect>faces;
    faceCascade.detectMultiScale(img, faces,1.1,10);    //1.1�Ǳ�������,10�����ھ��ε���С���
    
    //��⵽���е�faces�����
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
        //�����и���haarcascades_cuda�ļ���/CUDA��Ҫ����NVIDIA���Կ�
        faceCascade.load("Resources/data/haarcascades/haarcascade_frontalface_default.xml");

        if (faceCascade.empty())
            cout << "XML file not loaded" << endl;

        //�����沿�ľ�������
        vector<Rect>faces;
        faceCascade.detectMultiScale(img, faces, 1.1, 10);    //1.1�Ǳ�������,10�����ھ��ε���С���
        //��⵽���е�faces�����
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
