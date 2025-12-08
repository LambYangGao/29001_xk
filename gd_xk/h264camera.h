#ifndef H254CAMERA_H
#define H254CAMERA_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include "libavutil/time.h"
#include <libavfilter/avfilter.h>
#include <libavutil/avutil.h>
#include <libavdevice/avdevice.h>
#include "libavutil/mathematics.h"
}
#include <qobject.h>
#include<stdio.h>
#include <qmutex.h>
#include<qsize.h>
#include<qimage.h>
#include<SDL2/SDL.h>
#include<time.h>
#include<opencv2/opencv.hpp>
#include<queue>
#include"UdpSocket.h"




class QMutex;
template<typename> class QFutureWatcher;
#define SFM_VI_REFRESH_EVENT (SDL_USEREVENT +1)
#define SFM_IR_REFRESH_EVENT (SDL_USEREVENT +2)
#define SFM_PAUSE_EVENT (SDL_USEREVENT +3)

class RTSPCamera
{
public:
    RTSPCamera(void);
};


class RTSPDataDecode : public QObject
{
    Q_OBJECT
public:
    explicit RTSPDataDecode(QString type, QString in_url, QObject* parent = nullptr);
    ~RTSPDataDecode(void);
    AVDictionary* options = NULL;
    void UpdateFrameAndPacket(QString type, AVFormatContext* in_FrameContext, AVPacket* inPacket);
    AVPacket* Copy_Packet(QString type, AVPacket* src);

    cv::Mat m_imgSnap;
public slots:
    int RTSP_Open(void);
    void start(void);
    void stop(void);
    void pause(void);
    void frame_state(bool res);
    void showError(int err);



signals:
    void SigImageChangedVi(cv::Mat& in_mat);
    void SigImageChangedIr(cv::Mat& in_mat);
    void Sig_PacketVi(AVFormatContext* in_FrameContext, AVPacket* inPacket);
    void Sig_PacketIr(AVFormatContext* in_FrameContext, AVPacket* inPacket);
    void SigImageDataVi(quint8* in_imageData);
    void SigImageDataIr(quint8* in_imageData);

private:
    volatile bool isStop;//线程运行标志位

    bool is_Stop = false;
    bool isFirst = false;
    bool is_Decode = false;
    bool is_Pause = false;
    QHostAddress m_ip;
    qint32 m_port;
    QString input_url;
    QString input_type;
    quint8* imageDataByte;
    QMutex* mmutex;
    bool copy_alloc_first = true;

    int m_videoIndex = 0;
    int errorUrlIndex = 0;
    qint64 m_totalFrames = 0;
    QSize  m_size;
    AVFormatContext* mFormatContext = nullptr;
    qreal m_frameRate = 0;                  // 视频帧率

    QString murl;
    bool mstoped;
    QFutureWatcher<void>* mwatcher;
    AVPacket* dst_vi;
    AVPacket* dst_ir;
};

class SDL_Play : public QObject
{
    Q_OBJECT
public:
    explicit SDL_Play(int in_width, int in_height, QString type, void* in_winID, QObject* parent = nullptr);
    ~SDL_Play(void);
public slots:
    void SDL_Windows_Show(SDL_Renderer* in_render, SDL_Texture* in_texture, quint8* in_imageData);
    void SDL_Windows_Init(QString inType);
    void start(void);
    void stop(void);
    //    void ImageDataUpdate(quint8 *in_imageData);
    void SDL_Refersh_Windows(int in_width, int in_height);
    void SDL_Windows_Changed(int in_width, int in_height);

private:

    SDL_Window* m_screen;
    SDL_Renderer* m_render;
    SDL_Texture* m_texture;
    QString inType;
    void* m_winID;
    int m_width;
    int m_height;
    int refersh_width;
    int refersh_height;
    QMutex* mutex;
    quint8* imageData;


    int m_proportion_width;
    int m_proportion_height;
    bool is_Pause = false;
    bool is_Stop = false;
    bool is_Resize = false;
    bool is_Successful_Show = false;



};

class RTSPRecord : public QObject
{
    Q_OBJECT
public:
    explicit RTSPRecord(QString in_type, QString in_url, QObject* parent = nullptr);
    ~RTSPRecord(void);
public slots:
    void Start(QString filename);//recv data
    void Packet_init(AVFormatContext* i_FrameContext, AVFormatContext* o_FrameContext, const char* o_file);
    void Update_VideoStream(AVFormatContext* in_FrameContext, AVPacket* in_pkt);
    void Frame_init(AVFormatContext* in_FrameContext, int videoindex, const char* URL);
    void Out_Put_init(AVFormatContext*& in_FrameContext, int& videoindex, AVFormatContext*& out_FrameContext, const char* out_filename, AVStream*& outVStream);
    void Stop(void);
    void Write_Packet(AVFormatContext* in_FrameContext, AVFormatContext* out_FrameContext, int videoindex, AVStream* outVStream);
private:
    AVFormatContext* i_fmt_ctx = NULL;
    AVStream* i_video_stream = NULL;

    AVFormatContext* o_fmt_ctx = NULL;
    AVStream* o_video_stream = NULL;

    AVPacket* pkt = NULL;
    QString o_filename = "filename";
    QMutex* record_mutex = NULL;

    QString type = "vi";

    int StreamIndex = 0;
    int frameIndex = 0;
    bool isVideoRecord;
    bool isPictureSave;
    bool isFirst = true;

};
#endif // H254CAMERA_H
