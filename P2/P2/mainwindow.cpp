#include "mainwindow.h"

cv::Scalar meanValues(78.4263377603, 87.7689143744, 114.895847746);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    cameraMenu(nullptr)
{
    initUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI(){
    //LAYOUT
    QGridLayout *image_layout = new QGridLayout();
    QGridLayout *button_layout = new QGridLayout();

    main_layout->addLayout(image_layout, 0, 0, 4, 5);
    main_layout->addLayout(button_layout, 0, 5, 0, 1);
    main_layout->addLayout(text_layout, 4, 0, 1, 5);

    //IMAGE
    imageScene = new QGraphicsScene(this);
    imageView = new QGraphicsView(imageScene);
    image_layout->setContentsMargins(0,0,0,0);
    image_layout->addWidget(imageView);
    connect(this, &MainWindow::newFrame, this,&MainWindow::uploadImage);

    //STOP BUTTON
    stopButton = new QPushButton(this);
    stopButton->setText("Stop");
    stopButton->setStyleSheet("QPushButton { background-color : red; }");
    button_layout->addWidget(stopButton, 3, 0, 1, 3);
    connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stopTimer()));
    stopButton->hide();

    //START BUTTON
    startButton = new QPushButton(this);
    startButton->setText("Start");
    startButton->setStyleSheet("QPushButton { background-color : green; }");
    button_layout->addWidget(startButton, 2, 0, 1, 3);
    connect(startButton, SIGNAL(clicked(bool)), this, SLOT(startTimer()));

    //SETTING BUTTON
    settingButton = new QPushButton(this);
    settingButton->setText("⚙");
    settingButton->setStyleSheet("QPushButton { background-color : white; }");
    button_layout->addWidget(settingButton, 13, 2, 1, 1);
    connect(settingButton, SIGNAL(clicked(bool)), this, SLOT(setting()));

    //MEDIA BUTTON
    mediaButton = new QPushButton(this);
    mediaButton->setText("Média");
    mediaButton->setStyleSheet("QPushButton { background-color : blue; }");
    button_layout->addWidget(mediaButton, 1, 0, 1, 3);
    connect(mediaButton, SIGNAL(clicked(bool)), this, SLOT(media()));

    //HIDE IMAGE BUTTON
    hideButton = new QPushButton(this);
    hideButton->setText("Cacher image");
    hideButton->setStyleSheet("QPushButton { background-color : white; }");
    button_layout->addWidget(hideButton, 13, 0, 1, 2);
    connect(hideButton, SIGNAL(clicked(bool)), this, SLOT(hideImage()));

    //MODE BUTTON
    modeButton = new QPushButton(this);
    modeButton->setText("Mode");
    modeButton->setStyleSheet("QPushButton { background-color : cadetblue; }");
    button_layout->addWidget(modeButton, 0, 0, 1, 3);
    connect(modeButton, SIGNAL(clicked(bool)), this, SLOT(selectMode()));


    //SLIDER SENSIVITY
    sliderSens = new QSlider(this);
    sliderSens->setMinimum(10);
    sliderSens->setMaximum(200);
    sliderSens->setValue(50);
    button_layout->addWidget(sliderSens, 7, 0 , 1, 3, Qt::Alignment(Qt::AlignHCenter));
    connect(sliderSens, SIGNAL(valueChanged(int)), this, SLOT(sensi(int)));
    sliderSens->hide();

    //SLIDER SENSIVITY TEXT
    sliderSensText = new QLabel(this);
    sliderSensText->setText("Faire varier sensibilité\n        de détection");
    button_layout->addWidget(sliderSensText, 5, 0 , 1, 3, Qt::Alignment(Qt::AlignHCenter));
    sliderSensText->hide();

    sliderSensMax = new QLabel(this);
    sliderSensMax->setText("200p");

    QFont font = sliderSensMax->font();
    font.setPointSize(10);
    font.setBold(true);

    sliderSensMax->setFont(font);
    button_layout->addWidget(sliderSensMax, 6, 0 , 1, 3, Qt::Alignment(Qt::AlignHCenter));
    sliderSensMax->hide();

    sliderSensMin = new QLabel(this);
    sliderSensMin->setText("10p");
    sliderSensMin->setFont(font);
    button_layout->addWidget(sliderSensMin, 8, 0 , 1, 3, Qt::Alignment(Qt::AlignHCenter));
    sliderSensMin->hide();

    //SLIDER INTERVAL
    sliderInterval = new QSlider(this);
    sliderInterval->setMinimum(1);
    sliderInterval->setMaximum(200);
    sliderInterval->setValue(50);
    button_layout->addWidget(sliderInterval, 11, 0 , 1, 3, Qt::Alignment(Qt::AlignHCenter));
    connect(sliderInterval, SIGNAL(valueChanged(int)), this, SLOT(timeBetweenImage(int)));
    sliderInterval->hide();

    //SLIDER INTERVAL TEXT
    sliderIntervalText = new QLabel(this);
    sliderIntervalText->setText("Faire varier le temps\n    entre les images");
    button_layout->addWidget(sliderIntervalText, 9, 0 , 1, 3, Qt::Alignment(Qt::AlignHCenter));
    sliderIntervalText->hide();

    sliderIntervalMax = new QLabel(this);
    sliderIntervalMax->setText("200ms");
    sliderIntervalMax->setFont(font);
    button_layout->addWidget(sliderIntervalMax, 10, 0 , 1, 3, Qt::Alignment(Qt::AlignHCenter));
    sliderIntervalMax->hide();

    sliderIntervalMin = new QLabel(this);
    sliderIntervalMin->setText("1ms");
    sliderIntervalMin->setFont(font);
    button_layout->addWidget(sliderIntervalMin, 12, 0 , 1, 3, Qt::Alignment(Qt::AlignHCenter));
    sliderIntervalMin->hide();


    //LABEL
    connect(this, &MainWindow::newLabel, this,&MainWindow::uploadListLabel);
    connect(this, &MainWindow::elapsedTime, this,&MainWindow::uploadTimeLabel);

    QWidget *imageWidget = new QWidget();
    imageWidget->setLayout(main_layout);
    setCentralWidget(imageWidget);
}

