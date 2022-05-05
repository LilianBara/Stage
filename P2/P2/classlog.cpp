#include "classlog.h"
//#include "classparam.h"
//#include "wesync.h"


ClassLog::ClassLog()
{
}

void ClassLog::clean(QString path)
{
#define NBLOG 30
    QStringList filtres;
    QStringList listefichier;
    filtres<< "*.wepub";
    QDir repertoire(path);
    repertoire.setNameFilters(filtres);
    listefichier=repertoire.entryList();
    int nbfichier=listefichier.count();
    if(nbfichier>NBLOG)
    {
        int i=0;

        listefichier.sort();
        foreach (QString nom, listefichier)
        {
            if(i<nbfichier-NBLOG)
            {
                QDir fichier;
                fichier.remove(path+nom);
            }
            i++;
        }
    }
}

void ClassLog::log(QString path,QString titre,QString text)
{
        QString nom = QDateTime::currentDateTime().toString("yy-MM-dd");
        QFile file(path + titre +"-"+ nom +".txt");
        // Ouverture du fichier configuration en ecriture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            qDebug() << "qERROR: " + QString(path) + titre +"-"+ nom+ ".txt write\n";
        }
        else
        {
            // Ecrasement du fichier configuration avec le nouveau parametre
            QTextStream flux(&file);
            QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
            flux << " [ti] " + time + " [ui] " + text + "\n";
            file.close();
        }
}

void ClassLog::logUnJour(QString path,QString titre,QString text)
{
    QFile file(path + titre +".txt");
    // Ouverture du fichier configuration en ecriture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "qERROR: " + QString(path) + " write\n";
    }
    else
    {
        // Ecrasement du fichier configuration avec le nouveau parametre
        QTextStream flux(&file);
        QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
        if(QSysInfo::productType() == "windows")
            flux << " [ti] " + time + " [ui] " + text + "\r\n";
        else
            flux << " [ti] " + time + " [ui] " + text + "\n";
        // qDebug() << " [ui] " << text;
        file.close();
    }
}



