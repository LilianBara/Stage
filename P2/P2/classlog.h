#ifndef CLASSLOG_H
#define CLASSLOG_H
#include <QString>
#include <QStringList>
#include <QDir>
#include <QTextStream>
#include <qdatetime.h>
#include <QDebug>
#include <QSysInfo>
//#include "systeme.h"

#ifdef ALLINONE
#define DIRLOG  "DATA/LOG/"
#else
#define DIRLOG  "../DATA/LOG/"
#endif


class ClassLog
{
public:
    ClassLog();
    static void clean(QString path);
    static void log(QString path,QString titre,QString text);
    static void logUnJour(QString path,QString titre,QString text);
};

#endif // CLASSLOG_H
