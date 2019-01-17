#include "LineSensingPipeline.h"
#include "LineSensingPipelineRunner.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

//camera port/index
const int cameraIndex = 1;
//threshold (from 0-256) for finding white
const int thresh = 170;
team2036::LineSensingPipelineRunner runner(cameraIndex, thresh);

/* uncomment the following line, or pass -DDISPLAY_DEBUG to g++ to display thresholding debugging images (only for platforms with guis) */
//#define DISPLAY_DEBUG  1


int main(){
  #ifdef DISPLAY_DEBUG
    cv::namedWindow( "Test", cv::WINDOW_AUTOSIZE );
  #endif
  while(1){
    runner.runPipeline();
    printf("%f\n", runner.getAngle());
    #ifdef DISPLAY_DEBUG
      cv::imshow("Test", *runner.getPipeline()->GetCvThresholdOutput());
      if(cv::waitKey(1) == 'q'){
        return 0;
      };
    #endif
  }
}
