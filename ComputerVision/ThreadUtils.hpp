#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

#include <windows.h>
#include <thread>

using namespace cv;
using namespace std;



struct threadData
{
	// min bounding Rectangle
	int ltx, lty; // ltx: left-top-x, lty: left-top-y
	int rtx, rty; //
	int lbx, lby; //
	int rbx, rby; //
	vector<cv::Point2d> ApproxPolyPoints;
	int shape; // 0=unknown, 1=triangle, 2=rectangle(expands to right and bottom), 3=circle(inside), 4=circle(outside)
	byte* (*colorManipulateFn)(byte*);
	const cv::Mat* sourceImage;
	cv::Mat* createdImage;	
};

byte* colorManipulateFn_white(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { 255,255,255 };
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
	byte clr[3] = { 0,0,inputColor[2] };
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
byte* colorManipulateFn_bluered(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { inputColor[0],0,inputColor[2] };
	return clr;
}
byte* colorManipulateFn_inv_blue(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { 255-inputColor[0],inputColor[1],inputColor[2] };
	return clr;
}
byte* colorManipulateFn_inv_green(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { inputColor[0],255-inputColor[1],inputColor[2] };
	return clr;
}
byte* colorManipulateFn_inv_red(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { inputColor[0],inputColor[1],255 - inputColor[2] };
	return clr;
}
byte* colorManipulateFn_inv_bg(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { 255 - inputColor[0],255 - inputColor[1],inputColor[2]};
	return clr;
}
byte* colorManipulateFn_inv_br(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { 255 - inputColor[0],inputColor[1],255 - inputColor[2]};
	return clr;
}
byte* colorManipulateFn_inv_gr(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { inputColor[0], 255-inputColor[1], 255-inputColor[2] };
	return clr;
}
byte* colorManipulateFn_inv_bgr(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { 255 - inputColor[0], 255 - inputColor[1], 255 - inputColor[2] };
	return clr;
}
byte* colorManipulateFn_bgr(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { inputColor[0],inputColor[1],inputColor[2] };
	return clr;
}
byte* colorManipulateFn_removeWeakColors(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { inputColor[0],inputColor[1],inputColor[2] };
	int wkIndex0 = 0, wkIndex1=1, wkIndex2=2;

	if (clr[0] < clr[1] && clr[0] < clr[2])
	{
		wkIndex0 = 0;
		wkIndex1 = 1; wkIndex2 = 2;
	}
	else if (clr[1] < clr[0] && clr[1] < clr[2])
	{
		wkIndex0 = 1;
		wkIndex1 = 0; wkIndex2 = 2;
	}
	else
	{
		wkIndex0 = 2;
		wkIndex1 = 0; wkIndex2 = 1;
	}
	if (clr[wkIndex1] > clr[wkIndex2])
	{
		wkIndex1 += wkIndex2;
		wkIndex2 = wkIndex1 - wkIndex2;
		wkIndex1 = wkIndex1 - wkIndex2;
	}

	// Now, we've clr[wkIndex0] < clr[wkIndex1] < clr[wkIndex2]

	if (clr[wkIndex0] * 2 <= clr[wkIndex2])	
		clr[wkIndex0] = 0;
	
	if (clr[wkIndex1] * 2 <= clr[wkIndex2])	
		clr[wkIndex1] = 0;	

	return clr;
}
byte* colorManipulateFn_removeStrongColors(byte* inputColor)
{
	if (!inputColor) return NULL;
	byte clr[3] = { inputColor[0],inputColor[1],inputColor[2] };
	int wkIndex0 = 0, wkIndex1 = 1, wkIndex2 = 2;

	if (clr[0] < clr[1] && clr[0] < clr[2])
	{
		wkIndex0 = 0;
		wkIndex1 = 1; wkIndex2 = 2;
	}
	else if (clr[1] < clr[0] && clr[1] < clr[2])
	{
		wkIndex0 = 1;
		wkIndex1 = 0; wkIndex2 = 2;
	}
	else
	{
		wkIndex0 = 2;
		wkIndex1 = 0; wkIndex2 = 1;
	}
	if (clr[wkIndex1] > clr[wkIndex2])
	{
		wkIndex1 += wkIndex2;
		wkIndex2 = wkIndex1 - wkIndex2;
		wkIndex1 = wkIndex1 - wkIndex2;
	}

	// Now, we've clr[wkIndex0] < clr[wkIndex1] < clr[wkIndex2]

	if (clr[wkIndex0] * 2 <= clr[wkIndex2])	
		clr[wkIndex2] = 0;
	
	if (clr[wkIndex1] * 2 <= clr[wkIndex2])	
		clr[wkIndex2] = 0;
	
	if (clr[wkIndex0] * 2 <= clr[wkIndex1])	
		clr[wkIndex1] = 0;	

	return clr;
}

void imgRectManupulateWorkerThread(void* thData)
{
	if (thData == NULL) return;
	threadData* cthData = (struct threadData*)thData;
	if (cthData == NULL) return;
	const cv::Mat& sourceImage = *(cthData->sourceImage);
	if (sourceImage.data == nullptr || sourceImage.empty()) return;
	cv::Mat& createdImage = *(cthData->createdImage);
	if (createdImage.data == nullptr || createdImage.empty()) return;

	byte col[3];
	for (int y = cthData->lty; y < cthData->lby; y++)
	{
		for (int x = cthData->ltx; x < cthData->rtx; x++)
		{
			const cv::Vec3b& pixel = sourceImage.at<cv::Vec3b>(y, x);
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

void imgRectManupulateWorkerThread2(void* thData)
{
	if (thData == NULL) return;
	threadData* cthData = (struct threadData*)thData;
	if (cthData == NULL) return;
	const cv::Mat& sourceImage = *(cthData->sourceImage);
	if (sourceImage.data == nullptr || sourceImage.empty()) return;
	cv::Mat& createdImage = *(cthData->createdImage);
	if (createdImage.data == nullptr || createdImage.empty()) return;

	byte col[3];
	for (int y = cthData->lty; y < cthData->rty; y++)
	{
		for (int x = cthData->ltx; x < cthData->rtx; x++)
		{
			const cv::Vec3b& pixel = sourceImage.at<cv::Vec3b>(y, x);
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

cv::Mat ThreadedImageRegionCompose(const cv::Mat& srcImage, int hRegionCount)
{
	if (srcImage.data == nullptr || hRegionCount < 1) return srcImage;
	//Mat resizedImg = resizeWithAspectRatio(srcImage, 1200, 1024);  // optional, random resize selected
	cv::Mat createdImg = cv::Mat(srcImage.rows, srcImage.cols, CV_8UC3, Scalar(0, 0, 0));

	int xParts = hRegionCount; int yParts = hRegionCount;  // output image regions: hRegionCount x hRegionCount
	int xPartLength = srcImage.cols / xParts; int yPartLength = srcImage.rows / yParts;
	vector<std::thread> threads(xParts * yParts);  // one thread per region
	vector<struct threadData> threadDatas(xParts * yParts);
	vector<void*> colorManipulatorFns;  // store some coloring delegate/function randomly
	colorManipulatorFns.push_back(colorManipulateFn_white);
	colorManipulatorFns.push_back(colorManipulateFn_black);
	colorManipulatorFns.push_back(colorManipulateFn_blue);
	colorManipulatorFns.push_back(colorManipulateFn_green);
	colorManipulatorFns.push_back(colorManipulateFn_red);
	colorManipulatorFns.push_back(colorManipulateFn_greenred);
	colorManipulatorFns.push_back(colorManipulateFn_bluegreen);
	colorManipulatorFns.push_back(colorManipulateFn_bluered);
	colorManipulatorFns.push_back(colorManipulateFn_inv_blue);
	colorManipulatorFns.push_back(colorManipulateFn_inv_green);
	colorManipulatorFns.push_back(colorManipulateFn_inv_red);
	colorManipulatorFns.push_back(colorManipulateFn_inv_bg);
	colorManipulatorFns.push_back(colorManipulateFn_inv_br);
	colorManipulatorFns.push_back(colorManipulateFn_inv_gr);
	colorManipulatorFns.push_back(colorManipulateFn_inv_bgr);
	colorManipulatorFns.push_back(colorManipulateFn_bgr);
	colorManipulatorFns.push_back(colorManipulateFn_removeWeakColors);
	colorManipulatorFns.push_back(colorManipulateFn_removeStrongColors);

	for (int y = 0; y < yParts; y++)
	{
		for (int x = 0; x < xParts; x++)
		{
			threadDatas[y * yParts + x].ltx = x * xPartLength; threadDatas[y * yParts + x].lty = y * yPartLength;
			threadDatas[y * yParts + x].rtx = (x + 1) * xPartLength; threadDatas[y * yParts + x].rty = y * yPartLength;
			threadDatas[y * yParts + x].lbx = x * xPartLength; threadDatas[y * yParts + x].lby = (y + 1) * yPartLength;
			threadDatas[y * yParts + x].rbx = (x + 1) * xPartLength; threadDatas[y * yParts + x].rby = (y + 1) * yPartLength;

			threadDatas[y * yParts + x].ApproxPolyPoints.push_back(Point2d(x * xPartLength, y * yPartLength));
			threadDatas[y * yParts + x].ApproxPolyPoints.push_back(Point2d((x + 1) * xPartLength, y * yPartLength));
			threadDatas[y * yParts + x].ApproxPolyPoints.push_back(Point2d(x * xPartLength, (y + 1) * yPartLength));
			threadDatas[y * yParts + x].ApproxPolyPoints.push_back(Point2d((x + 1) * xPartLength, (y + 1) * yPartLength));

			threadDatas[y * yParts + x].createdImage = &createdImg; threadDatas[y * yParts + x].sourceImage = &srcImage;
			threadDatas[y * yParts + x].shape = 2;

			// Select color manipulation function pointers randomly. Possibly this should be an input argument
			threadDatas[y * yParts + x].colorManipulateFn = (byte* (*)(byte*))colorManipulatorFns[(y * yParts + x) % colorManipulatorFns.size()];			
		}
	}

	for (int i = 0; i < threadDatas.size(); i++)
		threads.emplace_back(imgRectManupulateWorkerThread, (void*)&threadDatas[i]);
	for (auto& t : threads)
		if (t.joinable())
			t.join();
	
	// at this point, all threads are done
	return createdImg;
}