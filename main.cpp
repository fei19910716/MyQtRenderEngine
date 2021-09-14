
#include "mainwindow.h"
#include <QApplication>

#include "Components/ComponentManager.h"
#ifndef WIN32
#include <QSurfaceFormat>
#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifndef WIN32
    QSurfaceFormat glFormat;
    glFormat.setVersion(3,3);
    glFormat.setProfile(QSurfaceFormat :: CoreProfile);
    QSurfaceFormat :: setDefaultFormat(glFormat);
#endif
    CFEngineRender::ComponentManager::registerComponentDescriptions();
    MainWindow w;
    w.show();

    return a.exec();
}
