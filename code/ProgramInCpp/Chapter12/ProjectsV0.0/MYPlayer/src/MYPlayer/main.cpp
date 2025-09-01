#include <QCoreApplication>
#include <qquickwindow.h>
#include "MainApp.h"


extern MainApp* g_pApp;


int main(int argc, char *argv[])
{
    QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Software); // QT BUG硬件渲染出现了问题, 需要开启软件渲染
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    MainApp app(argc, argv);

    g_pApp = &app;
    int nRet = app.Main(argc, argv);
    g_pApp = nullptr;

    return nRet;
}
