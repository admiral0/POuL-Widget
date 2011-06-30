#include "poulwidget.h"

#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include "poulstatus.h"
#include <sys/stat.h>
#include <QPushButton>
#include <QSettings>
#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>

PoulWidget::PoulWidget(QWidget *parent) :
    QWidget(parent)
{
    prefs=new QSettings;
    format=new QString();//TODO Load from settings 
    *format=prefs->value("format","%o %D/%M/%Y %h:%m:%s").toString();
    show_icon=prefs->value("show_icon",true).toBool();
    
    
    netstatus=new PoulStatus(60000);
    setAttribute(Qt::WA_TranslucentBackground);
    layout=new QHBoxLayout(this);
    icon=new QLabel;
    status=new QLabel;
    status->setText("Waiting...");
    refresh=new QPushButton();
    refresh->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    refresh->setIcon(QIcon::fromTheme("view-refresh"));
    if(show_icon)
        layout->addWidget(icon);
    layout->addWidget(status);
    layout->addWidget(refresh);
    setLayout(layout);
    pic_c = new QPixmap();
    pic_c->load(":./poulwidget.png");
    QSize s=sizeHint();
    pic_w = new QPixmap();
    pic_w->load(":./poulwidget_w.png");
    
    

    
    icon->setPixmap(pic_c->scaledToHeight(s.height()/4,Qt::SmoothTransformation));
    connect(netstatus,SIGNAL(changed(QString)),SLOT(updateWidget(QString)));
    connect(refresh,SIGNAL(clicked(bool)),netstatus,SLOT(updateStatus()));
//     connect(refresh,SIGNAL(clicked(bool)),this,SLOT(showSettings()));
    netstatus->start();
}

PoulWidget::~PoulWidget()
{
    prefs->setValue("format", *format);
    prefs->setValue("show_icon",show_icon);
    delete prefs;
    delete icon;
    delete status;
    delete refresh;
    delete format;
    delete netstatus;
    delete pic_c;
    delete pic_w;
    delete layout;
}


void PoulWidget::showSettings(){
    QDialog dialog;
    QVBoxLayout layout;
    QHBoxLayout inner;
    QCheckBox box;
    box.setChecked(show_icon);
    box.setText("Show Icon?");
    QLabel desc;
    desc.setText("Display format:");
    QLineEdit ed_line;
    ed_line.setText(*format);
    inner.addWidget(&desc);
    inner.addWidget(&ed_line);
    layout.addWidget(&box);
    layout.addLayout(&inner);
    dialog.setLayout(&layout);
    dialog.exec();
    netstatus->updateStatus();
    *format=ed_line.text();
    show_icon=box.isChecked();
    prefs->setValue("format", *format);
    prefs->setValue("show_icon",show_icon);
}

QSize PoulWidget::sizeHint()
{
    return 2 * QWidget::sizeHint();
}


void PoulWidget::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setBrush(QColor(0, 0, 0, 128));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect(), 25, 25);
    p.end();
    
    QWidget::paintEvent(event);
}
void PoulWidget::updateWidget(QString line)
{
    QString date,month,year,hour,minute,second;
    bool open,manual;
    PoulStatus::populate(line,&date,&month,&year,&hour,&minute,&second,&open,&manual);
    QString tmp=*format;
    tmp.replace("%o", (open) ? "Open" : "Closed");
    tmp.replace("%t", (manual) ? "Manual" : "BITS");
    tmp.replace("%D",date);
    tmp.replace("%M",month);
    tmp.replace("%Y",year);
    tmp.replace("%h",hour);
    tmp.replace("%m",minute);
    tmp.replace("%s",second);
    status->setText(tmp);
    QSize s=sizeHint();
    if(open){
        icon->setPixmap(pic_c->scaledToHeight(s.height()/4,Qt::SmoothTransformation));
    }else{
        icon->setPixmap(pic_w->scaledToHeight(s.height()/4,Qt::SmoothTransformation));
    }
}


#include "poulwidget.moc"