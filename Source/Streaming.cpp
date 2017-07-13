#include "Streaming.h"
#include<iostream>
#include <vector>
#include "stasm_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include "ConvolNetwork.h"
#include <thread>
#include <mutex>
using namespace std;
using namespace cv;

ConvolNetwork *conv;
int width = 160;
int heigth = 80;
int foundface;
int arrSize = 2 * stasm_NLANDMARKS;
float landmCoords[2 * stasm_NLANDMARKS];
mutex mtx;
Streaming::Streaming()
{
	string model_file = "//home//noega//Desktop//stasm//IncludeFiles//deploy.prototxt";
	string trained_file = "//home//noega//Desktop//stasm//IncludeFiles//trained_file.caffemodel";
	string mean_file = "//home//noega//Desktop//stasm//IncludeFiles//MRS_mean.binaryproto";
	string label_file = "//home//noega//Desktop//stasm//IncludeFiles//synset.txt";
	cout << "cam init" << endl;
	conv = new ConvolNetwork(model_file, trained_file, mean_file, label_file);
	stasm_init("/home/noega/Desktop/stasm/IncludeFiles/", 0);
}

// captures stream
void Streaming::capture() {
	cout << "cam capture" << endl;
	VideoCapture cap(1);
	cap.set(CV_CAP_PROP_FPS, 24);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 480);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 280);
	Landmarks landmarks;
	Img image;
	while( cap.isOpened() )   // check if  succeeded
	{
		Mat frame;
		if ( ! cap.read(frame) ){
			cout << "cap no frame" << endl;
			break;
		}
		//read frame 1 threeads
		//convol otraja threadaa ar mutex

		resize(frame, frame, Size(480, 280), 0, 0, INTER_CUBIC);
		imshow("Stream Window",frame);
		thread t1 (&Streaming::getPredictions, this, frame, landmarks, image);
		t1.detach();
		//getPredictions(frame, landmarks, image);
		int k = waitKey(1);
		if ( k == 27 ){
			break;
		}
	}
}

void Streaming::getPredictions(Mat frame, Landmarks landmarks, Img image){
  if(mtx.try_lock() == true){
		Mat landmFrame;
		landmFrame = frame;
		cv::cvtColor(landmFrame, landmFrame, cv::COLOR_BGR2GRAY);
		if (!stasm_search_single(&foundface, landmCoords, (const char*)landmFrame.data, landmFrame.cols, landmFrame.rows, "../" , "/home/noega/Desktop"))
		{
			printf("Error in stasm_search_single: %s\n", stasm_lasterr());
		}

		if (foundface){
			//	cout << "face is detected" << endl;
			std::vector< std::vector<int> > coordinates = landmarks.getCoordinates(landmCoords, arrSize);
			int centroidX = landmarks.getCentroidX(coordinates);
			//gets centroid y
			int centroidY = landmarks.getCentroidY(coordinates);
			//gets top left x
			int topLeftX = landmarks.getTopLeftX(width, centroidX);
			//gets top left y
			int topLeftY = landmarks.getTopLeftY(heigth, centroidY);
			if (topLeftX  >= 0 && topLeftY >= 0 && topLeftX + width <= 480 && topLeftY + heigth <= 280) {
				Mat croppedFrame = image.getCroppedImage(topLeftX, topLeftY, width, heigth, frame);
			//image.showLandmarks(frame, coordinates);
			//imshow("Mouth Windows", croppedFrame);
				conv->displayPredictions(croppedFrame);
			}
		}
		mtx.unlock();
	}
}

Streaming::~Streaming(){
	delete conv;
}
