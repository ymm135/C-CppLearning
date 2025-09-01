#include <QDir>
#include <QFont>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <QStandardPaths>
#include <QDebug>
#include "MainApp.h"

#define APP_NAME                                "MYPlayer"
#define APP_DISPLAYNAME                         "MYPlayer"
#define APP_ICON_PATH                           ":/image/AppIcon.ico"
#define UI_MAIN_PATH                            "qrc:/qml/main.qml"
#define UI_TRANSLATION_PATH                     ":/translation/MYPlayer_zh_CN.qm"
#define IMAGEDIR_RELATIVE_PATH                  "./resource/ui/image"
#define DEFAULT_FONT_NAME                       "微软雅黑"


MainApp* g_pApp = nullptr;

MainApp* GetMainApp()
{
    return g_pApp;
}

QObject* MainApp::GetInstance(QQmlEngine* /*engine*/, QJSEngine* /*scriptEngine*/)
{
    QObject* pObj = GetMainApp();
    QQmlEngine::setObjectOwnership(pObj, QQmlEngine::CppOwnership);
    return pObj;
}

MainApp::MainApp(int &argc, char **argv)
       : QApplication(argc, argv)
       , m_strAppRootPath()
       , m_strImageRootPath()
{
}

MainApp::~MainApp() = default;

int MainApp::Main(int /*argc*/, char* /*argv*/[])
{
    if (!Initialize())
    {
        Uninitialize();
        return EXIT_FAILURE;
    }

    int nRet = exec();

    Uninitialize();

    return nRet;
}

void MainApp::testFunc()
{
    qDebug()<<"MainApp::testFunc()";
	setDemoNum(demoNum() + 1);
}

int MainApp::demoNum() const
{
	return m_DemoNum;
}
void MainApp::setDemoNum(int newValue)
{
	if (m_DemoNum != newValue)
	{
		m_DemoNum = newValue;
		emit demoNumChanged(m_DemoNum);
	}
}

bool MainApp::Initialize()
{
    // 设置应用程序属性
    setApplicationName(QStringLiteral(APP_NAME));
    setWindowIcon(QIcon(QStringLiteral(APP_ICON_PATH)));
    setApplicationDisplayName(tr(APP_DISPLAYNAME));

    // Initialize Path
    InitializePath();

    // Initialize config
    InitializeCfg();

    // Initialize translator
    if (!InitializeTranslator())
        {return false;}

    // Initialize QML engine
    if (!InitializeQmlEngine())
        {return false;}

    // Initialize UI
    if (!InitializeUI(m_pQmlEngine.data()))
        {return false;}

    InitializeOthers();

    return true;
}

bool MainApp::Uninitialize()
{
    UninitializeOthers();

    // Uninitialize UI
    UninitializeUI(m_pQmlEngine.data());

    // Uninitialize Qml Engine
    UninitializeQmlEngine();

    //Uninitialize translator
    UninitializeTranslator();

    // Uninitialize config
    UninitializeCfg();

    // Uninitialize Path
    UninitializePath();

    return true;
}

bool MainApp::InitializePath()
{
    // Application directory path
    m_strAppRootPath = qApp->applicationDirPath();
    QDir dirApp(m_strAppRootPath);
    if (!dirApp.exists())
        {return false;}

    // Image root directory path
    m_strImageRootPath = m_strAppRootPath;
    m_strImageRootPath.append(QStringLiteral("/")).append(QStringLiteral(IMAGEDIR_RELATIVE_PATH));
    QDir dirImg(m_strImageRootPath);
    if (!dirImg.exists())
    {
    }
    m_strImageRootPath = dirImg.canonicalPath();

    return true;
}

bool MainApp::UninitializePath()
{
    // Image root directory path
    m_strImageRootPath.clear();

    // Application directory path
    m_strAppRootPath.clear();

    return true;
}

bool MainApp::InitializeCfg()
{
    return true;
}

bool MainApp::UninitializeCfg()
{
    return true;
}

bool MainApp::InitializeTranslator()
{
    if (m_pTranslator != nullptr)
        {return true;}

    // Load translation from resource
    m_pTranslator.reset(new QTranslator);
    if (!m_pTranslator->load(QStringLiteral(UI_TRANSLATION_PATH)))
        {return false;}

    // Add translator
    installTranslator(m_pTranslator.data());

    return true;
}

bool MainApp::UninitializeTranslator()
{
    if (!m_pTranslator)
        {return true;}

    // Remove translator
    removeTranslator(m_pTranslator.data());

    // Free translator instance
    m_pTranslator.reset();

    return true;
}

bool MainApp::InitializeQmlEngine()
{
    if (m_pQmlEngine != nullptr)
        {return true;}

    // Create QML engine instance
    m_pQmlEngine.reset(new QQmlApplicationEngine);

    return (nullptr != m_pQmlEngine);
}

bool MainApp::UninitializeQmlEngine()
{
    if (!m_pQmlEngine)
        {return true;}

    // Free QML engine instance
    m_pQmlEngine.reset();

    return true;
}

bool MainApp::InitializeUI(QQmlApplicationEngine* pQmlEngine)
{
    if (pQmlEngine == nullptr)
        {return false;}

    // 设置程序默认字体
    setFont(QFont(DEFAULT_FONT_NAME, 9));

    // Register Qml Types
    qmlRegisterSingletonType<MainApp>("com.imooc.myplayer", 1, 0, "MainApp",
                                      &MainApp::GetInstance);

    // Load main UI qml from resource
    pQmlEngine->load(QUrl(QStringLiteral(UI_MAIN_PATH)));
    QList<QObject*> rootObjs(pQmlEngine->rootObjects());
    return !rootObjs.isEmpty();
}

bool MainApp::UninitializeUI(QQmlApplicationEngine* pQmlEngine)
{
    if (pQmlEngine == nullptr)
        {return true;}

    return true;
}

bool MainApp::InitializeOthers()
{
    return true;
}

bool MainApp::UninitializeOthers()
{
    return true;
}