void MainWindow::media(){
    if(timerActive)
        return;

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    QString info = QString("Cameras disponibles: \n");
    cameraMenu = new QMenu(this);

    foreach (const QCameraInfo &cameraInfo, cameras){
        int i = 0;
        info = cameraInfo.deviceName();
        String device = info.toStdString();
        char ID = device.at(device.length() - 1);

        info = " - " + cameraInfo.description();
        camera[i] = new QAction(info, cameraMenu);
        cameraMenu->addAction(camera[i]);

        if(ID == '0'){
            connect(camera[i], SIGNAL(triggered(bool)), this, SLOT(openCam0()));
        }

        if(ID == '1'){
            connect(camera[i], SIGNAL(triggered(bool)), this, SLOT(openCam1()));
        }

        if(ID == '2'){
            connect(camera[i], SIGNAL(triggered(bool)), this, SLOT(openCam2()));
        }
        i++;
    }

    camera[3] = new QAction(" - Photo", cameraMenu);
    cameraMenu->addAction(camera[3]);
    connect(camera[3], SIGNAL(triggered(bool)), this, SLOT(openPhoto()));

    camera[4] = new QAction(" - Vidéo", cameraMenu);
    cameraMenu->addAction(camera[4]);
    connect(camera[4], SIGNAL(triggered(bool)), this, SLOT(openVideo()));

    QPoint cursorPosition = QCursor::pos();
    cameraMenu->popup(cursorPosition);
}

void MainWindow::selectMode(){
    if(timerActive)
        return;

    modeMenu = new QMenu(this);

    mode[0] = new QAction(" - Détection visage, âge et genre", cameraMenu);
    modeMenu->addAction(mode[0]);
    connect(mode[0], SIGNAL(triggered(bool)), this, SLOT(setModeVisage()));

    mode[1] = new QAction(" - Détection objets", cameraMenu);
    modeMenu->addAction(mode[1]);
    connect(mode[1], SIGNAL(triggered(bool)), this, SLOT(setModeObjet()));

    mode[2] = new QAction(" - Comptage personnes", cameraMenu);
    modeMenu->addAction(mode[2]);
    connect(mode[2], SIGNAL(triggered(bool)), this, SLOT(setModeComptage()));

    QPoint cursorPosition = QCursor::pos();
    modeMenu->popup(cursorPosition);
}

