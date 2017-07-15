#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Landmarks.h"
#include "Img.h"

class Streaming
{
	public:
		Streaming();
		void capture();
		~Streaming();
	private:
		void getPredictions(cv::Mat frame, Landmarks landmarks, Img image);
		void showPredictions(vector<string> predictions);
		void showPredictions(string text);
};
