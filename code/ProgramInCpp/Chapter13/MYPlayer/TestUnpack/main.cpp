#include <QCoreApplication>
#include <QDebug>
extern "C" {
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}
//#pragma comment(lib,"avformat.lib")
//#pragma comment(lib,"avutil.lib")
//#pragma comment(lib,"avcodec.lib")

static double FractionToDouble(AVRational fraction) //AVRational为分数表示,其目的为避免精度损失，分数表示为分子除以分母，这里将其转换为double
{
    return fraction.den == 0 ? 0 : (double)fraction.num / (double)fraction.den;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const char* path = "test.mp4";         //路径在此设置

    // 初始化封装库
	av_register_all();

	// 初始化解码器
	avcodec_register_all();

	// 音视频索引，读取时可以区别音视频
	int videoStream = 0;
	int audioStream = 1;

	// 打开输入视频文件
	AVFormatContext* avfc = NULL;
	int ret = avformat_open_input(&avfc, path, NULL, NULL);
	if (ret != 0)
	{
		qDebug() << "OPen " << path << "failed!";
		exit(-1);
	}
	// 获取流信息
	ret = avformat_find_stream_info(avfc, NULL);
	if (ret < 0)
	{
		qDebug() << "avformat_find_stream_info failed!";
		exit(-1);
	}
	qDebug() << "number of stream is " << ret;

	// 总时长，秒数
	qDebug() << (avfc->duration / AV_TIME_BASE);
	//avfc->streams
	qDebug() << "streams number is " << avfc->nb_streams;
	for (int i = 0; i < avfc->nb_streams; i++)
	{
		qDebug() << "i is " << i;
		AVStream* as = avfc->streams[i];
		qDebug() << as->codecpar->codec_id;  // AV_CODEC_ID_H264
		qDebug() << as->codecpar->format;     // 
		qDebug(); 

		// 音频 AVMEDIA_TYPE_AUDIO,
		if (as->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audioStream = i;
			qDebug() << i << " audo info";
			qDebug() << "sample_rate = " << as->codecpar->sample_rate;
			qDebug() << "Channels = " << as->codecpar->channels;
		}
		// 视频AVMEDIA_TYPE_VIDEO
		else if (as->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStream = i;
			qDebug() << i << "video info";
			qDebug() << "width = " << as->codecpar->width;
			qDebug() << "height = " << as->codecpar->height;
			// 帧率fps
			//qDebug() << "video fps = " << FractionToDouble(as->avg_frame_rate);
		}
	}

	// 找到视频解码器，创建并打开解码器
	AVCodec*  vcodec = avcodec_find_decoder(avfc->streams[videoStream]->codecpar->codec_id);
	if (!vcodec)
	{
		qDebug() << "video Can't find the video codec ";
	}
	// 上下文
	AVCodecContext* vc = avcodec_alloc_context3(vcodec);
	// 参数
	ret = avcodec_parameters_to_context(vc, avfc->streams[videoStream]->codecpar);
	if (ret < 0)
	{
		qDebug() << "video avcodec_parameters_to_context failed";
	}
	// 8线程同时解码
	vc->thread_count = 8;
	ret = avcodec_open2(vc, NULL, NULL);
	if (ret < 0)
	{
		qDebug() << "video avcodec_open2 failed";
	}

	// 找到音频解码器，创建并打开解码器
	AVCodec*  acodec = avcodec_find_decoder(avfc->streams[audioStream]->codecpar->codec_id);
	if (!acodec)
	{
		qDebug() << "audio Can't find the video codec ";
	}
	// 上下文
	AVCodecContext* ac = avcodec_alloc_context3(acodec);
	// 参数
	ret = avcodec_parameters_to_context(ac, avfc->streams[audioStream]->codecpar);
	if (ret < 0)
	{
		qDebug() << "audio avcodec_parameters_to_context failed";
	}
	// 8线程同时解码
	ac->thread_count = 8;
	ret = avcodec_open2(ac, NULL, NULL);
	if (ret < 0)
	{
		qDebug() << "audio avcodec_open2 failed";
	}

	// Packet, Frame
	AVPacket* pkt = av_packet_alloc();  // using av_packet_free()
	AVFrame* frame = av_frame_alloc(); // using av_frame_free()
	ret = 0;
	while (ret >= 0)
	{
		ret = av_read_frame(avfc, pkt);
		qDebug() << "pkt->size=" << pkt->size;
		qDebug() << "pkt->pts=" << pkt->pts;
		qDebug() << "pkt->dts=" << pkt->dts;
		// 解码
		AVCodecContext* cc = NULL;
		if (pkt->stream_index == videoStream)
		{
			qDebug() << "视频数据";
			cc = vc;
		}
		else if (pkt->stream_index == audioStream)
		{
			qDebug() << "音频数据";
			cc = ac;
		}
		int ret2 = avcodec_send_packet(cc, pkt);//--> frame
		av_packet_unref(pkt); // 引用计数-1
		if (ret2 != 0)
		{
			qDebug() << "Send packet failed";
		}


		// 接受frame
		while (true)
		{
			// 有可能有多处接受decode发过来的frame
			int ret3 = avcodec_receive_frame(cc, frame);
			if (ret3 != 0)
			{
				break;
			}
			qDebug() << "recv frame " << frame->format << " " << frame->linesize[0];
		}
	}
	// 释放资源
	av_frame_free(&frame);
	av_packet_free(&pkt);
	if (avfc)
	{
		avformat_close_input(&avfc);
	}
	avfc = NULL;
	



    return a.exec();
}
