#include "Img.h"
using namespace cv;
Img::Img()
{

}


Mat Img::getCroppedImage(int &tpX, int &tpY, int &width, int &heigth, Mat &image) {
	Rect cropField(tpX, tpY, width, heigth);
	Mat croppedImage = image(cropField);
	return croppedImage;
}

void Img::showLandmarks(Mat &image, std::vector<std::vector <int> > &coordinates) {
	for (int i = 0; i < coordinates.size(); i++) {
		cv::Point pt;
		pt.x = coordinates[i][0];
		pt.y = coordinates[i][1];

		circle(image, pt, 2, CvScalar (0, 255, 255));

	}
}
