
#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

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
