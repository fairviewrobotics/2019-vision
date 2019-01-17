#include "LineSensingPipelineRunner.h"
#include <exception>

namespace team2036 {
  /* just init camera */
  LineSensingPipelineRunner::LineSensingPipelineRunner(int cam_index, int thresh):camera(cam_index) {
    pipeline.setCvThreshold(thresh);
  }



  void LineSensingPipelineRunner::runPipeline(){
    if(!camera.isOpened()){
      throw "Camera not open\n";
    }
    camera >> in_image;
    pipeline.Process(in_image);

  }

  double LineSensingPipelineRunner::getAngle(){

    return pipeline.GetFindLineOutput()->angle();
  }

  grip::LineSensingPipeline * LineSensingPipelineRunner::getPipeline(){
    return &pipeline;
  }

}