void MainWindow::openCam0(){
    cap.open(0);
    photo = false;
}

void MainWindow::openCam1(){
    cap.open(1);
    photo = false;
}

void MainWindow::openCam2(){
    cap.open(2);
    photo = false;
}

void MainWindow::openPhoto(){
    string fileName = "/home/digital/Documents/GitHub/Stage/P2/photo.jpeg";
    cap.open(fileName);
    cap.read(image);
    photo = true;
}

void MainWindow::openVideo(){
    string fileName = "/home/digital/Documents/GitHub/Stage/P2/video.mp4";
    cap.open(fileName, CAP_FFMPEG);
    photo = false;
}

void MainWindow::setModeVisage(){
    modeSelected = 0;
}

void MainWindow::setModeObjet(){
    modeSelected = 1;
}

void MainWindow::setModeComptage(){
    comptage = true;
}


void MainWindow::startTimer(){
    if(!cap.isOpened())
        return;

    timerCamera = new QTimer(this);

    if(modeSelected == 0){
        connect(timerCamera, SIGNAL(timeout()), this, SLOT(faceResearch()));
        disconnect(timerCamera, SIGNAL(timeout()), this, SLOT(objectResearch()));
    }
    if(modeSelected == 1){
        connect(timerCamera, SIGNAL(timeout()), this, SLOT(objectResearch()));
        disconnect(timerCamera, SIGNAL(timeout()), this, SLOT(faceResearch()));
    }

    timerCamera->setInterval(frameInterval);

    if(photo){
        timerCamera->setSingleShot(true);
        settingButton->hide();
    }
    else{
        timerCamera->setSingleShot(false);
        settingButton->show();
    }
    timerCamera->start();
    timerActive = true;
    startButton->hide();
    stopButton->show();
    resizeWindow = true;
}

void MainWindow::stopTimer(){
    timerCamera->stop();
    timerActive = false;
    timerCamera->deleteLater();
    stopButton->hide();
    startButton->show();
}


void MainWindow::setting(){
    if(!settings){
        settingButton->setStyleSheet("QPushButton { background-color : grey; }");
        sliderIntervalMin->show();
        sliderIntervalMax->show();
        sliderIntervalText->show();
        sliderInterval->show();
        sliderSensMin->show();
        sliderSensMax->show();
        sliderSensText->show();
        sliderSens->show();
        settings = true;
    }
    else{
        settingButton->setStyleSheet("QPushButton { background-color : white; }");
        sliderIntervalMin->hide();
        sliderIntervalMax->hide();
        sliderIntervalText->hide();
        sliderInterval->hide();
        sliderSensMin->hide();
        sliderSensMax->hide();
        sliderSensText->hide();
        sliderSens->hide();
        settings = false;
    }
}

void MainWindow::hideImage(){
    if(!imageHided){
        hideButton->setStyleSheet("QPushButton { background-color : grey; }");
        imageView->hide();
        imageHided = true;
    }
    else{
        hideButton->setStyleSheet("QPushButton { background-color : white; }");
        imageView->show();
        imageHided = false;
    }
}


