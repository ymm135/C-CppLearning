#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QDebug>
#include <QThread>


class SPA
{
public:
	SPA()
	{
		qDebug() << "SPA::SPA()" << endl;
	}
	~SPA()
	{
		qDebug() << "SPA::~SPA()" << endl;
	}
	void Print()
	{
		qDebug() << "SPA::Print()" << endl;
	}
};

class MyThread :public QThread
{
public:
	MyThread() 
	{
		isStop = false;
	}
	void CloseThread()
	{
		isStop = true;
	}
	void run()
	{
		while (true)
		{
			if (isStop) { return; }
			qDebug() << tr("MyThread id is: ") << QThread::currentThreadId();
			sleep(1);
		}
	}
private:
	bool isStop;
};


int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //QGuiApplication app(argc, argv);

    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    //if (engine.rootObjects().isEmpty())
    //    return -1;

    //return app.exec();

	//// QString的基本使用
	//QString str = "C:/";
	//QString str2 = "D:\\";
	//qDebug() << str << endl;
	//qDebug() << str2 << endl;
	//str += "muying/";
	//str2.append("muying/"); // D:\\muying/
	//qDebug() << str << endl;
	//qDebug() << str2 << endl;
	//str.clear();
	//int pos = str2.indexOf("\\");
	////pos = str2.indexOf("X");
	//str2 = str2.mid(pos+1, QStringLiteral("muying").length());
	//qDebug() << str << endl;
	//qDebug() << str2 << endl;

	//// QString字符串的转换
	//// 数字-》字符串
	//str = QString::number(3.14);
	//str.setNum(34);
	//// 字符串-》数字
	//QString str3 = "123";
	//int i = str3.toInt();
	//qDebug("The value of str is: %s", qPrintable(str3) );
	//qDebug("The value of i is: %d", i);
	//str3 = "abc";
	//i = str3.toInt();
	//qDebug("The value of str is: %s", qPrintable(str3) );
	//qDebug("The value of i is: %d", i);

	//// QScopedPointer
	//{
	//	QScopedPointer<int> i2(new int(3) );
	//	qDebug("The value of i2 is: %d", *i2);
	//	i2.reset(new int(4) );
	//	qDebug("The value of i2 is: %d", *i2);

	//	QScopedPointer<SPA> spA(new SPA);
	//	spA->Print();
	//	QScopedArrayPointer<SPA> spArr(new SPA[10]);
	//}

	// 实现多线程
	MyThread thread;
	thread.start();
	while (true)
	{
		;
	}
	thread.CloseThread();

	return 0;
}
