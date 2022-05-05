TEMPLATE = app
QT += gui core multimedia widgets

CONFIG += c++17
CONFIG -= app_bundle

TARGET = Video

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix: !mac {
    INCLUDEPATH += /usr/local/include/opencv4
    LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_video -lopencv_videoio -lopencv_objdetect -lopencv_face -lopencv_highgui -lopencv_dnn
}

unix: mac {
    INCLUDEPATH += /path/to/opencv/include/opencv4
    LIBS += -L/path/to/opencv/lib -lopencv_world
}

win32 {
    INCLUDEPATH += c:/path/to/opencv/include/opencv4
    LIBS += -lc:/path/to/opencv/lib/opencv_world
}

SOURCES += \
        classlog.cpp \
        main.cpp \
        mainwindow.cpp

DEFINES += OPENCV_DATA_DIR=\\\"/usr/local/share/opencv4/\\\"
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    classlog.h \
    mainwindow.h