void MainWindow::faceResearch(){
    Mat image300;
    if (!photo)
        cap.read(image);

    if(resizeWindow){
        int width = image.cols *1.34;
        int height = image.rows*1.325;

        QSize size = qApp->screens()[0]->size();

        if(width>size.width())
            width = size.width();

        if(height>size.height())
                height = size.height();

        this->resize(width,height);
        resizeWindow = false;
    }

    //INIT ELDERBOX
    for(int b = 0; b < 10; b++){
        vector<int> voidBox = {0,0,0,0};
        elderBoxOfBox.push_back(voidBox);
    }

   //CREATE BLOB 300x300
   cv::resize(image, image300, Size(300,300));
   cv::Mat inputBlob300 = cv::dnn::blobFromImage(image, 1.0, Size(300, 300), meanValues, true,false);

   //FACE DETECTION
   net.setInput(inputBlob300, "data");
   Mat detection = net.forward("detection_out");
   cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

   vector<vector<int>> boxOfBox;


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

           vector<int> actualBox = {box_x1, box_y1, box_x2, box_y2};
           boxOfBox.push_back(actualBox);

           newBox = true;
           //TEST NEW BOX
           for(unsigned long b = 0; b < elderBoxOfBox.size(); b++){
               if(actualBox[0] <= elderBoxOfBox[b][0] + sensivity
                    && actualBox[0] >= elderBoxOfBox[b][0] - sensivity
                    && actualBox[1] <= elderBoxOfBox[b][1] + sensivity
                    && actualBox[1] >= elderBoxOfBox[b][1] - sensivity){
                         newBox = false;
               }
           }

           if(newBox == true){
               imageTreatment(actualBox, image);
               elderBoxOfBox = boxOfBox;
           }

           //DRAW RECTANGLE
           rectangle(image, Point(actualBox[0], actualBox[1]), Point(actualBox[2], actualBox[3]), Scalar(0, 255, 0),2, 4);
        }

        //PUT LIST OF LABEL
        if(labels.size() > elderBoxOfBox.size()){
            vector<string> temp = labels;

            for(unsigned long b = 0; b <labels.size(); b++)
                temp[b] = labels[b];

            labels.clear();
            for(unsigned long b = temp.size() -1; b > 0; b--)
                labels.push_back(temp[b]);

            temp.clear();
            for(unsigned long b = labels.size() ; b != elderBoxOfBox.size(); b--)
                labels.pop_back();
            emit newLabel();
        }

        emit newFrame(&image);
   }
}

void MainWindow::imageTreatment(vector<int> actualBox, Mat image){
    Mat croppedImage, image224;

    int treatmentStarted = cv::getTickCount();

    //GET FRAME TO CROP
    int box_width = actualBox[2] - actualBox[0];
    int box_height = actualBox[3] - actualBox[1];

    int width = box_width * 1.1;
    int height = box_height *1.2;

    int centre_x = actualBox[2] - box_width/2;
    int centre_y = actualBox[3] - box_height/1.8;

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

    qDebug()<<x<<y<<width<<height;

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

    //CREATE BLOB 224x224 FROM CROPPED IMAGE
    cv::resize(croppedImage, image224, Size(224,224));
    cv::Mat inputBlob224 = cv::dnn::blobFromImage(image224, 1.0, Size(224, 224), meanValues);


    //GENDER NET
    genderNet.setInput(inputBlob224);
    vector<float> genderPreds = genderNet.forward();
    int max_index_gender = distance(genderPreds.begin(), max_element(genderPreds.begin(), genderPreds.end()));
    string gender = genderList[max_index_gender];


    //AGE NET
    ageNet.setInput(inputBlob224);
    vector<float> agePreds = ageNet.forward();
    int max_indice_age = distance(agePreds.begin(), max_element(agePreds.begin(), agePreds.end()));
    string age = ageList[max_indice_age];


    //STOCK LABEL
    string label = gender + ", " + age;
    putText(image, label, Point(actualBox[0], actualBox[1]- 10),FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 1, LINE_AA);
    labels.push_back(label);

    int treatmentEnded = cv::getTickCount();
    double treatmentTime = (treatmentEnded-treatmentStarted) /cv::getTickFrequency();
    treatmentText = "Temps de traitement : " + to_string(treatmentTime) + " s";

    emit newLabel();
    emit elapsedTime();
}

