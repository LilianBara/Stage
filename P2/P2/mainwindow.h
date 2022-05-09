#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsScene>
#include <QDebug>
#include <QApplication>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include <QStandardItemModel>
#include <QGridLayout>
#include <QTimer>
#include <QSlider>
#include <QCameraInfo>
#include <QMessageBox>
#include <QCheckBox>
#include <QWidgetAction>
#include <QMouseEvent>
#include <QFont>
#include <QScreen>

#include <iostream>
#include <fstream>
#include <sstream>
#include <QString>
#include <stdlib.h>
#include <vector>

#include "opencv2/opencv.hpp"
#include "opencv2/dnn.hpp"
#include "opencv2/dnn/dnn.hpp"

using namespace std;
using namespace cv;


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

signals:
    void newFrame(cv::Mat *data);
    void newLabel();
    void elapsedTime();
    void mediaSelected(int);

private slots:
    void uploadImage(cv::Mat*);
    void faceResearch();
    void startTimer();
    void stopTimer();
    void selectMedia();
    void sensi(int);
    void uploadTimeLabel();
    void uploadListLabel();
    void timeBetweenImage(int);
    void imageTreatment(vector<int> actualBox, cv::Mat image);
    void initUI();
    void openPhoto();
    void openVideo();
    void openCam0();
    void openCam1();
    void openCam2();
    void setting();
    void hideImage();
    void selectMode();
    void setObjectMode();
    void setFaceMode();
    void checkCountMode();
    void objectResearch();
    void resizeWindows();
    std::string selectObject();
    void NMS(vector<int> *outClassIds, vector<cv::Rect> *outBoxes, vector<float> *outConfidences, vector<int> classIds, vector<float> confidences, vector<cv::Rect> box);
    void rectAndLabelObject(vector<int> outClassIds, vector<std::string> objectClasses, vector<cv::Rect> outBoxes, vector<float> outConfidences);
    void objectCounter(cv::Rect objectBox);
    void uploadCounter();


private :
    bool debugActif = false;
    bool settings = false;
    bool photo = false;
    bool resizeWindow = true;
    bool imageHided = false;
    bool timerActive = false;
    bool comptage = false;
    bool modeMenuSet = false;
    bool mediaMenuSet = false;
    bool personOnly = false;

    vector<string> labels;
    vector<string> objectClasses;

    string profil;
    string treatmentText;

    Mat image;

    int labelCount =0;
    int sensivity = 50;
    int frameInterval = 50;
    int modeSelected = -1;
    int compteur = 0;
    int newBox = 1;

    vector<Mat> facesFrame;
    vector<vector<int>> elderBoxOfBox;

    vector<Rect> tempObjectBox;

    VideoCapture cap;

    QGridLayout *main_layout = new QGridLayout();
    QGridLayout *text_layout = new QGridLayout();

    QGraphicsScene *imageScene;
    QGraphicsView *imageView;

    QCheckBox *objectToDetect;
    QCheckBox *countMode;

    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *mediaButton;
    QPushButton *settingButton;
    QPushButton *hideButton;
    QPushButton *modeButton;

    QSlider *sliderSens;
    QSlider *sliderInterval;

    QFont *font;
    QLabel *sliderSensText;
    QLabel *sliderSensMax;
    QLabel *sliderSensMin;
    QLabel *sliderIntervalText;
    QLabel *sliderIntervalMax;
    QLabel *sliderIntervalMin;
    QLabel *labelText;
    QLabel *labelTime;
    QLabel *objectToDetectText;
    QLabel *countText;
    QLabel *countModeText;

    QTimer *timerCamera;

    QMouseEvent *event;
    QMenu *cameraMenu;
    QMenu *modeMenu;
    QAction *camera[5];
    QAction *mode[2];
    QPoint *cursorPosition;

    // OBJECT DETECTION
    cv::dnn::Net objectNet = cv::dnn::readNet("/home/digital/Documents/GitHub/Stage/P2/yolov3/yolov3.weights",
                             "/home/digital/Documents/GitHub/Stage/P2/yolov3/yolov3.cfg",
                             "Darknet");
    string objectName;
    string objectNamesFile = "/home/digital/Documents/GitHub/Stage/P2/yolov3/coco.names";

    // FACE DETECTION
    cv::dnn::Net net = cv::dnn::readNet("/home/digital/Documents/GitHub/Stage/P2/face_detection/res10_300x300_ssd_iter_140000.caffemodel",
                      "/home/digital/Documents/GitHub/Stage/P2/face_detection/deploy.prototxt.txt",
                      "Caffe");

    // GENDER
    cv::dnn::Net genderNet = cv::dnn::readNet("/home/digital/Documents/GitHub/Stage/P2/gender_model/gender.caffemodel",
                            "/home/digital/Documents/GitHub/Stage/P2/gender_model/gender.prototxt",
                            "Caffe");

    vector<string> genderList = {"Femme", "Homme"};


    // AGE
    cv::dnn::Net ageNet = cv::dnn::readNet("/home/digital/Documents/GitHub/Stage/P2/age_model/dex_imdb_wiki.caffemodel",
                         "/home/digital/Documents/GitHub/Stage/P2/age_model/age.prototxt",
                         "Caffe");

    vector<string> ageList = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33",
                                 "34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66",
                                 "67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100"};


};

#endif // MAINWINDOW_H
