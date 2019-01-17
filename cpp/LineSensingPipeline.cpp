#include "LineSensingPipeline.h"

namespace grip {

LineSensingPipeline::LineSensingPipeline() {
}
/**
* Runs an iteration of the pipeline and updates outputs.
*/
void LineSensingPipeline::Process(cv::Mat& source0){
	//Step Desaturate0:
	//input
	cv::Mat desaturateInput = source0;
	desaturate(desaturateInput, this->desaturateOutput);
	//Step Resize_Image0:
	//input
	cv::Mat resizeImageInput = desaturateOutput;
	double resizeImageWidth = 420.0;  // default Double
	double resizeImageHeight = 320.0;  // default Double
	int resizeImageInterpolation = cv::INTER_CUBIC;
	resizeImage(resizeImageInput, resizeImageWidth, resizeImageHeight, resizeImageInterpolation, this->resizeImageOutput);
	//Step Blur0:
	//input
	cv::Mat blurInput = resizeImageOutput;
	BlurType blurType = BlurType::BOX;
	double blurRadius = 6.306306306306306;  // default Double
	blur(blurInput, blurType, blurRadius, this->blurOutput);
	//Step CV_Threshold0:
	//input
	cv::Mat cvThresholdSrc = blurOutput;
	double cvThresholdThresh = 170.0;  // default Double
	double cvThresholdMaxval = 256.0;  // default Double
    int cvThresholdType = cv::THRESH_BINARY;
	cvThreshold(cvThresholdSrc, cvThresholdThresh, cvThresholdMaxval, cvThresholdType, this->cvThresholdOutput);
	//Step Find_Lines0:
	//input
	cv::Mat findLinesInput = cvThresholdOutput;
	findLines(findLinesInput, this->findLinesOutput);
}

/**
 * This method is a generated getter for the output of a Desaturate.
 * @return Mat output from Desaturate.
 */
cv::Mat* LineSensingPipeline::GetDesaturateOutput(){
	return &(this->desaturateOutput);
}
/**
 * This method is a generated getter for the output of a Resize_Image.
 * @return Mat output from Resize_Image.
 */
cv::Mat* LineSensingPipeline::GetResizeImageOutput(){
	return &(this->resizeImageOutput);
}
/**
 * This method is a generated getter for the output of a Blur.
 * @return Mat output from Blur.
 */
cv::Mat* LineSensingPipeline::GetBlurOutput(){
	return &(this->blurOutput);
}
/**
 * This method is a generated getter for the output of a CV_Threshold.
 * @return Mat output from CV_Threshold.
 */
cv::Mat* LineSensingPipeline::GetCvThresholdOutput(){
	return &(this->cvThresholdOutput);
}
/**
 * This method is a generated getter for the output of a Find_Lines.
 * @return LinesReport output from Find_Lines.
 */
std::vector<Line>* LineSensingPipeline::GetFindLinesOutput(){
	return &(this->findLinesOutput);
}
	/**
	 * Converts a color image into shades of grey.
	 *
	 * @param input The image on which to perform the desaturate.
	 * @param output The image in which to store the output.
	 */
	void LineSensingPipeline::desaturate(cv::Mat &input, cv::Mat &output) {
		switch (input.channels()) {
			case 1:
				// If the input is already one channel, it's already desaturated
				input.copyTo(output);
				break;
			case 3:
				cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);
				break;
			case 4:
				cv::cvtColor(input, output, cv::COLOR_BGRA2GRAY);
				break;
			default:
				throw "Input to desaturate must have 1, 3, or 4 channels";
		}
	}

	/**
	 * Scales and image to an exact size.
	 *
	 * @param input The image on which to perform the Resize.
	 * @param width The width of the output in pixels.
	 * @param height The height of the output in pixels.
	 * @param interpolation The type of interpolation.
	 * @param output The image in which to store the output.
	 */
	void LineSensingPipeline::resizeImage(cv::Mat &input, double width, double height, int interpolation, cv::Mat &output) {
		cv::resize(input, output, cv::Size(width, height), 0.0, 0.0, interpolation);
	}

	/**
	 * Softens an image using one of several filters.
	 *
	 * @param input The image on which to perform the blur.
	 * @param type The blurType to perform.
	 * @param doubleRadius The radius for the blur.
	 * @param output The image in which to store the output.
	 */
	void LineSensingPipeline::blur(cv::Mat &input, BlurType &type, double doubleRadius, cv::Mat &output) {
		int radius = (int)(doubleRadius + 0.5);
		int kernelSize;
		switch(type) {
			case BOX:
				kernelSize = 2 * radius + 1;
				cv::blur(input,output,cv::Size(kernelSize, kernelSize));
				break;
			case GAUSSIAN:
				kernelSize = 6 * radius + 1;
				cv::GaussianBlur(input, output, cv::Size(kernelSize, kernelSize), radius);
				break;
			case MEDIAN:
				kernelSize = 2 * radius + 1;
				cv::medianBlur(input, output, kernelSize);
				break;
			case BILATERAL:
				cv::bilateralFilter(input, output, -1, radius, radius);
				break;
        }
	}
	/**
	 * Apply a fixed-level threshold to each array element in an image.
	 * @param src Image to threshold.
	 * @param thresh threshold value.
	 * @param maxVal Maximum value for THRES_BINARY and THRES_BINARY_INV.
	 * @param type Type of threshold to apply.
	 * @param dst output Image.
	 */
	void LineSensingPipeline::cvThreshold(cv::Mat &src, double thresh, double maxVal, int type, cv::Mat &dst) {
		cv::threshold(src, dst, thresh, maxVal, type);
	}

	/**
	 * Finds all line segments in an image.
	 *
	 * @param input The image on which to perform the find lines.
	 * @param lineList The output where the lines are stored.
	 */
	void LineSensingPipeline::findLines(cv::Mat &input, std::vector<Line> &lineList) {
		cv::Ptr<cv::LineSegmentDetector> lsd = cv::createLineSegmentDetector(LSD_REFINE_STD);
		std::vector<cv::Vec4i> lines;
		lineList.clear();
		if (input.channels() == 1) {
			lsd->detect(input, lines);
		} else {
			// The line detector works on a single channel.
			cv::Mat tmp;
			cv::cvtColor(input, tmp, cv::COLOR_BGR2GRAY);
			lsd->detect(tmp, lines);
		}
		// Store the lines in the LinesReport object
		if (!lines.empty()) {
			for (int i = 0; i < lines.size(); i++) {
				cv::Vec4i line = lines[i];
				lineList.push_back(Line(line[0], line[1], line[2], line[3]));
			}
		}
	}



} // end grip namespace

