#include <iostream>
#include <fstream>
#include <QString>
#include "opencv2/opencv.hpp"
#include "opencv2/dnn.hpp"
#include "opencv2/dnn/dnn.hpp"
//#include "opencv2/dnn/all_layers.hpp"
#include <QDebug>

using namespace std;
using namespace cv;
using namespace dnn;


int main(int, char**) {
    VideoCapture cap(0);
    Mat image;
    cap.read(image);

    Scalar meanValues = (78.4263377603, 87.7689143744, 114.895847746);

    // FACE
    Net net = readNet("/home/lilian/Documents/GitHub/Projets/P2/res10_300x300_ssd_iter_140000_fp16.caffemodel",
                      "/home/lilian/Documents/GitHub/Projets/P2/deploy.prototxt",
                      "Caffe");

    // GENDER
    Net genderNet = readNet("/home/lilian/Documents/GitHub/Projets/P2/gender_net.caffemodel",
                      "/home/lilian/Documents/GitHub/Projets/P2/deploy_gender.prototxt",
                      "Caffe");

    vector<string> genderList = {"Male", "Female"};


    // AGE
    Net ageNet = readNet("/home/lilian/Documents/GitHub/Projets/P2/age_net.caffemodel",
                      "/home/lilian/Documents/GitHub/Projets/P2/deploy_age.prototxt",
                      "Caffe");

    vector<string> ageList = {"(0-2)", "(4-6)", "(8-12)", "(15-20)", "(25-32)", "(38-43)", "(48-53)", "(60-100)"};

    //BOUCLE
   while (cap.isOpened()) {
       Mat image300, image227;
       resize(image, image300, Size(300,300));
       resize(image, image227, Size(227,227));

       cv::Mat inputBlob300 = cv::dnn::blobFromImage(image300, 1.0, Size(300, 300), meanValues, true, false);
       cv::Mat inputBlob227 = cv::dnn::blobFromImage(image227, 1.0, Size(227, 227), meanValues, true, false);


       //GENDER
       genderNet.setInput(inputBlob227);
       vector<float> genderPreds =genderNet.forward();

       int max_index_gender = std::distance(genderPreds.begin(), max_element(genderPreds.begin(), genderPreds.end()));
       string gender = genderList[max_index_gender];


       //AGE
       ageNet.setInput(inputBlob227);
       vector<float> agePreds = ageNet.forward();
       int max_indice_age = distance(agePreds.begin(), max_element(agePreds.begin(), agePreds.end()));
       string age = ageList[max_indice_age];


       //DETECTION
       net.setInput(inputBlob300);
       qDebug()<<"1";
       Mat detection = net.forward();
       cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

//       vector<float> detection = net.forward();
//       qDebug()<<"1";
//       float *p;
//       p = &detection[0];
//       Mat detectionMat(3, 227, CV_32F, *p);

       vector<vector<int>> bboxes;
       for(int i = 0; i < detectionMat.rows; i++)
       {
           float confidence = detectionMat.at<float>(i, 2);
           if(confidence > 0.4)
           {
               int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * 300);
               int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * 300);
               int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * 300);
               int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * 300);

               vector<int> box = {x1, y1, x2, y2};
               bboxes.push_back(box);
               cv::rectangle(image, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0),2, 4);
               string label = gender + ", " + age; // label
               cv::putText(box, label, Point(x1, y1),cv::FONT_HERSHEY_SIMPLEX, 0.9, Scalar(0, 255, 255), 2, cv::LINE_AA);
           }
       }

       imshow("image", image);
      }

   cap.release();
   destroyAllWindows();
}
