package frc.team2036.robot;
import frc.team2036.robot.vision.linesensing.*;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.HashMap;

import org.opencv.videoio.VideoCapture;
import org.opencv.videoio.Videoio;


import org.opencv.core.*;
import org.opencv.core.Core.*;
//import org.opencv.features2d.FeatureDetector;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.*;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.objdetect.*;


public class Main {
    static private LineSenseRunner sense = new LineSenseRunner();
    static private Mat out = new Mat(420, 320, CvType.CV_8UC3);

    static private ArrayList<LineSensingVisionPipeline.Line> lines;
    static Imshow imgshow = new Imshow("Test", 420, 320);

    public static void run(){
        double angle = 0.0;
        out.setTo(new Scalar(0,0,0));
        sense.runPipeline();
        lines = sense.getPipeline().findGoodLinesOutput();
        for(int i = 0; i < lines.size(); i++){
            Imgproc.line(out, new Point(lines.get(i).x1, lines.get(i).y1), new Point(lines.get(i).x2, lines.get(i).y2), new Scalar(255,255,255), 1);
            Imgproc.circle(out, new Point(lines.get(i).x1, lines.get(i).y1), 1, new Scalar(255,0,0), 2);
            Imgproc.circle(out, new Point(lines.get(i).x2, lines.get(i).y2), 1, new Scalar(0,0,255), 2);

            double curAngle = lines.get(i).angle();
            //normalize to range 0-180
            if(curAngle < 0.0){
                curAngle += 180.0;
            }
            curAngle = 180.0 - curAngle;
            angle += curAngle / 2.0;

        }

        System.out.println(angle);

        imgshow.showImage(out);
        //imgshow2.showImage(sense.getPipeline().cvThresholdOutput());

    }

    public static void main(String args[]){
        sense.openCamera(1);
        while(true){
            run();
        }
    }

}
