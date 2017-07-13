
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>
using namespace std;

class Img
{
public:
	Img();
	cv::Mat getCroppedImage(int &tpX, int &tpY, int &width, int &heigth, cv::Mat &image);
	void showLandmarks(cv::Mat &image, std::vector <std::vector<int> > &coordinates);
};
