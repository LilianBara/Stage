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
    void media();
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

private :
    bool debugActif = false;
    bool settings = false;
    bool photo = false;
    bool newBox = true;
    bool resizeWindow = true;
    bool imageHided = false;
    bool timerActive = false;

    vector<string> labels;

    string profil;
    string treatmentText;

    Mat image;

    int labelCount =0;
    int sensivity = 50;
    int frameInterval = 50;

    vector<Mat> facesFrame;
    vector<vector<int>> elderBoxOfBox;

    VideoCapture cap;

    QGridLayout *main_layout = new QGridLayout();
    QGridLayout *text_layout = new QGridLayout();

    QGraphicsScene *imageScene;
    QGraphicsView *imageView;

    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *mediaButton;
    QPushButton *settingButton;
    QPushButton *hideButton;

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

    QTimer *timerCamera;

    QMouseEvent *event;
    QMenu *cameraMenu;
    QAction *camera[5];
    QPoint *positionCamButton;





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
