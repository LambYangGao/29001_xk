#ifndef QIMAGEVIEW_H
#define QIMAGEVIEW_H
#include <QLabel>
#include <opencv2\opencv.hpp>
#include <QSlider>
#include <QMenu>
#include <QMouseEvent>
#include <QTimer>
#include <QPen>
#include <QBoxLayout>
#include <QTime>
#include <mutex>
#include <vector>
#include <QPainter>
#include "ImageProcessor.h"

class CImageStream;
class wrt_xk;

using namespace std;

class QImageView : public QLabel
{
	Q_OBJECT

public:
	QImageView(QWidget* parent, CImageStream* pStream = nullptr);
	~QImageView(void);
	//设置展示图象
	void SetDisplayImage(cv::Mat& mat);
	void SetTarget(double x, double y);
	//设置展示设备
	void setDisplayDevice(CImageStream* pStream)
	{
		if (m_pStream == pStream)
		{
			return;
		}
		m_displayImage = cv::Mat();
		m_pStream = pStream;
		emit DoUpdate();
	}
	std::vector<CImageProcessor*> GetStreamOwnerAlg();

	QPoint m_checkBoxRectLT, m_checkBoxRectrRB;
	bool m_isDrawTrackCheckBox = false;
private:
	CImageStream* m_pStream;
	cv::Mat m_displayImage;//Mat 展示图像
	std::mutex m_imgMutex;
	QPixmap m_pixelmapShow;//像素展示图像
	QTime m_timeLastDisplay;
	double m_target_x;
	double m_target_y;
protected:
	void paintEvent(QPaintEvent* event);
	QImage convertMattoQImage(cv::Mat& mat);
	int m_nImageWidth;//展示图像宽
	int m_nImageHight;//展示图像高
	QPen  m_PenText;
	QPen  m_PenRegion;
	QPen  m_PenTrack;
	bool m_mouseRightPressFlag = false;
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
signals:
	void DoUpdate();
	void sig_Resize();
	void MouseLeftClick(int x, int y);
	void MouseRightClick(int x, int y);
	void MouseDoubleClick(double x, double y);
	void MouseRightRelease(int x, int y);
protected:
	//渲染相机固有信息
	void renderCameraInfo(QPainter& painter);
	//渲染算法执行效果
	void renderTaskInfo(CImageProcessor* pProcessor, QPainter& painter);
};

#endif
