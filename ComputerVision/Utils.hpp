#pragma once

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;


cv::Mat CreateEmptyImage(int width, int height, cv::Scalar bgColor)
{
	return cv::Mat(height, width, CV_8UC3, bgColor);// cv::Scalar(c_blue, c_green, c_red));
}

cv::Mat resizeWithAspectRatio(const cv::Mat& src, int maxWidth, int maxHeight)
{
	int originalWidth = src.cols;
	int originalHeight = src.rows;

	double aspectRatio = (double)originalWidth / originalHeight;

	int newWidth = maxWidth;
	int newHeight = (int)(maxWidth / aspectRatio);

	if (newHeight > maxHeight)
	{
		newHeight = maxHeight;
		newWidth = (int)(maxHeight * aspectRatio);
	}

	cv::Mat retImg;
	cv::resize(src, retImg, cv::Size(newWidth, newHeight), cv::INTER_AREA);
	return retImg;
}

cv::Mat imageResize(const cv::Mat& src, float scale = 0.75)
{
	if (src.data == nullptr || src.empty()) return src;

	cv::Mat imgResized;
	if (scale <= 0) return imgResized;

	resize(src, imgResized, cv::Size(), (scale, scale));
	return imgResized;
}

cv::Mat imageCrop(const cv::Mat& src, int x, int y, int w, int h)
{
	if (src.data == nullptr || src.empty()) return src;

	cv::Mat imgCorped;
	if (x < 0 || y < 0 || w < 1 || h < 1) return imgCorped;

	cv::Rect roi(x, y, w, h);
	imgCorped = src(roi);
	return imgCorped;
}

vector<vector<Point>> getContours(const cv::Mat& img)
{
	cv::Mat imgGray, imgBlur, imgCanny, imgDil;
	cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	// erode(imgDil, imgErode, kernel);

	std::vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy;
	int i = 0;

	findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);

	vector<vector<Point>> contoursApproxPoly(contours.size());
	vector<Rect> boundRect;
	for (auto& x : contours)
	{
		float perimeter = arcLength(x, true);
		approxPolyDP(x, contoursApproxPoly[i], 0.02 * perimeter, true);
		//cout << contourArea(x) << endl;
		//if (contoursApproxPoly[i].size() == 4) cout << "Rectangle" << endl;
		//else if (contoursApproxPoly[i].size() == 3) cout << "Triangle" << endl;
		//else cout << "Polygon, sides=" << contoursApproxPoly[i].size() << endl;
		//Rect rec = boundingRect(x);
		//boundRect.push_back(rec);
		//rectangle(img, rec.tl(), rec.br(), Scalar(0, 255, 0), 5);
		// putText(img, <text>, x0, y0, <font>, <float>, <Scalar>, <text thickness>)
		i++;
	}
	//drawContours(img, contoursApproxPoly, -1, Scalar(255, 0, 255), 2);

	return contoursApproxPoly;
}

cv::Mat getWarp(const cv::Mat& img, vector<Point> points, float w, float h)
{
	Point2f src[4] = { points[0], points[1],points[2], points[3] };
	//
	// points[0]       points[1]
	//
	//        points[2]         points[3]
	//
	Point2f dst[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

	Mat imgWarp, matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	return imgWarp;
}

cv::Mat PolyImageCopy(const cv::Mat& src, vector<cv::Point> poly)
{
	if (src.data == nullptr || src.empty() || poly.empty() || poly.size() < 3) return src;
	for (auto& p : poly)
	{
		if (p.x < 0 || p.x > src.rows || p.y < 0 || p.y > src.cols)
			return src;
	}
	cv::Mat extractedImage;	
	cv::Mat mask = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
	cv::fillPoly(mask, std::vector<std::vector<cv::Point>>{poly}, cv::Scalar(255));
	src.copyTo(extractedImage, mask);
	return extractedImage;
	/* to get contour boundary pixel coordinates
	std::vector<cv::Point> inside;
	for (int y = 0; y < mask.rows; y++) 
	{
		for (int x = 0; x < mask.cols; x++) 
		{
			if (mask.at<uchar>(y, x) > 0) 
			{
				inside.emplace_back(x, y);
			}
		}
	}
	*/
}

