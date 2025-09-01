#include "MyPlay.h"
#include <QSettings>


MyPlay::MyPlay(QObject *parent) : QObject(parent)
{
	setBackGround(NULL);
}

void MyPlay::changeBackground(QString url)
{
	setBackGround(url);
}

QString MyPlay::backGround()const
{
    return m_strBackgroundPath;
}

QString MyPlay::backGroundChoose()const
{
	return m_strBackgroundChoosePath;
}

void MyPlay::setBackGround(QString url)
{
	QSettings* settingini = new QSettings("setting.ini", QSettings::IniFormat);
	QString backGroundpath = settingini->value("Path/Background").toString();
	if (url == NULL)
	{
		if (backGroundpath == NULL)
		{
			delete settingini;
			return;
		}
		else
		{
			m_strBackgroundPath = backGroundpath;
			m_strBackgroundChoosePath = backGroundpath;
			delete settingini;
			emit backGroundChanged(m_strBackgroundPath);
			emit backGroundChanged(m_strBackgroundChoosePath);
		}
	}
	else
	{
		if (url != m_strBackgroundPath)
		{
			settingini->setValue("Path/Background", url);
			m_strBackgroundPath = url;
			m_strBackgroundChoosePath = url;
			emit backGroundChanged(m_strBackgroundPath);
			emit backGroundChanged(m_strBackgroundChoosePath);
		}
	}
}
