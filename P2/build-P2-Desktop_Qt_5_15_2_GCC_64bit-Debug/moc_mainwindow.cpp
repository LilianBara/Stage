/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../P2/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[55];
    char stringdata0[635];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "newFrame"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "cv::Mat*"
QT_MOC_LITERAL(4, 30, 4), // "data"
QT_MOC_LITERAL(5, 35, 8), // "newLabel"
QT_MOC_LITERAL(6, 44, 11), // "elapsedTime"
QT_MOC_LITERAL(7, 56, 13), // "mediaSelected"
QT_MOC_LITERAL(8, 70, 11), // "uploadImage"
QT_MOC_LITERAL(9, 82, 12), // "faceResearch"
QT_MOC_LITERAL(10, 95, 10), // "startTimer"
QT_MOC_LITERAL(11, 106, 9), // "stopTimer"
QT_MOC_LITERAL(12, 116, 11), // "selectMedia"
QT_MOC_LITERAL(13, 128, 5), // "sensi"
QT_MOC_LITERAL(14, 134, 15), // "uploadTimeLabel"
QT_MOC_LITERAL(15, 150, 15), // "uploadListLabel"
QT_MOC_LITERAL(16, 166, 16), // "timeBetweenImage"
QT_MOC_LITERAL(17, 183, 14), // "imageTreatment"
QT_MOC_LITERAL(18, 198, 11), // "vector<int>"
QT_MOC_LITERAL(19, 210, 9), // "actualBox"
QT_MOC_LITERAL(20, 220, 7), // "cv::Mat"
QT_MOC_LITERAL(21, 228, 5), // "image"
QT_MOC_LITERAL(22, 234, 6), // "initUI"
QT_MOC_LITERAL(23, 241, 9), // "openPhoto"
QT_MOC_LITERAL(24, 251, 9), // "openVideo"
QT_MOC_LITERAL(25, 261, 8), // "openCam0"
QT_MOC_LITERAL(26, 270, 8), // "openCam1"
QT_MOC_LITERAL(27, 279, 8), // "openCam2"
QT_MOC_LITERAL(28, 288, 7), // "setting"
QT_MOC_LITERAL(29, 296, 9), // "hideImage"
QT_MOC_LITERAL(30, 306, 10), // "selectMode"
QT_MOC_LITERAL(31, 317, 13), // "setObjectMode"
QT_MOC_LITERAL(32, 331, 11), // "setFaceMode"
QT_MOC_LITERAL(33, 343, 14), // "checkCountMode"
QT_MOC_LITERAL(34, 358, 14), // "objectResearch"
QT_MOC_LITERAL(35, 373, 13), // "resizeWindows"
QT_MOC_LITERAL(36, 387, 12), // "selectObject"
QT_MOC_LITERAL(37, 400, 11), // "std::string"
QT_MOC_LITERAL(38, 412, 3), // "NMS"
QT_MOC_LITERAL(39, 416, 12), // "vector<int>*"
QT_MOC_LITERAL(40, 429, 11), // "outClassIds"
QT_MOC_LITERAL(41, 441, 17), // "vector<cv::Rect>*"
QT_MOC_LITERAL(42, 459, 8), // "outBoxes"
QT_MOC_LITERAL(43, 468, 14), // "vector<float>*"
QT_MOC_LITERAL(44, 483, 14), // "outConfidences"
QT_MOC_LITERAL(45, 498, 8), // "classIds"
QT_MOC_LITERAL(46, 507, 13), // "vector<float>"
QT_MOC_LITERAL(47, 521, 11), // "confidences"
QT_MOC_LITERAL(48, 533, 16), // "vector<cv::Rect>"
QT_MOC_LITERAL(49, 550, 3), // "box"
QT_MOC_LITERAL(50, 554, 18), // "rectAndLabelObject"
QT_MOC_LITERAL(51, 573, 19), // "vector<std::string>"
QT_MOC_LITERAL(52, 593, 13), // "objectClasses"
QT_MOC_LITERAL(53, 607, 13), // "objectCounter"
QT_MOC_LITERAL(54, 621, 13) // "uploadCounter"

    },
    "MainWindow\0newFrame\0\0cv::Mat*\0data\0"
    "newLabel\0elapsedTime\0mediaSelected\0"
    "uploadImage\0faceResearch\0startTimer\0"
    "stopTimer\0selectMedia\0sensi\0uploadTimeLabel\0"
    "uploadListLabel\0timeBetweenImage\0"
    "imageTreatment\0vector<int>\0actualBox\0"
    "cv::Mat\0image\0initUI\0openPhoto\0openVideo\0"
    "openCam0\0openCam1\0openCam2\0setting\0"
    "hideImage\0selectMode\0setObjectMode\0"
    "setFaceMode\0checkCountMode\0objectResearch\0"
    "resizeWindows\0selectObject\0std::string\0"
    "NMS\0vector<int>*\0outClassIds\0"
    "vector<cv::Rect>*\0outBoxes\0vector<float>*\0"
    "outConfidences\0classIds\0vector<float>\0"
    "confidences\0vector<cv::Rect>\0box\0"
    "rectAndLabelObject\0vector<std::string>\0"
    "objectClasses\0objectCounter\0uploadCounter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  179,    2, 0x06 /* Public */,
       5,    0,  182,    2, 0x06 /* Public */,
       6,    0,  183,    2, 0x06 /* Public */,
       7,    1,  184,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,  187,    2, 0x08 /* Private */,
       9,    0,  190,    2, 0x08 /* Private */,
      10,    0,  191,    2, 0x08 /* Private */,
      11,    0,  192,    2, 0x08 /* Private */,
      12,    0,  193,    2, 0x08 /* Private */,
      13,    1,  194,    2, 0x08 /* Private */,
      14,    0,  197,    2, 0x08 /* Private */,
      15,    0,  198,    2, 0x08 /* Private */,
      16,    1,  199,    2, 0x08 /* Private */,
      17,    2,  202,    2, 0x08 /* Private */,
      22,    0,  207,    2, 0x08 /* Private */,
      23,    0,  208,    2, 0x08 /* Private */,
      24,    0,  209,    2, 0x08 /* Private */,
      25,    0,  210,    2, 0x08 /* Private */,
      26,    0,  211,    2, 0x08 /* Private */,
      27,    0,  212,    2, 0x08 /* Private */,
      28,    0,  213,    2, 0x08 /* Private */,
      29,    0,  214,    2, 0x08 /* Private */,
      30,    0,  215,    2, 0x08 /* Private */,
      31,    0,  216,    2, 0x08 /* Private */,
      32,    0,  217,    2, 0x08 /* Private */,
      33,    0,  218,    2, 0x08 /* Private */,
      34,    0,  219,    2, 0x08 /* Private */,
      35,    0,  220,    2, 0x08 /* Private */,
      36,    0,  221,    2, 0x08 /* Private */,
      38,    6,  222,    2, 0x08 /* Private */,
      50,    4,  235,    2, 0x08 /* Private */,
      53,    0,  244,    2, 0x08 /* Private */,
      54,    0,  245,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 20,   19,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 37,
    QMetaType::Void, 0x80000000 | 39, 0x80000000 | 41, 0x80000000 | 43, 0x80000000 | 18, 0x80000000 | 46, 0x80000000 | 48,   40,   42,   44,   45,   47,   49,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 51, 0x80000000 | 48, 0x80000000 | 46,   40,   52,   42,   44,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newFrame((*reinterpret_cast< cv::Mat*(*)>(_a[1]))); break;
        case 1: _t->newLabel(); break;
        case 2: _t->elapsedTime(); break;
        case 3: _t->mediaSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->uploadImage((*reinterpret_cast< cv::Mat*(*)>(_a[1]))); break;
        case 5: _t->faceResearch(); break;
        case 6: _t->startTimer(); break;
        case 7: _t->stopTimer(); break;
        case 8: _t->selectMedia(); break;
        case 9: _t->sensi((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->uploadTimeLabel(); break;
        case 11: _t->uploadListLabel(); break;
        case 12: _t->timeBetweenImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->imageTreatment((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< cv::Mat(*)>(_a[2]))); break;
        case 14: _t->initUI(); break;
        case 15: _t->openPhoto(); break;
        case 16: _t->openVideo(); break;
        case 17: _t->openCam0(); break;
        case 18: _t->openCam1(); break;
        case 19: _t->openCam2(); break;
        case 20: _t->setting(); break;
        case 21: _t->hideImage(); break;
        case 22: _t->selectMode(); break;
        case 23: _t->setObjectMode(); break;
        case 24: _t->setFaceMode(); break;
        case 25: _t->checkCountMode(); break;
        case 26: _t->objectResearch(); break;
        case 27: _t->resizeWindows(); break;
        case 28: { std::string _r = _t->selectObject();
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
        case 29: _t->NMS((*reinterpret_cast< vector<int>*(*)>(_a[1])),(*reinterpret_cast< vector<cv::Rect>*(*)>(_a[2])),(*reinterpret_cast< vector<float>*(*)>(_a[3])),(*reinterpret_cast< vector<int>(*)>(_a[4])),(*reinterpret_cast< vector<float>(*)>(_a[5])),(*reinterpret_cast< vector<cv::Rect>(*)>(_a[6]))); break;
        case 30: _t->rectAndLabelObject((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< vector<std::string>(*)>(_a[2])),(*reinterpret_cast< vector<cv::Rect>(*)>(_a[3])),(*reinterpret_cast< vector<float>(*)>(_a[4]))); break;
        case 31: _t->objectCounter(); break;
        case 32: _t->uploadCounter(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(cv::Mat * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::newFrame)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::newLabel)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::elapsedTime)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::mediaSelected)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 33;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::newFrame(cv::Mat * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::newLabel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::elapsedTime()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::mediaSelected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
