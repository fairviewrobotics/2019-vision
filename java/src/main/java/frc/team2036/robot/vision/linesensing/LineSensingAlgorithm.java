package frc.team2036.robot.vision.linesensing;

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
import org.opencv.objdetect.*;

public class LineSensingAlgorithm {
    public Mat downscaled = new Mat(), gray = new Mat(), thresholded = new Mat(), blured = new Mat();


    //algorithm vars
    //downscale size
    private int sizeX = 420, sizeY = 320;
    //blur size
    private int blurSize = 7;

    public void run(Mat input){
        //resize
        Imgproc.resize(input, downscaled, new Size(sizeX, sizeY));
        //grayscale
        Imgproc.cvtColor(downscaled, gray, Imgproc.COLOR_BGR2GRAY);
        //guassian blur
        Imgproc.GaussianBlur(gray, blured, new Size(blurSize, blurSize), 0);
        //threshold
        //Otsu's method automatically chooses a global threshold value - should work well if line is clearly brighter from most of the rest of the image
        Imgproc.threshold(blured, thresholded,0,255,Imgproc.THRESH_BINARY+Imgproc.THRESH_OTSU);

        //Find contours
        List<MatOfPoint> contours = new ArrayList<>();
        Mat contourHierarchy = new Mat();
        Imgproc.findContours(thresholded, contours, contourHierarchy, Imgproc.RETR_LIST, Imgproc.CHAIN_APPROX_SIMPLE);
        int largestIdx = findLargestContourIdx(contours);

        //draw contours

        Imgproc.drawContours(blured, contours, largestIdx, new Scalar(0,255,0), 5);

    }

    //find the largest contour index
    public int findLargestContourIdx(List<MatOfPoint> contours){
        double maxVal = 0;
        int maxValIdx = 0;
        for (int contourIdx = 0; contourIdx < contours.size(); contourIdx++)
        {
            double contourArea = Imgproc.contourArea(contours.get(contourIdx));
            if (maxVal < contourArea)
            {
                maxVal = contourArea;
                maxValIdx = contourIdx;
            }
        }

        return maxValIdx;
    }

    public void setDownscaleSize(int w, int h){
        sizeX = w;
        sizeY = h;
    }

    public void setBlurSize(int size){
        blurSize = size;
    }
}