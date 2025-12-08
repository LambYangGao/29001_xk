#include "h264camera.h"
#include <QList>
#include <QTime>
struct message_queue* g_msg_queue;
int g_ParamBuf[8] = { 0 };
bool isDataStart = false;

quint8* imageDataByteVi = NULL;
quint8* imageDataByteIr = NULL;
quint8* buffer_vi = NULL;
quint8* buffer_ir = NULL;
bool isTrueRecordStart = false;


AVFormatContext* in_Record_FrameContext_Vi = NULL;
AVPacket* in_Record_Packet_Vi = NULL;
AVFormatContext* in_Record_FrameContext_Ir = NULL;
AVPacket* in_Record_Packet_Ir = NULL;

bool is_Show = false;

RTSPDataDecode::RTSPDataDecode(QString type, QString in_url, QObject* parent)
	: QObject(parent)

{
	is_Stop = false;
	is_Decode = false;
	input_url = in_url;
	input_type = type;
	mmutex = new QMutex();
	if (input_type == "vi")
	{
		imageDataByteVi = (quint8*)malloc(1920 * 1080 * 3 * sizeof(quint8));
		imageDataByte = imageDataByteVi;
	}
	else if (input_type == "ir")
	{
		imageDataByteIr = (quint8*)malloc(1920 * 1080 * 3 * sizeof(quint8));
		imageDataByte = imageDataByteIr;
	}
}
RTSPDataDecode::~RTSPDataDecode(void)
{
	avformat_close_input(&mFormatContext);
	mstoped = true;
	is_Stop = true;
	delete mmutex;
}



void RTSPDataDecode::start(void)
{
	avformat_network_init();
	is_Stop = false;
	while (is_Stop == false)
	{
		int ret = RTSP_Open();
		if (ret == false)
		{
			av_usleep(400000);
		}
		else
		{
			//
		}
	}
}



void RTSPDataDecode::stop(void)
{
	QMutexLocker locker(mmutex);
	mstoped = true;
	is_Stop = true;

}
void RTSPDataDecode::pause(void)
{
	is_Pause = true;
}
void RTSPDataDecode::frame_state(bool res)
{
	if (res == true)
	{
		is_Decode = false;
	}
	else
	{
		is_Decode = true;
	}
}



void RTSPDataDecode::showError(int err)
{
#if PRINT_LOG
	memset(m_error, 0, ERROR_LEN);        // 将数组置零
	av_strerror(err, m_error, ERROR_LEN);
	qWarning() << "DecodeVideo Error：" << m_error;
#else
	Q_UNUSED(err)
#endif
}

