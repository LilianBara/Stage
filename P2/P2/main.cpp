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
    //CAM
//    VideoCapture cap(0);

    //VIDEO
//    string fileName = "/home/digital/Documents/GitHub/Stage/P2/video.mp4";
//    VideoCapture cap(fileName, CAP_FFMPEG);

    //PHOTO
    string fileName = "/home/digital/Documents/GitHub/Stage/P2/photo.jpeg";
    VideoCapture cap(fileName);

    Mat image, croppedImage, image227, image300;

    Scalar meanValues(78.4263377603, 87.7689143744, 114.895847746);

    // FACE DETECTION
    Net net = readNet("/home/digital/Documents/GitHub/Stage/P2/res10_300x300_ssd_iter_140000.caffemodel",
                      "/home/digital/Documents/GitHub/Stage/P2/deploy.prototxt.txt",
                      "Caffe");

    // GENDER
    Net genderNet = readNet("/home/digital/Documents/GitHub/Stage/P2/gender_model/gender_net.caffemodel",
                      "/home/digital/Documents/GitHub/Stage/P2/gender_model/deploy.prototxt",
                      "Caffe");

    vector<string> genderList = {"Homme", "Femme"};


    // AGE
    Net ageNet = readNet("/home/digital/Documents/GitHub/Stage/P2/age_model/age_net.caffemodel",
                      "/home/digital/Documents/GitHub/Stage/P2/age_model/deploy.prototxt",
                      "Caffe");

    vector<string> ageList = {"(0-2)", "(4-6)", "(8-12)", "(15-20)", "(25-32)", "(38-43)", "(48-53)", "(60-100)"};

    if(!cap.isOpened()){
        cout<<"Can't open video\n";
    }


    //BOUCLE
    while (cap.isOpened()) {
       cap.read(image);

       //CREATE BLOB 300x300
       resize(image, image300, Size(300,300));
       cv::Mat inputBlob300 = cv::dnn::blobFromImage(image, 1.0, Size(300, 300), meanValues, true,false);


       //FACE DETECTION
       net.setInput(inputBlob300, "data");
       Mat detection = net.forward("detection_out");
       cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

       vector<Mat> facesFrame;

       for(int i = 0; i < detectionMat.rows; i++)
       {
           float confidence = detectionMat.at<float>(i, 2);
           if(confidence > 0.4)
           {
               //GET FACE
               int box_x1 = static_cast<int>(detectionMat.at<float>(i, 3) * image.cols);
               int box_y1 = static_cast<int>(detectionMat.at<float>(i, 4) * image.rows);
               int box_x2 = static_cast<int>(detectionMat.at<float>(i, 5) * image.cols);
               int box_y2 = static_cast<int>(detectionMat.at<float>(i, 6) * image.rows);

               vector<int> box = {box_x1, box_y1, box_x2, box_y2};

               //GET FRAME TO CROP
               int box_width = static_cast<int>(detectionMat.at<float>(i, 5) * image.cols - box_x1);
               int box_height = static_cast<int>(detectionMat.at<float>(i, 6) * image.rows - box_y1);

               int width = box_width * 1.1;
               int height = box_height *1.1;

               int centre_x = box_x2 - box_width/2;
               int centre_y = box_y2 - box_height/2;

               //GET SQUARE FRAME
               if(width<height)
                   width = height;
               else
                   height = width;

               //RECENTRE
               int x = centre_x - width/2;
               int y = centre_y - height/2;

               //AVOID ROI OUT OF FRAME
               if(x + width > image.cols)
                   width = image.cols - x;

               if(y + height > image.rows)
                   height = image.rows - y;


               //GET ROI
               if (x >0 && y>0 && width >0 && height >0){
                   Rect ROI(x,y,width,height);
                   croppedImage = image(ROI);
                   facesFrame.push_back(croppedImage);
               }
               else{
                   croppedImage = image;
                   facesFrame.push_back(croppedImage);
               }

               //CREATE BLOB 227x277 FROM CROPPED IMAGE
               resize(croppedImage, image227, Size(227,227));
               cv::Mat inputBlob227 = cv::dnn::blobFromImage(image227, 1.0, Size(227, 227), meanValues);


               //DRAW RECTANGLE
               rectangle(image, Point(box_x1, box_y1), Point(box_x2, box_y2), Scalar(0, 255, 0),2, 4);


               //GENDER NET
               genderNet.setInput(inputBlob227);
               vector<float> genderPreds = genderNet.forward();
               int max_index_gender = distance(genderPreds.begin(), max_element(genderPreds.begin(), genderPreds.end()));
               string gender = genderList[max_index_gender];


               //AGE NET
               ageNet.setInput(inputBlob227);
               vector<float> agePreds = ageNet.forward();
               int max_indice_age = distance(agePreds.begin(), max_element(agePreds.begin(), agePreds.end()));
               string age = ageList[max_indice_age];


               //PUT LABEL
               string label = gender + ", " + age;
               putText(image, label, Point(box_x1, box_y1- 10),FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 1, LINE_AA);
           }
       }
       imshow("image", image);

       waitKey(5000);
       imshow("image", facesFrame[0]);
       waitKey(2000);
       imshow("image", facesFrame[1]);
       waitKey(2000);
       imshow("image", facesFrame[2]);
       waitKey(2000);

//       imshow("image", facesFrame[0]);

       waitKey(20);
       }

   cap.release();
   destroyAllWindows();
}
