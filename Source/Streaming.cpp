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
static const int arrSize = 2 * stasm_NLANDMARKS;
ConvolNetwork *conv;
int width = 160;
int heigth = 80;
int foundface;
float landmCoords[arrSize];
mutex mtx;
//initialize
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
	VideoCapture cap(-1);
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
		imshow("Stream Window",frame);
		Mat resizedFrame;
		resize(frame.clone(), resizedFrame, Size(480, 280), 0, 0, INTER_CUBIC);
		//resize(resizedFrame, resizedFrame, Size(480, 280), 0, 0, INTER_CUBIC);
		thread t1 (&Streaming::getPredictions, this, resizedFrame, landmarks, image);
		t1.detach();
		int k = waitKey(1);
		if ( k == 27 ){
			break;
		}
	}
}

//gets predictions
void Streaming::getPredictions(Mat frame, Landmarks landmarks, Img image){
  if(mtx.try_lock() == true){
	Mat grayScFrame;
	cv::cvtColor(frame, grayScFrame, cv::COLOR_BGR2GRAY);
	//finds face and landmark coordinates
	if (!stasm_search_single(&foundface, landmCoords, (const char*)grayScFrame.data, grayScFrame.cols, grayScFrame.rows, "../" , "/home/noega/Desktop"))
	{
		cout << "Error in stasm_search_single: " << stasm_lasterr() << endl;
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
			frame = image.getCroppedImage(topLeftX, topLeftY, width, heigth, frame);
			//image.showLandmarks(frame, coordinates);
			//imshow("Mouth Windows", frame);
			showPredictions(conv->getPredictions(frame));
			}
		}else {
				showPredictions("Face isn't detected");
		}
		mtx.unlock();
	}
}

//shows predictions on new window
void Streaming::showPredictions(vector<string> predictions){
	Mat predArea(150, 300, CV_8UC3, Scalar(0, 0, 0));
	int y = 0;
	for(int i = 0; i < predictions.size(); ++i){
		y += 25;
		putText(predArea, predictions[i], cvPoint(10,y),FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,255,255), 1, CV_AA);
	}
	imshow("Prediction Window", predArea);
}
void Streaming::showPredictions(string text){
	Mat predArea(150, 300, CV_8UC3, Scalar(0, 0, 0));
	int y = 75;
	putText(predArea, text, cvPoint(60, y),FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,255,255), 1, CV_AA);
	imshow("Prediction Window", predArea);
}
//destructor
Streaming::~Streaming(){
	delete conv;
}
