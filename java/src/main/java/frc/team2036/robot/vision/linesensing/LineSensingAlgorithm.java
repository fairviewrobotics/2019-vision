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
    private int blurSize = 11;

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

        //find moments
        Moments moments = Imgproc.moments(contours.get(largestIdx));
        Point centroid = new Point();
        //centroid
	    centroid.x = moments.get_m10() / moments.get_m00();
        centroid.y = moments.get_m01() / moments.get_m00();

        //fit ellipse
        MatOfPoint2f contour_points = new MatOfPoint2f();
        contours.get(largestIdx).convertTo(contour_points, CvType.CV_32F);
        RotatedRect ellipse = Imgproc.fitEllipse(contour_points);

        //check major and minor axis
        float axis1 = ellipse.size.width;
        float axis2 = ellipse.size.height;

        float major_axis = axis1 > axis2 ? axis1 : axis2;
        float minor_axis = axis1 > axis2 ? axis2 : axis1;

        //TODO: check major axis is certain amount more than minor axis

        //print angle
        System.out.println(ellipse.angle);

        //draw contours + centroid

        Imgproc.drawContours(blured, contours, largestIdx, new Scalar(0,255,0), 5);
        Imgproc.circle(blured, centroid, 3, new Scalar(0,0,0), 3);

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