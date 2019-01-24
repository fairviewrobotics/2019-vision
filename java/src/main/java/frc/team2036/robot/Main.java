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
    private static LineSense sense = new LineSense();

    static Imshow imgshow = new Imshow("test", 420, 320);

    public static void run(){
        sense.runAlgorithm();
        System.out.println(sense.algorithm.angle);
        System.out.println(sense.algorithm.angle_updated);
        imgshow.showImage(sense.algorithm.blured);
    }

    public static void main(String args[]){
        sense.openCamera(1);
        //sense.algorithm.setDownscaleSize(240, 180);
        while(true){
            run();
        }
    }

}