QList<AVPacket*> g_packet_list_vi;
QList<AVPacket*> g_packet_list_ir;
int RTSPDataDecode::RTSP_Open(void)
{

	mFormatContext = avformat_alloc_context();
	av_dict_set(&options, "buffer_size", "1024*1000", 0);
	av_dict_set(&options, "stimeout", "2000000", 0);
	av_dict_set(&options, "max_delay", "300000", 0);
	av_dict_set(&options, "rtsp_transport", "tcp", 0);
	//输入url
	int ret = avformat_open_input(&mFormatContext, input_url.toUtf8(), nullptr, &options);
	if (ret < 0)
	{
		return false;
	}
	else
	{
		//
	}
	//找到流信息
	ret = avformat_find_stream_info(mFormatContext, nullptr);
	//找到流的m_videoIndex
	m_videoIndex = av_find_best_stream(mFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
	if (m_videoIndex < 0)
	{
		showError(m_videoIndex);
		return false;
	}
	else
	{
		//
	}

	AVStream* srcStream = mFormatContext->streams[m_videoIndex];
	//找到解码器
	const AVCodec* srcCodec = avcodec_find_decoder(srcStream->codecpar->codec_id);
	//分配解码器上下文
	AVCodecContext* srcCodecContext = avcodec_alloc_context3(srcCodec);
	//将流信息填入解码器上下文
	ret = avcodec_parameters_to_context(srcCodecContext, srcStream->codecpar);
	if (ret < 0)
	{
		showError(ret);
		return false;
	}
	//检查输入编码器是否符合标准
	ret = avcodec_open2(srcCodecContext, srcCodec, nullptr);
	if (ret < 0)
	{
		showError(ret);
		return false;
	}
	//打印信息
	av_dump_format(mFormatContext, 0, mFormatContext->url, 0);
	AVPixelFormat desFormat = AV_PIX_FMT_YUV420P;
	SwsContext* swscontext = sws_getContext(srcCodecContext->width, srcCodecContext->height, srcCodecContext->pix_fmt,
		srcCodecContext->width, srcCodecContext->height, desFormat,
		SWS_BICUBIC, nullptr, nullptr, nullptr);
	AVFrame* srcFrame = av_frame_alloc();
	AVFrame* desFrame = av_frame_alloc();
	//将解码信息传入流中
	desFrame->width = srcCodecContext->width;
	desFrame->height = srcCodecContext->height;
	desFrame->format = desFormat;
	desFrame->linesize[0] = desFrame->width;
	desFrame->linesize[1] = desFrame->width;
	desFrame->linesize[2] = desFrame->width;
	int bufferSize = av_image_get_buffer_size(desFormat, srcCodecContext->width, srcCodecContext->height, 1);
	uint8_t* buffer = (uint8_t*)av_malloc(bufferSize);
	//根据图像宽高申请指定大小的buffer内存
	av_image_fill_arrays(desFrame->data, desFrame->linesize, imageDataByte,
		desFormat, desFrame->width, desFrame->height, 1);
	is_Decode = true;
	cv::Mat hw_frame_mat;
	errorUrlIndex = 0;
	int testPrintPicUseTimeNum = 10;
	while (is_Decode == true)
	{
		auto start = std::chrono::steady_clock::now();

		{
			QMutexLocker locker(mmutex);
			if (is_Stop == true)
			{
				break;
			}
			if (is_Pause == true)
			{
				continue;
			}
		}

		// 从解码器取出一帧AVFrame数据
		AVPacket* srcPkt = av_packet_alloc();
		ret = av_read_frame(mFormatContext, srcPkt);
		if (ret < 0)
		{
			av_packet_unref(srcPkt);
			av_packet_free(&srcPkt);
			showError(ret);
			break;
		}
		if (testPrintPicUseTimeNum > 0)
		{
			QTime currecttime = QTime::currentTime();
			if (input_type == "vi")
			{
				QString str = QStringLiteral("%1:%2").arg(currecttime.toString("hh:mm:ss.zzz")).arg("接收图像数据");
				qDebug() << str;
			}
		}
		if (srcPkt->stream_index != m_videoIndex)
		{
			av_packet_unref(srcPkt);
			av_packet_free(&srcPkt);
			continue;
		}
		//把AVpacket数据包发送给解码器
		ret = avcodec_send_packet(srcCodecContext, srcPkt);
		if (ret < 0)
		{
			av_packet_unref(srcPkt);
			av_packet_free(&srcPkt);
			showError(ret);
			continue;
		}
		//获得解码后的AVFrame
		ret = avcodec_receive_frame(srcCodecContext, srcFrame);
		if (ret < 0)
		{
			av_packet_unref(srcPkt);
			av_packet_free(&srcPkt);
			showError(ret);
			continue;
		}

		srcFrame->format = AV_PIX_FMT_YUV420P;
		sws_scale(swscontext, (const unsigned char* const*)srcFrame->data, srcFrame->linesize, 0, srcFrame->height, desFrame->data, desFrame->linesize);

		{
			QMutexLocker locker(mmutex);
			if (input_type == "vi")
			{
				g_packet_list_vi.push_back(srcPkt);
				emit SigImageDataVi(imageDataByte);
				/*emit Sig_PacketVi(mFormatContext, srcPkt);*/

				UpdateFrameAndPacket(input_type, mFormatContext, srcPkt);

				cv::Mat yuvmat(srcFrame->height + srcFrame->height / 2, srcFrame->width, CV_8UC1, imageDataByte);
				cvtColor(yuvmat, hw_frame_mat, cv::COLOR_YUV420p2RGB);
				hw_frame_mat.copyTo(m_imgSnap);//供算法拉取图像
				QImage imageVi = QImage(imageDataByte, srcFrame->width, srcFrame->height, QImage::Format_ARGB32);
				emit SigImageChangedVi(hw_frame_mat);

				if (isTrueRecordStart == false)
				{
					if (g_packet_list_vi.size() > 0)
					{
						av_packet_unref(g_packet_list_vi.front());
						av_packet_free(&g_packet_list_vi.front());
						g_packet_list_vi.pop_front();
					}
				}
				else
				{
					if (g_packet_list_vi.size() > 200)
					{
						av_packet_unref(g_packet_list_vi.front());
						av_packet_free(&g_packet_list_vi.front());
						g_packet_list_vi.pop_front();
					}
				}

				if (testPrintPicUseTimeNum > 0)
				{
					testPrintPicUseTimeNum--;
					QTime currecttime = QTime::currentTime();
					QString str = QStringLiteral("%1:%2\r\n").arg(currecttime.toString("hh:mm:ss.zzz")).arg("播放一帧图像");
					qDebug() << str;
				}
			}
			else if (input_type == "ir")
			{

				g_packet_list_ir.push_back(srcPkt);
				emit SigImageDataIr(imageDataByte);

				UpdateFrameAndPacket(input_type, mFormatContext, srcPkt);

				cv::Mat yuvmat(srcFrame->height + srcFrame->height / 2, srcFrame->width, CV_8UC1, imageDataByte);
				cvtColor(yuvmat, hw_frame_mat, cv::COLOR_YUV420p2RGB);
				hw_frame_mat.copyTo(m_imgSnap);//供算法拉取图像

				QImage imageIr(buffer, srcFrame->width, desFrame->height, QImage::Format_RGB888);
				emit SigImageChangedIr(hw_frame_mat);
				//av_packet_unref(srcPkt);
				if (isTrueRecordStart == false)
				{
					if (g_packet_list_ir.size() > 0)
					{
						av_packet_unref(g_packet_list_ir.front());
						av_packet_free(&g_packet_list_ir.front());
						g_packet_list_ir.pop_front();
					}
					//                    qDebug()<<g_packet_list_ir.size()<<endl;

				}
				else
				{
					if (g_packet_list_ir.size() > 200)
					{
						av_packet_unref(g_packet_list_ir.front());
						av_packet_free(&g_packet_list_ir.front());
						g_packet_list_ir.pop_front();
					}
				}
			}

		}
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		while (duration.count() < 0.01)
		{
			av_usleep(1);
			end = std::chrono::steady_clock::now();
			duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		}
	}
	av_free(buffer);
	//av_packet_free(&srcPkt);
	av_frame_free(&srcFrame);
	av_frame_free(&desFrame);
	avcodec_close(srcCodecContext);
	avformat_close_input(&mFormatContext);

}



void RTSPDataDecode::UpdateFrameAndPacket(QString type, AVFormatContext* in_FrameContext, AVPacket* inPacket)
{
	if (type == "vi")
	{
		if (in_Record_FrameContext_Vi != in_FrameContext)
		{
			in_Record_FrameContext_Vi = in_FrameContext;

		}
		//        in_Record_Packet_Vi = Copy_Packet(type, inPacket);
	}
	else if (type == "ir")
	{
		if (in_Record_FrameContext_Ir != in_FrameContext)
		{
			in_Record_FrameContext_Ir = in_FrameContext;
		}
		//        in_Record_Packet_Ir = Copy_Packet(type, inPacket);
	}
}

AVPacket* RTSPDataDecode::Copy_Packet(QString type, AVPacket* src)
{

	AVPacket* dst = NULL;
	static AVPacket* dst_vi = NULL;
	static AVPacket* dst_ir = NULL;
	static bool first_vi = true;
	static bool first_ir = true;



	if (type == "vi" && first_vi)
	{
		dst_vi = av_packet_alloc();
		memcpy(dst_vi, src, sizeof(AVPacket));
		//av_packet_ref(dst_vi, src);
		first_vi = false;
		dst_vi->data = (uint8_t*)av_malloc(src->size);
	}
	else if (type == "ir" && first_ir)
	{
		dst_ir = av_packet_alloc();
		memcpy(dst_ir, src, sizeof(AVPacket));
		first_ir = false;
		dst_ir->data = (uint8_t*)av_malloc(src->size);
	}


	if (type == "vi")
	{
		dst = dst_vi;
	}
	else if (type == "ir")
	{
		dst = dst_ir;
	}

	// 分配内存
	if (!dst) {
		return NULL;
	}

	// 复制所有字段
	//av_packet_ref(dst, src);

	if (src->buf == NULL)
	{
		return NULL;
	}
	// 复制音视频数据
//    dst->data = (uint8_t*)av_malloc(src->size);
	memcpy(dst->data, src->data, src->size);
	return dst;
}

SDL_Play::SDL_Play(int in_width, int in_height, QString type, void* in_winID, QObject* parent)
	: QObject(parent)

{
	m_winID = in_winID;
	m_width = in_width;
	m_height = in_height;
	mutex = new QMutex();
	inType = type;
	if (inType == "vi")
	{
		imageData = imageDataByteVi;
		m_proportion_width = 1920;
		m_proportion_height = 1080;
	}
	else
	{
		imageData = imageDataByteIr;
		m_proportion_width = 640;
		m_proportion_height = 512;
	}
}
SDL_Play::~SDL_Play(void)
{
	SDL_DestroyRenderer(m_render);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_screen);
	atexit(SDL_Quit);


}

