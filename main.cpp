
#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <QFile>

#include "Components/ComponentManager.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/qss/css/qss.css");
    if (!file.open(QIODevice::ReadOnly))
        exit(0);

    QTextStream in(&file);
    QString css = in.readAll();
    qApp->setStyleSheet(css);

#ifndef WIN32
    QSurfaceFormat glFormat;
    glFormat.setVersion(3,3);
    glFormat.setProfile(QSurfaceFormat :: CoreProfile);
    QSurfaceFormat :: setDefaultFormat(glFormat);
#endif
    render::ComponentManager::registerComponentDescriptions();
    MainWindow w;
    w.show();

    return a.exec();
}
