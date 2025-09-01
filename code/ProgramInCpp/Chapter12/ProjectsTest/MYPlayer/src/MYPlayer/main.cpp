#include <QCoreApplication>
#include <QQuickWindow>
#include "MainApp.h"

extern MainApp* g_pApp;

int main(int argc, char *argv[])
{
	// 用软件来渲染图像，防止硬件渲染导致程序崩溃
	QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Software);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    MainApp app(argc, argv);
	g_pApp = &app;
    int nRet = app.Main(argc, argv);
	g_pApp = nullptr;

    return nRet;
}