void SDL_Play::SDL_Windows_Init(QString in_Type)
{
	if (in_Type == "vi")
	{
		SDL_Window* viScreen = SDL_CreateWindowFrom(m_winID);
		SDL_ShowWindow(viScreen);
		SDL_SetWindowSize(viScreen, m_width, m_height);
		SDL_Renderer* viRender = SDL_CreateRenderer(viScreen, -1, SDL_RENDERER_ACCELERATED);
		SDL_Texture* viTexture = SDL_CreateTexture(viRender, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, m_proportion_width, m_proportion_height);
		m_screen = viScreen;
		m_render = viRender;
		m_texture = viTexture;
	}
	else if (in_Type == "ir")
	{
		SDL_Window* irScreen = SDL_CreateWindowFrom(m_winID);
		SDL_ShowWindow(irScreen);
		SDL_SetWindowSize(irScreen, m_width, m_height);
		SDL_Renderer* irRender = SDL_CreateRenderer(irScreen, -1, SDL_RENDERER_ACCELERATED);
		SDL_Texture* irTexture = SDL_CreateTexture(irRender, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, m_proportion_width, m_proportion_height);
		m_screen = irScreen;
		m_render = irRender;
		m_texture = irTexture;
	}
	is_Show = true;
	is_Pause = false;

}

