#include <iostream>
#include <fstream>
#include <sstream>
#include <QString>
#include "opencv2/opencv.hpp"
#include "opencv2/dnn.hpp"
#include "opencv2/dnn/dnn.hpp"
#include <QDebug>

using namespace std;
using namespace cv;
using namespace dnn;


int main(int, char**) {
    VideoCapture cap(0);
    Mat image;

    Scalar meanValues = (78.4263377603, 87.7689143744, 114.895847746);

    // FACE DETECTION
    Net net = readNet("/home/digital/Documents/GitHub/Stage/P2/res10_300x300_ssd_iter_140000.caffemodel",
                      "/home/digital/Documents/GitHub/Stage/P2/deploy.prototxt.txt",
                      "Caffe");

    // GENDER
    Net genderNet = readNet("/home/digital/Documents/GitHub/Stage/P2/gender_net.caffemodel",
                      "/home/digital/Documents/GitHub/Stage/P2/deploy_gender.prototxt",
                      "Caffe");

    vector<string> genderList = {"Male", "Female"};


    // AGE
    Net ageNet = readNet("/home/digital/Documents/GitHub/Stage/P2/age_model2/age_net.caffemodel",
                      "/home/digital/Documents/GitHub/Stage/P2/age_model2/deploy.prototxt",
                      "Caffe");

    vector<string> ageList = {"(0-2)", "(4-6)", "(8-12)", "(15-20)", "(25-32)", "(38-43)", "(48-53)", "(60-100)"};



    //BOUCLE
    while (cap.isOpened()) {
       cap.read(image);

       //CREATE BLOB 300x300
       cv::Mat inputBlob = cv::dnn::blobFromImage(image, 1.0, Size(300, 300), meanValues,true,false);

       //CREATE BLOB 227x277
       Mat  image227;
       resize(image, image227, Size(227,227));
       cv::Mat inputBlob227 = cv::dnn::blobFromImage(image227, 1.0, Size(227, 227), meanValues);

       //FACE DETECTION
       net.setInput(inputBlob, "data");
       Mat detection = net.forward("detection_out");
       cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

       vector<Mat> facesFrame;

       for(int i = 0; i < detectionMat.rows; i++)
       {
           float confidence = detectionMat.at<float>(i, 2);
           if(confidence > 0.4)
           {
               //GET FACE FRAME
               int box_x1 = static_cast<int>(detectionMat.at<float>(i, 3) * image.cols);
               int box_y1 = static_cast<int>(detectionMat.at<float>(i, 4) * image.rows);
               int box_x2 = static_cast<int>(detectionMat.at<float>(i, 5) * image.cols);
               int box_y2 = static_cast<int>(detectionMat.at<float>(i, 6) * image.rows);

               vector<int> box = {box_x1, box_y1, box_x2, box_y2};
               int box_width = static_cast<int>(detectionMat.at<float>(i, 5) * image.cols - box_x1);
               int box_height = static_cast<int>(detectionMat.at<float>(i, 6) * image.rows - box_y1);
               Rect ROI(box_x1,box_y1,box_width,box_height);
               Mat croppedImage = image(ROI);
               facesFrame.push_back(croppedImage);

               //DRAW RECTANGLE
               rectangle(image, Point(box_x1, box_y1), Point(box_x2, box_y2), Scalar(0, 255, 0),2, 4);


               //GENDER
               genderNet.setInput(inputBlob227);
               vector<float> genderPreds = genderNet.forward();
               int max_index_gender = distance(genderPreds.begin(), max_element(genderPreds.begin(), genderPreds.end()));
               string gender = genderList[max_index_gender];


               //AGE
               ageNet.setInput(inputBlob227);
               vector<float> agePreds = ageNet.forward();
               int max_indice_age = distance(agePreds.begin(), max_element(agePreds.begin(), agePreds.end()));
               string age = ageList[max_indice_age];


               //PUT LABEL
               string label = gender + ", " + age;
               putText(image, label, Point(box_x1, box_y1- 10),FONT_HERSHEY_SIMPLEX, 0.9, Scalar(0, 255, 0), 1, LINE_AA);
           }
       }
       imshow("image", image);
       //imshow("image", facesFrame[0]);
       waitKey(20);
       }

   cap.release();
   destroyAllWindows();
}
