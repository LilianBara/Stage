#include "mainwindow.h"
#include "classlog.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt;

    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
        break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
        break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
        break;
    }
        ClassLog::log("/home/digital/Documents/GitHub/Stage/P2/","Qdebug",txt);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    qInstallMessageHandler(myMessageOutput);
    MainWindow window;
    window.setWindowTitle("Video");
    window.show();
    return app.exec();
}
