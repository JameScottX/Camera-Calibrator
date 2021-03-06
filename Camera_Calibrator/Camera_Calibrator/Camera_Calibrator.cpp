// Camera_Calibrator.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include <string>
#include <iostream>


using namespace cv;
using namespace std;

int main()
{
	VideoCapture inputVideo(1);
	inputVideo.set(CV_CAP_PROP_FRAME_WIDTH, 800);
	inputVideo.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
	if (!inputVideo.isOpened())
	{
		cout << "Could not open the input video: " << endl;
		return -1;
	}
	Mat frame;
	Mat frameCalibration;

	inputVideo >> frame;
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
	cameraMatrix.at<double>(0, 0) = 917.052472085750;
	cameraMatrix.at<double>(0, 1) = 0.657056681717874;
	cameraMatrix.at<double>(0, 2) = 408.884053678499;
	cameraMatrix.at<double>(1, 1) = 916.541676777971;
	cameraMatrix.at<double>(1, 2) = 332.189066871859;

	Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
	distCoeffs.at<double>(0, 0) = -0.108750634204250;
	distCoeffs.at<double>(1, 0) = -0.155068804309725;
	distCoeffs.at<double>(2, 0) = -0.00261486335789016;
	distCoeffs.at<double>(3, 0) = 0.00154770538482982;
	distCoeffs.at<double>(4, 0) = 0;

	Mat view, rview, map1, map2;
	Size imageSize;

	imageSize = frame.size();
	initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
		getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
		imageSize, CV_16SC2, map1, map2);


	while (1) //Show the image captured in the window and repeat
	{
		inputVideo >> frame;              // read
		if (frame.empty()) break;         // check if at end
		remap(frame, frameCalibration, map1, map2, INTER_LINEAR);
		imshow("Origianl", frame);
		imshow("Calibration", frameCalibration);
		char key = waitKey(1);
		if (key == 27 || key == 'q' || key == 'Q')break;
	}
	return 0;
}