void SDL_Play::SDL_Windows_Changed(int in_width, int in_height)
{

	is_Pause = true;
	refersh_width = in_width;
	refersh_height = in_height;
	SDL_SetWindowSize(m_screen, in_width, in_height);
	//    SDL_Refersh_Windows(refersh_width,refersh_height);
}
void SDL_Play::SDL_Refersh_Windows(int in_width, int in_height)
{
	mutex->lock();
	SDL_DestroyRenderer(m_render);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_screen);
	//这里按照实际窗口分辨率设置
	SDL_SetWindowSize(m_screen, in_width, in_height);
	m_screen = SDL_CreateWindowFrom(m_winID);
	SDL_ShowWindow(m_screen);

	int count = 0;
	//创建渲染器
	m_render = SDL_CreateRenderer(m_screen, -1, SDL_RENDERER_ACCELERATED);
	//创建纹理
	m_texture = SDL_CreateTexture(m_render, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, m_proportion_width, m_proportion_height);
	is_Pause = false;
	mutex->unlock();
}

void SDL_Play::SDL_Windows_Show(SDL_Renderer* in_render, SDL_Texture* in_texture, quint8* in_imageData)
{
	mutex->lock();
	SDL_UpdateTexture(in_texture, nullptr, in_imageData, m_proportion_width);
	SDL_RenderClear(m_render);
	SDL_RenderCopy(in_render, in_texture, nullptr, nullptr);
	SDL_RenderPresent(in_render);
	mutex->unlock();
}

