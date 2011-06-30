#include "poulstatus.h"
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>

PoulStatus::PoulStatus(int freq): QObject()
{
    time=freq;
    tmr=new QTimer();
    tmr->setInterval(time);
    updateStatus();
}
void PoulStatus::start()
{
    tmr->start();
}

void PoulStatus::updateStatus()
{
   tmr->stop();
   mgr=new QNetworkAccessManager;
   reply = mgr->get(QNetworkRequest(QUrl("http://bits.poul.org/stslog.txt")));
   connect(reply,SIGNAL(finished()),this,SLOT(updateStatus_callback()));
}

void PoulStatus::updateStatus_callback()
{
    QString all=reply->readAll();
    QStringList lines=all.split("\n",QString::SkipEmptyParts);
    cache=lines.last();
    emit changed(cache);
    tmr->start();
}

PoulStatus::~PoulStatus()
{
    tmr->stop();
    delete tmr;
}
void PoulStatus::populate(QString line, QString *D, QString *M, QString *Y, QString *h, QString* m, QString* s, bool* o, bool* b)
{
    QStringList data=line.split("|");
    *o=data[0].toInt();
    *b=data[1].toInt();
    QStringList date=data[2].split("%2F");
    *D=date[0];
    *M=date[1];
    *Y=date[2];
    QStringList time=data[3].split("%3A");
    *h=time[0];
    *m=time[1];
    *s=time[2];
    
}


#include "poulstatus.moc"