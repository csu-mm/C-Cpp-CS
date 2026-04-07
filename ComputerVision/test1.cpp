#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
//#include <omp.h>  // not used currently
#include <windows.h>

#include <thread>

using namespace cv;
using namespace std;

Mat sourceImage;
Mat createdImage;
struct threadData
{
	int x1, y1; // p1  // x1 <= x2
	int x2, y2; // p2  // y1 <= y3
	int x3, y3; // p3  // x3 <= x4
	int x4, y4; // p4  // y2 <= y4
	int shape; // 0=unknown, 1=triangle, 2=rectangle(expands to right and bottom), 3=circle(inside), 4=circle(outside)
	byte* (*colorManipulateFn)(byte*);  // pixel color manipulation function pointer
};

byte* colorManipulateFn_white(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = {255,255,255};
	return clr;
}

byte* colorManipulateFn_black(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { 0,0,0 };
	return clr;
}
byte* colorManipulateFn_blue(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { inputColor[0],0,0 };
	return clr;
}
byte* colorManipulateFn_green(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { 0,inputColor[1],0 };
	return clr;
}
byte* colorManipulateFn_red(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { 0,0,inputColor[2]};
	return clr;
}
byte* colorManipulateFn_greenred(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { 0,inputColor[1],inputColor[2] };
	return clr;
}
byte* colorManipulateFn_bluegreen(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { inputColor[0],inputColor[1],0 };
	return clr;
}

void imgRectManupulateWorkerThread(void* thData)
{
	if (thData == NULL) return;
	threadData* cthData = (struct threadData*)thData;
	if (cthData == NULL) return;
	if (cthData->shape != 2) return; // this thread is for rectangle region manipulation.

	byte col[3];
	for (int y = cthData->y1; y < cthData->y2; y++)
	{
		for (int x = cthData->x1; x < cthData->x2; x++)
		{
			cv::Vec3b& pixel = sourceImage.at<cv::Vec3b>(y, x);
			col[0] = pixel[0]; col[1] = pixel[1]; col[2] = pixel[2];
			byte* retCol = cthData->colorManipulateFn(col);
			if (retCol != NULL)
			{
				createdImage.at<cv::Vec3b>(y, x)[0] = retCol[0];
				createdImage.at<cv::Vec3b>(y, x)[1] = retCol[1];
				createdImage.at<cv::Vec3b>(y, x)[2] = retCol[2];
			}			
		}
	}	
}


void displayImage(string strImg)
{
	if (strImg.empty() || strImg.size() < 1) return;
	Mat img = imread(strImg);  // Mat (image: matrix of pixels)	
	imshow("Image", img);
	Mat imgGray;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	imshow("Gray Image", imgGray);
	waitKey(0);
	destroyAllWindows();
}

void displayWebcam(int id)
{	
	VideoCapture cap(id);
	Mat img;
	while (cap.read(img))
	{		
		imshow("Image", img);
		waitKey(10);
	}
	destroyAllWindows();
}



int main()
{
	string imgPath1 = "Resources/family 4.jpg";
	string imgPath2 = "Resources/Brain.jpg";
	string imgPath3 = "Resources/city 2.jpg";
	
	sourceImage = imread(imgPath2);
	createdImage = CreateImage(sourceImage.cols, sourceImage.rows, Scalar(0, 0, 0 /*BGR*/));

	// threaded execution test
	
	// Divide the whole image region into parts, so that each thread can be assigned to work
	//        in one region of the image exclusively.   
	// Divide image in 4 equal parts/quadrant , rectangle region.
	// So, in this case 4 threads are needed to work.
	int partlengthX = sourceImage.cols / 2; int partlengthY = sourceImage.rows / 2;
	
	threadData threadDatas[4];
	
	// quadrant: 2 
	threadDatas[0].x1 = 0; threadDatas[0].y1 = 0; threadDatas[0].x2 = partlengthX; threadDatas[0].y2 = partlengthY;
	threadDatas[0].shape = 2; threadDatas[0].colorManipulateFn = colorManipulateFn_blue;

	// quadrant: 1	
	threadDatas[1].x1 = partlengthX; threadDatas[1].y1 = 0; threadDatas[1].x2 = 2 * partlengthX; threadDatas[1].y2 = partlengthY;
	threadDatas[1].shape = 2; threadDatas[1].colorManipulateFn = colorManipulateFn_green;

	// quadrant: 3	
	threadDatas[2].x1 = 0; threadDatas[2].y1 = partlengthY; threadDatas[2].x2 = partlengthX; threadDatas[2].y2 = 2 * partlengthY;
	threadDatas[2].shape = 2; threadDatas[2].colorManipulateFn = colorManipulateFn_red;

	// quadrant: 4	
	threadDatas[3].x1 = partlengthX; threadDatas[3].y1 = partlengthY; threadDatas[3].x2 = 2 * partlengthX; threadDatas[3].y2 = 2 * partlengthY;
	threadDatas[3].shape = 2; threadDatas[3].colorManipulateFn = colorManipulateFn_bluegreen;

	std::thread t1(imgRectManupulateWorkerThread, (void*)&threadDatas[0]);
	std::thread t2(imgRectManupulateWorkerThread, (void*)&threadDatas[1]);
	std::thread t3(imgRectManupulateWorkerThread, (void*)&threadDatas[2]);
	std::thread t4(imgRectManupulateWorkerThread, (void*)&threadDatas[3]);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::cout << "All threads finished\n";
	imshow("Original Image", sourceImage);
	imshow("Created Image", createdImage);
	waitKey(0);
	return 0;
}

/*

OpenCV C++ library, dll, header download and installation needed.
https://github.com/opencv/opencv/releases
Configure these in Microsoft Visual Studio 2019.

*/