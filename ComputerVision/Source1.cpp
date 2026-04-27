#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <omp.h>
#include <windows.h>
#include <thread>

#include "ThreadUtils.hpp"
#include "functions-1.hpp"


using namespace cv;
using namespace std;


Scalar GetScalar(int i)  // just to understand rotation direction
{
	if (i == 0) return Scalar(255, 0, 0);
	if (i == 1) return Scalar(0, 255, 0);
	if (i == 2) return Scalar(0, 0, 255);

	return Scalar(255, 255, 255);
}

void prospectiveTransformation(string strImg)
{
	if (strImg.empty() || strImg.size() < 1) return;

	float w = 250, h = 350; // actual width and height
	Mat matrix, imgWarp;
	Mat img = imread(strImg);

	// Point2f src[4] = { {529,142},{771,190},{405,395},{674,457} };
	//x Point2f src[4] = { {797,219},{608,595},{1013,692},{1157,288} }; // anti-clockwise
	//x Point2f src[4] = { {797,219},{1157,288},{1013,692},{608,595} }; // clockwise
	Point2f src[4] = { {797,219},{1157,288},{608,595},{1013,692} }; // ok // lt, rt, lb, rb
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	for (int i = 0; i < 4; i++)
	{
		cv::circle(img, src[i], 8, GetScalar(i), FILLED);
	}

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
	cv::imshow("Image", img);
	cv::imshow("Image Warp", imgWarp);
	cv::waitKey(0);
	cv::destroyAllWindows();
}


cv::Mat getImageFromWebCam()
{
	Mat img;

	VideoCapture cap(0);
	bool bCaptured = false;
	while (!bCaptured && cv::waitKey(2) && cap.read(img))
	{
		bCaptured = true;  // (cv::waitKey(2) & 0xFF) == 'q';
	}
	return img;

	while (true)
	{
		cap.read(img);
		//newPojnts = findColor(img);
		//drawOnCanvas(newPojnts);
		cv::imshow("Image", img);
		waitKey(1);
	}
}

Mat imgOriginal, imgGray, imgBlur, imgCanny, imgDil, imgErode, imgThre, imgWarp, imgCrop;
vector<Point> initialPoints;

Mat preprocessing(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	// erode(imgDil, imgErode, kernel);

	return imgDil;
}


void drawPoints(cv::Mat imgOriginal, vector<Point> points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOriginal, points[i], 10, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
	}
}


int main()
{
	std::cout << "Application started...\n\n";

	string imgFamily4 = "Resources/family 4.jpg";
	string imgPath2 = "Resources/Brain.jpg";
	string imgPath3 = "Resources/city 2.jpg";
	string videoPath = "Resources/videoFile.MOV";
	string imgCardsPath = "Resources/Cards.jpg";
	string imgShapesPath = "Resources/Shapes.PNG";
	string imgScannedA4Doc1 = "Resources/A4 Doc1.JPG";
	string imgScannedA4Doc2 = "Resources/A4 Doc2.JPG";

	string imgNature1 = "Resources/Ducks swimming Asus28U.PNG";
	string imgNature2 = "Resources/Ducks swimming Asus289U.PNG";

	Mat imgOrg = imread(imgNature1);
	Mat resizedImg = resizeWithAspectRatio(imgOrg, 1200, 1024);
	cv::imshow("Image", resizedImg);

	// Create empty new image	
	cv::Mat retImg = ThreadedImageRegionCompose(resizedImg, 4); // divive into 4x4 regions, apply different coloring schemes, 
	                                                            // composte all these regions into a single image and return that image.
	cv::imshow("Created Image", retImg);

	cout << "Application closing. Press 'q' to quit...\n\n";
	if ((cv::waitKey(0) & 0xFF) == 'q')
		cv::destroyAllWindows();
	return 0;
}

