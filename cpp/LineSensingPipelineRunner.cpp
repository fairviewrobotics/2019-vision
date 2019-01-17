#include "LineSensingPipelineRunner.h"
#include <exception>

namespace team2036 {
  /* just init camera */
  LineSensingPipelineRunner::LineSensingPipelineRunner(int cam_index, int thresh):camera(cam_index) {
    pipeline.setCvThreshold(thresh);
  }

  void LineSensingPipelineRunner::find_longest(){
    std::vector<grip::Line> * in_lines = pipeline.GetFindLinesOutput();

    double max_len[2] = {0.0,0.0};

    /* reset longest lines */
    long_lines[0] = NULL;
    long_lines[1] = NULL;

    for(unsigned int i = 0; i < in_lines->size(); i++){
      double len = (*in_lines)[i].length();

      if(len > max_len[0]){
        //shift current first longest to second longest down
        max_len[1] = max_len[0];
        long_lines[1] = long_lines[0];

        max_len[0] = len;
        long_lines[0] = &((*in_lines)[i]);
      } else if(len > max_len[1]){
        max_len[1] = len;
        long_lines[1] = &((*in_lines)[i]);
      }

    }
  }

  void LineSensingPipelineRunner::runPipeline(){
    if(!camera.isOpened()){
      throw "Camera not open\n";
    }
    camera >> in_image;
    pipeline.Process(in_image);

    find_longest();

  }

  double LineSensingPipelineRunner::getAngle(){
    double angle = 0.0;
    double curAngle = 0.0;

    for(int i = 0; i < 2; i++){
      //make sure we found lines last frame
      if(!long_lines[i]){
        continue;
      }

      curAngle = long_lines[i]->angle();

      //normalize to range 0-180
      if(curAngle < 0.0){
        curAngle += 180.0;
      }
      curAngle = 180.0 - curAngle;
      angle += curAngle / 2.0;
    }

    return angle;
  }

  grip::LineSensingPipeline * LineSensingPipelineRunner::getPipeline(){
    return &pipeline;
  }

}