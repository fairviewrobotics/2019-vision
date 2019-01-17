#include "LineSensingPipeline.h"

namespace team2036 {
  class LineSensingPipelineRunner {
    private:

      /* Pipeline object */
      grip::LineSensingPipeline pipeline;
      /* longest two lines */
      grip::Line *long_lines[2];
      /* camera */
      cv::VideoCapture camera;
      cv::Mat in_image;

      /* find longest lines */
      void find_longest();

    public:

    LineSensingPipelineRunner(int cam_index, int thresh_index);

    /* run pipeline and find two best lines */
    void runPipeline();

    grip::LineSensingPipeline *getPipeline();

    /* get angle of lines */
    double getAngle();
  };
}