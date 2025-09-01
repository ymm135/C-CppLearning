#ifndef MYPLAY_H
#define MYPLAY_H

#include <QObject>

class MyPlay : public QObject
{
    Q_OBJECT
    // QML property
    Q_PROPERTY(QString backGround READ backGround WRITE setBackGround NOTIFY backGroundChanged)
	Q_PROPERTY(QString backGroundChoose READ backGroundChoose WRITE setBackGround NOTIFY backGroundChooseChanged)

public:
    explicit MyPlay(QObject *parent = nullptr);

	Q_INVOKABLE void changeBackground(QString url);

    QString backGround()const;
	QString backGroundChoose()const;
    void setBackGround(QString url);

signals:
    void backGroundChanged(QString url);
	void backGroundChooseChanged(QString url);
public slots:


private:
    QString m_strBackgroundPath{""};
    QString m_strBackgroundChoosePath{""};
};

#endif // MYPLAY_H
