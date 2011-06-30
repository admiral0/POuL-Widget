#ifndef POULSTATUS_H
#define POULSTATUS_H

#include <QObject>

class QNetworkReply;
class QNetworkAccessManager;
class QTimer;

class PoulStatus : public QObject
{
    Q_OBJECT
public:
    explicit PoulStatus(int freq);
    virtual ~PoulStatus();
    void start();
    static void populate(QString line, QString* D, QString* M, QString* Y, QString* h, QString* m, QString* s, bool* o, bool* b);
signals:
    void changed(QString);

public slots:
    void updateStatus();
private slots:
    void updateStatus_callback();
private:
    QTimer *tmr;
    int time;
    QString cache;
    QNetworkAccessManager *mgr;
    QNetworkReply *reply;
};

#endif // POULSTATUS_H
