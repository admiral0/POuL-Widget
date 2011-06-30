#ifndef POULWIDGET_H
#define POULWIDGET_H

#include <QWidget>

class QSettings;
class QPushButton;
class PoulStatus;
class QLabel;
class QHBoxLayout;
class PoulWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PoulWidget(QWidget *parent = 0);
    virtual ~PoulWidget();
    virtual void paintEvent(QPaintEvent* );
    virtual QSize sizeHint();

signals:

public slots:
    void showSettings();
    void updateWidget(QString line);
private:
    PoulStatus *netstatus;
    QLabel *icon;
    QLabel *status;
    QHBoxLayout *layout;
    QPixmap *pic_c;
    QPixmap *pic_w;
    QPushButton *refresh;
    
    QSettings* prefs;
    QDialog* prefs_ui;
    /* Settings */
    QString *format;
    bool show_icon;
};

#endif // POULWIDGET_H