void MainWindow::objectResearch(){
    if (!photo)
        cap.read(image);

    if(resizeWindow){
        int width = image.cols *1.34;
        int height = image.rows*1.325;

        QSize size = qApp->screens()[0]->size();

        if(width>size.width())
            width = size.width();

        if(height>size.height())
                height = size.height();

        this->resize(width,height);
        resizeWindow = false;
    }

    int inputWidth = 416;
    int inputHeight = 416;

    int treatmentStarted = cv::getTickCount();

    ifstream ifs(objectNamesFile.c_str());
    while(getline(ifs, objectName))
        objectClasses.push_back(objectName);

    cv::Mat blob;
    cv::dnn::blobFromImage(image, blob, 1 / 255.0, cv::Size(inputWidth, inputHeight), cv::Scalar(0, 0, 0), true, false);

    objectNet.setInput(blob);

    // forward
    static vector<string> names;
    vector<int> outLayers = objectNet.getUnconnectedOutLayers();
    vector<string> layersNames = objectNet.getLayerNames();
    names.resize(outLayers.size());

    for (size_t i = 0; i < outLayers.size(); ++i)
        names[i] = layersNames[outLayers[i] - 1];

    vector<cv::Mat> outs;
    objectNet.forward(outs, names);

    // remove the bounding boxes with low confidence
    vector<int> outClassIds;
    vector<float> outConfidences;
    vector<cv::Rect> outBoxes;

    float confThreshold = 0.5; // confidence threshold
    float nmsThreshold = 0.4;  // non-maximum suppression threshold

    vector<int> classIds;
    vector<float> confidences;
    vector<cv::Rect> boxes;

    for (size_t i = 0; i < outs.size(); ++i) {
        float* data = (float*)outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
        {
            cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            cv::Point classIdPoint;
            double confidence;
            // get the value and location of the maximum score
            cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > confThreshold)
            {
                int centerX = (int)(data[0] * image.cols);
                int centerY = (int)(data[1] * image.rows);
                int width = (int)(data[2] * image.cols);
                int height = (int)(data[3] * image.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(cv::Rect(left, top, width, height));
            }
        }
    }

    // non maximum suppression
    vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
    for (size_t i = 0; i < indices.size(); ++i) {
        int idx = indices[i];
        outClassIds.push_back(classIds[idx]);
        outBoxes.push_back(boxes[idx]);
        outConfidences.push_back(confidences[idx]);
    }

    for(size_t i = 0; i < outClassIds.size(); i ++) {
        cv::rectangle(image, outBoxes[i], cv::Scalar(0, 0, 255));

        // get the label for the class name and its confidence
        string label = objectClasses[outClassIds[i]];
        label += cv::format(":%.2f", outConfidences[i]);

        // display the label at the top of the bounding box
        int baseLine;
        cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        int left = outBoxes[i].x, top = outBoxes[i].y;
        top = max(top, labelSize.height);
        cv::putText(image, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255));
    }
    int treatmentEnded = cv::getTickCount();
    double treatmentTime = (treatmentEnded-treatmentStarted) /cv::getTickFrequency();
    treatmentText = "Temps de traitement : " + to_string(treatmentTime) + " s";

    emit elapsedTime();
    emit newFrame(&image);
}


void MainWindow::sensi(int sensi){
    sensivity = sensi;
}

void MainWindow::timeBetweenImage(int nb){
    frameInterval = nb;
    timerCamera->stop();
    timerCamera->deleteLater();
    startTimer();
}


void MainWindow::uploadListLabel(){
    labelText = new QLabel(this);
    labelText->setStyleSheet("QLabel { background-color : white; }");
    string temp1;
    for(unsigned long m = 0; m<labels.size(); m++){
        temp1 = temp1 + labels[m] + " | ";
    }

    labelText->setText(QString::fromStdString("Personnes détectées : " +temp1));
    text_layout->addWidget(labelText, 0, 0 , 1, 6);
}

void MainWindow::uploadTimeLabel(){
    labelTime = new QLabel(this);
    labelTime->setStyleSheet("QLabel { background-color : white; }");
    labelTime->setText(QString::fromStdString(treatmentText));
    text_layout->addWidget(labelTime, 1, 0 , 1, 6);
}

void MainWindow::uploadImage(Mat *mat){
    if(!imageHided){
        Mat f;
        cv::cvtColor(*mat, f, cv::COLOR_BGR2RGB);

        QImage frame(
                f.data,
                f.cols,
                f.rows,
                f.step,
                QImage::Format_RGB888);

        QPixmap PixImage;
        PixImage.convertFromImage(frame);


        imageScene->clear();
        imageView->resetTransform();
        imageScene->addPixmap(PixImage);
        imageScene->update();
        imageView->setSceneRect(PixImage.rect());
    }
    else
        return;
}