void SDL_Play::stop(void)
{
	is_Stop = true;
}
void SDL_Play::start(void)
{
	SDL_Windows_Init(inType);
	is_Stop = false;
	while (is_Stop == false) {
		auto start = std::chrono::steady_clock::now();
		SDL_RenderClear(m_render); // 清除渲染流A
		SDL_Windows_Show(m_render, m_texture, imageData);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		while (duration.count() < 0.015)
		{
			av_usleep(1);
			end = std::chrono::steady_clock::now();
			duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		}
	}
}


RTSPRecord::RTSPRecord(QString in_type, QString in_url, QObject* parent)
	: QObject(parent)
{
	type = in_type;
	record_mutex = new QMutex();
	//    Frame_init(i_fmt_ctx,StreamIndex,in_url.toStdString().data());
}
void RTSPRecord::Start(QString filename)
{
	isVideoRecord = true;
	isTrueRecordStart = true;
	if (type == "vi")
	{
		i_fmt_ctx = in_Record_FrameContext_Vi;
		//pkt = in_Record_Packet_Vi;
//        pkt = g_packet_list_vi.front();
//        g_packet_list_vi.pop_front();
	}
	else if (type == "ir")
	{
		i_fmt_ctx = in_Record_FrameContext_Ir;
		//pkt = in_Record_Packet_Ir;
//        pkt = g_packet_list_ir.front();
//        g_packet_list_ir.pop_front();
	}

	o_filename = filename;
	isVideoRecord = true;
	o_fmt_ctx = avformat_alloc_context();
	if (i_fmt_ctx != nullptr) {
		StreamIndex = av_find_best_stream(i_fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
		Out_Put_init(i_fmt_ctx, StreamIndex, o_fmt_ctx, o_filename.toStdString().data(), o_video_stream);
		Write_Packet(i_fmt_ctx, o_fmt_ctx, StreamIndex, o_video_stream);
	}
	avformat_close_input(&o_fmt_ctx);
	//    avformat_close_input(&i_fmt_ctx);



}
RTSPRecord::~RTSPRecord(void)
{
	delete record_mutex;
}
void RTSPRecord::Stop(void)
{
	isVideoRecord = false;
	isTrueRecordStart = false;

}
void RTSPRecord::Write_Packet(AVFormatContext* in_FrameContext,
	AVFormatContext* out_FrameContext, int videoindex
	, AVStream* outVStream)
{
	int ret = avformat_write_header(out_FrameContext, NULL);
	if (ret < 0) {
		printf("Cannot write header to file.\n");
		return;
	}
	else
	{
		//
	}
	//===============编码部分===============//
	int frame_index = 0;
	AVStream* inVStream = in_FrameContext->streams[videoindex];
	while (isVideoRecord == true) {//循环读取每一帧直到读完
		if (type == "vi")
		{
			//pkt = in_Record_Packet_Vi;
			if (g_packet_list_vi.size() > 0)
			{
				pkt = g_packet_list_vi.front();
				g_packet_list_vi.pop_front();
			}
			else {
				av_usleep(1000);
				continue;
			}
		}
		else if (type == "ir")
		{

			//pkt = in_Record_Packet_Ir;
			if (g_packet_list_ir.size() > 0)
			{
				pkt = g_packet_list_ir.front();
				g_packet_list_ir.pop_front();
			}
			else
			{
				av_usleep(1000);
				continue;
			}

		}
		//        QMutexLocker locker(record_mutex);
	
		else
		{
			//
		}
		if (pkt->size > 0)
		{
			if (pkt->stream_index == videoindex) {//确保处理的是视频流

				if (pkt->pts == AV_NOPTS_VALUE) {
					frame_index++;
					printf("errorframe_index:%d\n", frame_index);
					//Write PTS
					AVRational time_base1 = inVStream->time_base;
					//Duration between 2 frames (us)
					int64_t calc_duration = (double)AV_TIME_BASE / av_q2d(inVStream->r_frame_rate);
					//Parameters
					pkt->pts = (double)(frame_index * calc_duration) / (double)(av_q2d(time_base1) * AV_TIME_BASE);
					pkt->dts = pkt->pts;
					pkt->duration = (double)calc_duration / (double)(av_q2d(time_base1) * AV_TIME_BASE);
				}
				else
				{
					//Convert PTS/DTS
					pkt->pts = pkt->dts = frame_index * (out_FrameContext->streams[0]->time_base.den) / out_FrameContext->streams[0]->time_base.num / 25;
					frame_index++;
				}
				// Write
				
				if (av_interleaved_write_frame(out_FrameContext, pkt) < 0) {
					printf("Error muxing packet\n");
					av_packet_unref(pkt);
					av_packet_free(&pkt);
					continue;
				}
				av_packet_unref(pkt);
				av_packet_free(&pkt);
			}
			else
			{
				av_packet_unref(pkt);
				av_packet_free(&pkt);
			}
		}
	}

	av_write_trailer(out_FrameContext);

}

void RTSPRecord::Out_Put_init(AVFormatContext*& in_FrameContext, int& videoindex,
	AVFormatContext*& out_FrameContext,
	const char* out_filename, AVStream*& outVStream)
{
	frameIndex = 0;
	int ret;

	// 初始化一个用于输出的AVFormatContext结构体
	ret = avformat_alloc_output_context2(&out_FrameContext, NULL, NULL, out_filename);
	ret = avio_open(&out_FrameContext->pb, out_filename, AVIO_FLAG_READ_WRITE);
	if (ret < 0) {
		printf("output file open failed.\n");
		return;
	}
	AVCodecParameters* incodecPara = in_FrameContext->streams[videoindex]->codecpar;//输入视频流的编码参数

	//在输出的mp4文件中创建一条视频流
	outVStream = avformat_new_stream(out_FrameContext, NULL);
	outVStream->time_base.den = 25;
	outVStream->time_base.num = 1;

	if (!outVStream) {
		printf("Failed allocating output stream.\n");
		return;
	}
	AVCodec* outCodec = avcodec_find_encoder(incodecPara->codec_id);
	if (outCodec == NULL) {
		printf("Cannot find any encoder.\n");
		return;
	}


	//从输入的RTSP编码器数据复制一份到输出文件的编码器中
	AVCodecContext* outCodecCtx = avcodec_alloc_context3(outCodec);
	AVCodecParameters* outCodecPara = out_FrameContext->streams[outVStream->index]->codecpar;
	ret = avcodec_parameters_copy(outCodecPara, incodecPara);
	if (ret < 0) {
		printf("Cannot copy codec para.\n");
		return;
	}
	ret = avcodec_parameters_to_context(outCodecCtx, outCodecPara);
	if (ret < 0) {
		printf("Cannot alloc codec ctx from para.\n");
		return;
	}
	outCodecCtx->time_base.den = 25;
	outCodecCtx->time_base.num = 1;
	ret = avcodec_open2(outCodecCtx, outCodec, NULL);
	if (ret < 0) {
		printf("Cannot open output codec.\n,ret=%d", ret);
		return;
	}

	printf("============Output Information=============>\n");
	av_dump_format(out_FrameContext, 0, out_filename, 1);
	printf("============Output Information=============<\n");
}

void RTSPRecord::Frame_init(AVFormatContext* in_FrameContext, int videoindex, const char* URL)
{

	//Network
	avformat_network_init();
	int ret;
	ret = avformat_open_input(&in_FrameContext, URL, 0, 0);
	//Input
	if (ret < 0) {
		printf("Could not open input file.");
		return;
	}
	ret = avformat_find_stream_info(in_FrameContext, 0);
	if (ret < 0) {
		printf("Failed to retrieve input stream information");
		return;
	}

	videoindex = av_find_best_stream(in_FrameContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);

	av_dump_format(in_FrameContext, 0, URL, 0);
}


void RTSPRecord::Update_VideoStream(AVFormatContext* in_FrameContext, AVPacket* in_pkt)
{
	/*if (i_fmt_ctx != in_FrameContext)
	{
		i_fmt_ctx = in_FrameContext;
	}
	pkt = Copy_Packet(type, in_pkt);*/


}


void RTSPRecord::Packet_init(AVFormatContext* i_FrameContext, AVFormatContext* o_FrameContext,
	const char* o_file)
{
	int ret;
	AVFrame* o_video_stream = av_frame_alloc();
	// 初始化一个用于输出的AVFormatContext结构体
	ret = avformat_alloc_output_context2(&o_FrameContext, NULL, NULL, o_file);
	if (ret < 0)
	{
		qDebug() << "cant alloc Frame Context";
		return;
	}
	avio_open(&o_FrameContext->pb, o_file, AVIO_FLAG_WRITE);

	int m_videoIndex = av_find_best_stream(i_FrameContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
	AVCodecParameters* incodecPara = i_FrameContext->streams[m_videoIndex]->codecpar;//输入视频流的编码参数

	AVStream* outVStream = avformat_new_stream(o_FrameContext, NULL);

	if (!o_video_stream)
	{
		qDebug() << "Failed allocating output stream.\n";
		return;
	}
	//查找编码器
	AVCodec* outCodec = avcodec_find_encoder(incodecPara->codec_id);
	if (outCodec == NULL) {
		printf("Cannot find any encoder.\n");
		return;
	}
	AVCodecContext* outCodecCtx = avcodec_alloc_context3(outCodec);
	AVCodecParameters* outCodecPara = o_FrameContext->streams[outVStream->index]->codecpar;
	ret = avcodec_parameters_copy(outCodecPara, incodecPara);
	if (ret < 0)
	{
		printf("Cannot copy codec para.\n");
		return;
	}
	ret = avcodec_parameters_to_context(outCodecCtx, outCodecPara);
	if (ret < 0)
	{
		printf("Cannot alloc codec ctx from para.\n");
		return;
	}
	ret = avcodec_open2(outCodecCtx, outCodec, NULL);
	if (ret < 0)
	{
		printf("Cannot open output codec.\n");
		return;
	}
	printf("============Output Information=============>\n");
	av_dump_format(o_FrameContext, 0, o_file, 1);
	printf("============Output Information=============<\n");
	if (avformat_write_header(o_FrameContext, NULL) < 0)
	{
		printf("Cannot write header to file.\n");
		return;
	}
	while (isVideoRecord)
	{
		if (av_interleaved_write_frame(o_FrameContext, pkt) < 0)
		{
			printf("Error muxing packet\n");
			continue;
		}
		av_packet_unref(pkt);
	}
	av_write_trailer(o_FrameContext);
}
