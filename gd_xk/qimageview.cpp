#include "qimageview.h"
#include <QMutexLocker>
#include<qdebug.h>
#include <QMessageBox>
#include <qtoolbutton.h>
#include <qdatetime.h>
#include "windows.h"

QImageView::QImageView(QWidget *parent, CImageStream *pStream)
	: QLabel(parent)
{
	m_pStream = pStream;
	connect(this, SIGNAL(DoUpdate()), this, SLOT(update()));
	setWordWrap(true);
	m_nImageWidth = 0;
	m_nImageHight = 0;
	m_PenText.setWidth(3);
	m_PenRegion.setWidth(3);
	m_PenRegion.setColor(QColor(0, 255, 0));
	m_timeLastDisplay = QTime::currentTime();
	m_PenTrack.setWidth(1);
	m_PenTrack.setColor(QColor(0,255,0));
}

QImageView::~QImageView(void)
{

}

void QImageView::renderCameraInfo(QPainter &painter)
{
	painter.setFont(QFont(QStringLiteral("黑体"), 20));
	painter.setPen(m_PenRegion);
	//painter.setOpacity(0.5);//透明度
	//显示相机固有信息
	QString strCamInfo;
	//QDateTime qdt = QDateTime::currentDateTime();
	//strCamInfo = qdt.toString("yyyy-MM-dd hh:mm:ss");
	strCamInfo = QStringLiteral("");
	painter.drawText(QRectF(50, rect().height() - 80, rect().width(), 100), Qt::AlignLeft | Qt::AlignTop, strCamInfo);
}

void QImageView::renderTaskInfo(CImageProcessor* pProcessor, QPainter& painter)
{
	if (pProcessor)
	{
		if (!pProcessor->status().isEmpty())
		{
			painter.setFont(QFont(QStringLiteral("微软雅黑"), 16));
			painter.drawText(geometry(), Qt::AlignCenter, pProcessor->status());
		}
		if (pProcessor->m_renderArry.size() > 0)
		{
			painter.setFont(QFont(QStringLiteral("微软雅黑"), 14));
			pProcessor->m_renderArry[pProcessor->m_renderArry.size() - 1].renderToWnd(painter, geometry());
			if (pProcessor->m_renderArry.size() > 1)
			{
				pProcessor->m_renderArry.pop_front();
			}
		}
	}
}

void QImageView::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);
}

std::vector<CImageProcessor*>  QImageView::GetStreamOwnerAlg(void)
{
	//return GetMainWind()->m_activeAlg;
	std::vector<CImageProcessor*> m_activeAlg;//激活的算法
	return m_activeAlg;//激活的算法
}

QImage QImageView::convertMattoQImage(cv::Mat& mat)
{

	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	else if (mat.type() == CV_8UC3)
	{

		const uchar *pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

		return image;// .rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		const uchar *pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}

void QImageView::mouseMoveEvent(QMouseEvent* event)
{
	//移动框
	m_checkBoxRectrRB = event->pos();
	//
	Q_UNUSED(event);
}

void QImageView::mousePressEvent(QMouseEvent* event)
{
	// 如果是鼠标左键按下
	if (event->button() == Qt::LeftButton)
	{
		//调整伺服到指定位置
	    //emit MouseLeftClick(event->pos().x(), event->pos().y());
	}
	// 如果是鼠标右键按下
	else if (event->button() == Qt::RightButton)
	{
		m_mouseRightPressFlag = true;
		//进入跟踪模式
		emit MouseRightClick(event->pos().x(), event->pos().y());
		//开始画框
		m_isDrawTrackCheckBox = true;
		m_checkBoxRectLT = event->pos();
		m_checkBoxRectrRB = event->pos();
	}
	Q_UNUSED(event);
}

void QImageView::mouseReleaseEvent(QMouseEvent* event)
{
	// 如果是鼠标左键抬起
	if (event->button() == Qt::LeftButton)
	{
		//调整伺服到指定位置
		emit MouseLeftClick(event->pos().x(), event->pos().y());
	}
	// 如果是鼠标右键抬起
	else if (event->button() == Qt::RightButton)
	{
		m_mouseRightPressFlag = false;
		//取消框
		m_isDrawTrackCheckBox = false;
		//进入跟踪模式
		emit MouseRightRelease(event->pos().x(), event->pos().y());
	}
}


void QImageView::mouseDoubleClickEvent(QMouseEvent* event)
{

}

void QImageView::resizeEvent(QResizeEvent* event)
{
	emit sig_Resize();
}

void QImageView::SetDisplayImage(cv::Mat &mat)
{
	if (!isVisible())
	{
		//return;
	}

	//控制刷新率
	QTime timeNow = QTime::currentTime();
	if (abs(m_timeLastDisplay.msecsTo(timeNow)) < 70)
	{
		return;
	}
	else
	{
		//
	}
	m_timeLastDisplay = timeNow;

	//设置图像
	if (mat.rows==0 || mat.cols==0 || mat.data==0)
	{
		return;
	}else
	{
		//
	}
	m_displayImage = mat;
	m_nImageWidth = mat.cols;
	m_nImageHight = mat.rows;
	cv::Mat tmpMat;
	cv::cvtColor(mat, tmpMat, CV_BGR2RGB);
	QImage imgShow = convertMattoQImage(tmpMat);// m_displayImage);
	m_imgMutex.lock();
	m_pixelmapShow = QPixmap::fromImage(imgShow);
	m_imgMutex.unlock();

	//触发控件更新信号
	emit DoUpdate();
}

void QImageView::SetTarget(double x, double y)
{
	m_target_x = x;
	m_target_y = y;
}


