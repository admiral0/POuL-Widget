#include "qmaemo5homescreenadaptor.h"
#include "poulwidget.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("PoulWidget");
    PoulWidget poul;
    QMaemo5HomescreenAdaptor *adaptor= new QMaemo5HomescreenAdaptor(&poul);
    adaptor->setSettingsAvailable(true);
    QObject::connect(adaptor,SIGNAL(settingsRequested()),&poul,SLOT(showSettings()));
    poul.show();
    return app.exec();
}
