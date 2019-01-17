#include "LineSensingPipeline.h"

namespace team2036 {
  class LineSensingPipelineRunner {
    private:

      /* Pipeline object */
      grip::LineSensingPipeline pipeline;
      /* camera */
      cv::VideoCapture camera;
      cv::Mat in_image;



    public:

    LineSensingPipelineRunner(int cam_index, int thresh_index);

    /* run pipeline and find two best lines */
    void runPipeline();

    grip::LineSensingPipeline *getPipeline();

    /* get angle of lines */
    double getAngle();
  };
}