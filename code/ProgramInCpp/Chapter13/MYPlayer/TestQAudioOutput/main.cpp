#include <QtCore/QCoreApplication>
#include <QAudioFormat>
#include <QAudioOutput>
#include <Qthread>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QAudioFormat fmt;
    fmt.setSampleRate(44100);                       //采样率HZ 20HZ-20000HZ
    fmt.setSampleSize(16);                              //采样大小  2^16 = 65535
    fmt.setChannelCount(2);                           //声道数
    fmt.setCodec("audio/pcm");                     //编解码器
    fmt.setByteOrder(QAudioFormat::LittleEndian);  //字节序，小端模式
    fmt.setSampleType(QAudioFormat::UnSignedInt);  //采样类型，无符号int型
    
	// TODO: 生成PCM文件，然后使用二进制读文件的方式，读出流写入播放设备中进行播放声音
	QAudioOutput* out = new QAudioOutput(fmt);
	QIODevice* io = out->start(); // 操作声音设备
	int size = out->periodSize();//一个播放周期的大小
	//out->bytesFree
	char* tmp = new char[size];  // 文件缓冲区
	
	string src = "out.pcm";
	ifstream in(src.c_str(), ios::in | ios::binary);
	if (!in) // 开发是否成功
	{
		return -1;
	}
	//QIODevice
	//ifstream
	while (!in.eof())
	{
		if (out->bytesFree() < size)
		{
			// 等待继续读取数据，然后进行播放
			continue;
		}
		in.read(tmp, size);
		streamsize count = in.gcount();
		if (count <= 0)
		{
			break;
		}
		io->write(tmp, count);  // 向声音设备中写入数据
	}
	// 关闭文件，释放缓冲区
	in.close();
	delete[] tmp;
	tmp = NULL;


    return a.exec();
}
