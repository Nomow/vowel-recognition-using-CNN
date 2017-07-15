
#include <caffe/caffe.hpp>
#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
using namespace std;
using namespace cv;
using namespace caffe;
typedef std::pair<string, float> Prediction;
class ConvolNetwork
{
public:
	ConvolNetwork(const string& model_file,
		const string& trained_file,
		const string& mean_file,
		const string& label_file);
		std::vector<Prediction> Classify(const cv::Mat& img, int N = 5);
		std::vector<string> getPredictions(const cv::Mat& img);

private:
	void SetMean(const string& mean_file);
	std::vector<float> Predict(const cv::Mat& img);
	void WrapInputLayer(std::vector<cv::Mat>* input_channels);
	void Preprocess(const cv::Mat& img,
	std::vector<cv::Mat>* input_channels);
	caffe::shared_ptr<Net<float> > net_;
	cv::Size input_geometry_;
	int num_channels_;
	cv::Mat mean_;
	std::vector<string> labels_;

};
