#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <QString>
#include <QTime>
#include <QColor>
#include <QSettings>
#include <queue>
//#include "Message.h"
#include <mutex>
#include <QJsonObject>
#include <QJsonArray>
//#include "DeviceImage.h"
#include <QPainter>
#include <QTreeWidgetItem>
//#include<GPUImageProcessor.h>
//#pragma  comment(lib,"GPUImageProcessor.lib")
//#pragma  comment(lib,"DeviceImage.lib")
//using namespace std;


class CImageStream;
//定义工作区间
struct WorkSpanTime
{
	QTime timeStart;//开始时间
	QTime timeStop;//结束时间
};
struct MessageInfo
{
	MessageInfo(QString strInfo, float dX = 0.2, float dY = 0.1)
	{
		ptOri.x = dX;
		ptOri.y = dY;
		strMessage = strInfo;
		color = Qt::yellow;
	}
	MessageInfo(void)
	{
		color = Qt::yellow;
	}
	cv::Point2f ptOri;
	QString  strMessage;
	QColor   color;
	QJsonObject toJson(void) {

		return QJsonObject{
			{"type","txt"},
			{"x",ptOri.x},
			{"y",ptOri.y},
			{"txt",strMessage},
			{"r",color.red()},
			{ "g",color.green()},
			{"b",color.blue()}

		};
	}
	//通过图像坐标和图像，计算归一化坐标，并传递文本信息
	void Identity(int x, int y, QString& str, cv::Mat& img, QColor clr = Qt::yellow)
	{
		ptOri.x = (float)x / (float)img.cols;
		ptOri.y = (float)y / (float)img.rows;
		strMessage = str;
		color = clr;
	}
	void Identity(int x, int y, QString str, cv::Mat& img, QColor clr = Qt::yellow)
	{
		ptOri.x = (float)x / (float)img.cols;
		ptOri.y = (float)y / (float)img.rows;
		strMessage = str;
		color = clr;
	}
	void Identity(int x, int y, QString& str, int imgw, int imgh, QColor clr = Qt::yellow)
	{
		ptOri.x = (float)x / (float)imgw;
		ptOri.y = (float)y / (float)imgh;
		strMessage = str;
		color = clr;
	}
};
struct RectInfo
{
	cv::Point2f ptOri;
	float dRectWidth;
	float dRectHight;
	QColor color;

	QJsonObject toJson(void) {

		return QJsonObject{
			{ "type","rect" },
			{ "x",ptOri.x },
			{ "y",ptOri.y },
			{ "width",dRectWidth },
			{ "height",dRectHight},
			{ "r",color.red() },
			{ "g",color.green() },
			{ "b",color.blue() }

		};
	}

	//通过图像坐标计算归一化坐标
	void Identity(int x, int y, int nWidth, int nHight, cv::Mat& img, QColor clr = QColor(255, 255, 0))
	{
		ptOri.x = (float)x / (float)img.cols;
		ptOri.y = (float)y / (float)img.rows;
		dRectWidth = (float)nWidth / float(img.cols);
		dRectHight = (float)nHight / float(img.rows);
		color = clr;
	}

	void Offset(float dOffsetX, float dOffsetY)
	{

		ptOri.x += dOffsetX;
		ptOri.y += dOffsetY;
	}

	void Identity(cv::Rect rectImg, cv::Mat& img, QColor clr = QColor(255, 255, 0))
	{
		ptOri.x = (float)rectImg.x / (float)img.cols;
		ptOri.y = (float)rectImg.y / (float)img.rows;
		dRectWidth = (float)rectImg.width / float(img.cols);
		dRectHight = (float)rectImg.height / float(img.rows);
		color = clr;
	}

	void mapROI2SrcCoord(cv::Rect rectImg, cv::Size& sizeSrc, cv::Rect2f rectSubNormal)
	{
		if (rectSubNormal.width > 0.05 && rectSubNormal.height > 0.05)
		{
			cv::Rect2f rectSub(rectSubNormal.x * sizeSrc.width, rectSubNormal.y * sizeSrc.height, rectSubNormal.width * sizeSrc.width, rectSubNormal.height * sizeSrc.height);
			ptOri.x = rectSubNormal.x + ((float)rectImg.x / (float)rectSub.width) * ((float)rectSub.width / (float)sizeSrc.width);
			ptOri.y = rectSubNormal.y + ((float)rectImg.y / (float)rectSub.height) * ((float)rectSub.height / (float)sizeSrc.height);
			dRectWidth = ((float)rectImg.width / (float)rectSub.width) * ((float)rectSub.width / (float)sizeSrc.width);
			dRectHight = ((float)rectImg.height / (float)rectSub.height) * ((float)rectSub.height / (float)sizeSrc.height);
		}
		else
		{

			ptOri.x = (float)rectImg.x / (float)sizeSrc.width;
			ptOri.y = (float)rectImg.y / (float)sizeSrc.height;
			dRectWidth = (float)rectImg.width / float(sizeSrc.width);
			dRectHight = (float)rectImg.height / float(sizeSrc.height);
		}


	}
	void Identity(cv::Rect rectImg, int nImgWidth, int nImgHight, QColor clr = QColor(255, 255, 0))
	{
		ptOri.x = (float)rectImg.x / (float)nImgWidth;
		ptOri.y = (float)rectImg.y / (float)nImgHight;
		dRectWidth = (float)rectImg.width / float(nImgWidth);
		dRectHight = (float)rectImg.height / float(nImgHight);
		color = clr;
	}
};
struct CircleInfo
{
	cv::Point2f ptOri;
	float fRadius;
	QColor color;

	QJsonObject toJson(void) {

		return QJsonObject{
			{ "type","circle" },
			{ "x",ptOri.x },
			{ "y",ptOri.y },
			{ "radius",fRadius },
			{ "r",color.red() },
			{ "g",color.green() },
			{ "b",color.blue() }

		};
	}

	//通过图像坐标计算归一化坐标
	void Identity(int x, int y, int nRadius, cv::Mat& img, QColor clr = QColor(255, 255, 0))
	{
		ptOri.x = (float)x / (float)img.cols;
		ptOri.y = (float)y / (float)img.rows;
		fRadius = (float)nRadius / float(img.cols);
		color = clr;
	}

	void Offset(float dOffsetX, float dOffsetY)
	{

		ptOri.x += dOffsetX;
		ptOri.y += dOffsetY;
	}

};
struct LineInfo
{
	cv::Point2f ptOri;
	cv::Point2f ptEnd;
	QColor color;

	QJsonObject toJson(void) {

		return QJsonObject{
			{ "type","line" },
			{ "x",ptOri.x },
			{ "y",ptOri.y },
			{ "x2",ptEnd.x },
			{ "y2",ptEnd.y },
			{ "r",color.red() },
			{ "g",color.green() },
			{ "b",color.blue() }

		};
	}
	//通过图像坐标计算归一化坐标
	void Identity(cv::Point2f& pt1, cv::Point2f& pt2, cv::Mat& img, QColor clr = QColor(255, 255, 0))
	{
		ptOri.x = (float)pt1.x / (float)img.cols;
		ptOri.y = (float)pt1.y / (float)img.rows;
		ptEnd.x = (float)pt2.x / (float)img.cols;
		ptEnd.y = (float)pt2.y / (float)img.rows;
		color = clr;
	}
	void Identity(cv::Point pt1, cv::Point pt2, cv::Mat& img, QColor clr = QColor(255, 255, 0))
	{
		ptOri.x = (float)pt1.x / (float)img.cols;
		ptOri.y = (float)pt1.y / (float)img.rows;
		ptEnd.x = (float)pt2.x / (float)img.cols;
		ptEnd.y = (float)pt2.y / (float)img.rows;
		color = clr;
	}

	void Identity(cv::Point2f& pt1, cv::Point2f& pt2, int nImgWidth, int nImgHight, QColor clr = QColor(255, 255, 0))
	{
		ptOri.x = (float)pt1.x / (float)nImgWidth;
		ptOri.y = (float)pt1.y / (float)nImgHight;
		ptEnd.x = (float)pt2.x / (float)nImgWidth;
		ptEnd.y = (float)pt2.y / (float)nImgHight;
		color = clr;
	}


};
//封装渲染信息,采用归一化坐标系
class RenderInfo {

public:
	RenderInfo(QString strGroup, QString strDev)
	{
		m_strGroup = strGroup;
		m_strAdress = strDev;
	}
	RenderInfo(void)
	{
	}
	//转换为json格式
	QJsonObject toJson(void)
	{
		QJsonArray msgArry;
		for (int i = 0; i < m_messageArry.size(); i++)
		{
			msgArry.push_back(m_messageArry[i].toJson());
		}
		return  QJsonObject{

			{"renderArry",msgArry},
			{"group",m_strGroup},
			{"adress",m_strAdress}
		};
	}

	//渲染到窗口
	void renderToWnd(QPainter& painter, QRect rectRenderArea)
	{

		//显示文本消息
		for (int i = 0; i < m_messageArry.size(); i++)
		{

			painter.setPen(m_messageArry[i].color);
			painter.drawText(QPoint(m_messageArry[i].ptOri.x * rectRenderArea.width(), m_messageArry[i].ptOri.y * rectRenderArea.height()), m_messageArry[i].strMessage);
		}
		//显示矩形区域
		for (int i = 0; i < m_rectArry.size(); i++)
		{
			QPen pen(m_rectArry[i].color);
			pen.setWidth(2);
			painter.setPen(pen);
			int nX = m_rectArry[i].ptOri.x * rectRenderArea.width();
			int nY = m_rectArry[i].ptOri.y * rectRenderArea.height();
			int nWidth = m_rectArry[i].dRectWidth * rectRenderArea.width();
			int nHight = m_rectArry[i].dRectHight * rectRenderArea.height();
			painter.drawRect(nX, nY, nWidth, nHight);
		}
		//显示圆形区域
		for (int i = 0; i < m_circleArry.size(); i++)
		{
			QPen pen(m_circleArry[i].color);
			pen.setWidth(2);
			painter.setPen(pen);
			int nX = m_circleArry[i].ptOri.x * rectRenderArea.width();
			int nY = m_circleArry[i].ptOri.y * rectRenderArea.height();
			int nRadiu = m_circleArry[i].fRadius * rectRenderArea.width();
			painter.drawEllipse(nX, nY, nRadiu, nRadiu);
		}
		//显示点信息
		for (int i = 0; i < m_ptsArry.size(); i++)
		{
			painter.drawPoint(QPoint(m_ptsArry[i].x * rectRenderArea.width(), m_ptsArry[i].y * rectRenderArea.height()));
		}

		//显示直线
		for (int i = 0; i < m_LineInfo.size(); i++)
		{
			QPen pen(m_LineInfo[i].color);
			pen.setWidth(2);
			painter.setPen(pen);
			painter.drawLine(QPoint(m_LineInfo[i].ptOri.x * rectRenderArea.width(), m_LineInfo[i].ptOri.y * rectRenderArea.height()),
				QPoint(m_LineInfo[i].ptEnd.x * rectRenderArea.width(), m_LineInfo[i].ptEnd.y * rectRenderArea.height()));
		}
	}
	//渲染到图像，opencv的方式
	void renderToImage(cv::Mat& img)
	{
		//显示文本消息
		for (int i = 0; i < m_messageArry.size(); i++)
		{

			cv::putText(img, m_messageArry[i].strMessage.toStdString(), cv::Point(m_messageArry[i].ptOri.x * img.cols, m_messageArry[i].ptOri.y * img.rows), cv::FONT_HERSHEY_COMPLEX, 0.5, CV_RGB(m_messageArry[i].color.red(), m_messageArry[i].color.green(), m_messageArry[i].color.blue()));
		}
		//显示矩形区域
		for (int i = 0; i < m_rectArry.size(); i++)
		{

			int nX = m_rectArry[i].ptOri.x * img.cols;
			int nY = m_rectArry[i].ptOri.y * img.rows;
			int nWidth = m_rectArry[i].dRectWidth * img.cols;
			int nHight = m_rectArry[i].dRectHight * img.rows;
			cv::rectangle(img, cv::Rect(nX, nY, nWidth, nHight), CV_RGB(m_rectArry[i].color.red(), m_rectArry[i].color.green(), m_rectArry[i].color.blue()), 2);

		}
		//显示圆形区域
		for (int i = 0; i < m_circleArry.size(); i++)
		{

			int nX = m_circleArry[i].ptOri.x * img.cols;
			int nY = m_circleArry[i].ptOri.y * img.rows;
			int nRadiu = m_circleArry[i].fRadius * img.cols;
			cv::circle(img, cv::Point(nX, nY), nRadiu, cv::Scalar(m_rectArry[i].color.red(), m_rectArry[i].color.green(), m_rectArry[i].color.blue()), 2);
		}
		//显示点信息
		for (int i = 0; i < m_ptsArry.size(); i++)
		{
			cv::circle(img, cv::Point(m_ptsArry[i].x * img.cols, m_ptsArry[i].y * img.rows), 3, CV_RGB(255, 255, 0), 3);
			//painter.drawPoint(QPoint(m_ptsArry[i].x* rectRenderArea.width(), m_ptsArry[i].y*rectRenderArea.height()));
		}

		//显示直线
		for (int i = 0; i < m_LineInfo.size(); i++)
		{

			cv::line(img, cv::Point(m_LineInfo[i].ptOri.x * img.cols, m_LineInfo[i].ptOri.y * img.rows), cv::Point(m_LineInfo[i].ptEnd.x * img.cols, m_LineInfo[i].ptEnd.y * img.rows), CV_RGB(m_LineInfo[i].color.red(), m_LineInfo[i].color.green(), m_LineInfo[i].color.blue()));
			//painter.drawLine(QPoint(m_LineInfo[i].ptOri.x*rectRenderArea.width(), m_LineInfo[i].ptOri.y*rectRenderArea.height()),
			//	QPoint(m_LineInfo[i].ptEnd.x*rectRenderArea.width(), m_LineInfo[i].ptEnd.y*rectRenderArea.height()));
		}
	}
	//渲染到图像，支持中文渲染
	void renderToImage2(cv::Mat& img)
	{
		QImage Qimg = ConvertMattoQImage(img);
		QPainter painter(&Qimg);
		painter.setFont(QFont(QStringLiteral("微软雅黑"), 22));
		renderToWnd(painter, Qimg.rect());
		img = QImage2cvMat(Qimg);
	}
	void addText(MessageInfo& text) { m_messageArry.push_back(text); }
	void addRect(RectInfo& rect) { m_rectArry.push_back(rect); }
	void addCircle(CircleInfo& circ) { m_circleArry.push_back(circ); }
	void addLine(LineInfo& line) { m_LineInfo.push_back(line); }
	void addPoint(cv::Point2f& pt) { m_ptsArry.push_back(pt); }
	void clearInfo(void)
	{
		m_messageArry.clear();
		m_rectArry.clear();
		m_circleArry.clear();
		m_ptsArry.clear();
		m_LineInfo.clear();
	}
public:
	//显示相关
	std::vector<MessageInfo> m_messageArry;//文本信息
	std::vector<RectInfo> m_rectArry;//矩形区域
	std::vector<CircleInfo> m_circleArry;//圆形区域
	std::vector<cv::Point2f> m_ptsArry;//点序列
	std::vector<LineInfo> m_LineInfo;//线段序列
	std::vector<cv::Point2f> m_ptPaintArrow;//箭头点n*6
	QString m_strGroup;//分组名称
	QString m_strAdress;//设备地址
	QImage ConvertMattoQImage(cv::Mat& mat)
	{

		if (mat.type() == CV_8UC1)
		{
			QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
			// Set the color table (used to translate colour indexes to qRgb values)  
			image.setColorCount(256);
			for (int i = 0; i < 256; i++)
			{
				image.setColor(i, qRgb(i, i, i));
			}
			// Copy input Mat  
			uchar* pSrc = mat.data;
			for (int row = 0; row < mat.rows; row++)
			{
				uchar* pDest = image.scanLine(row);
				memcpy(pDest, pSrc, mat.cols);
				pSrc += mat.step;
			}
			return image;
		}
		// 8-bits unsigned, NO. OF CHANNELS = 3  
		else if (mat.type() == CV_8UC3)
		{
			// Copy input Mat  
			const uchar* pSrc = (const uchar*)mat.data;
			// Create QImage with same dimensions as input Mat  
			QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
			return image.rgbSwapped();
		}
		else if (mat.type() == CV_8UC4)
		{
			//qDebug() << "CV_8UC4";
			// Copy input Mat  
			const uchar* pSrc = (const uchar*)mat.data;
			// Create QImage with same dimensions as input Mat  
			QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
			return image.copy();
		}
		else
		{
			//qDebug() << "ERROR: Mat could not be converted to QImage.";
			return QImage();
		}
	}

	cv::Mat QImage2cvMat(QImage image)
	{
		cv::Mat mat;
		//qDebug() << image.format();
		switch (image.format())
		{
		case QImage::Format_ARGB32:
		case QImage::Format_RGB32:
		case QImage::Format_ARGB32_Premultiplied:
			mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
			break;
		case QImage::Format_RGB888:
		{
			cv::Mat matTemp = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
			cv::cvtColor(matTemp, mat, CV_BGR2RGB);
			break;
		}
		case QImage::Format_Indexed8:
			mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
			break;
		}
		return mat;
	}

};
//图像处理基类

class CImageProcessor
{
public:
	enum TASK_TYPE//任务类型
	{
		BaseFaceRecognize = -2,//人脸识别基础类
		BaseSkeletonDetector = -3,//骨架提取基础类
		BaseObjectDetector = -4,//目标识别分类基础类
		UnDefined = -1,//未定义类型
		Set_ImageROI = 0,//设置感兴趣区域
		ObjectOnSea_Detector = 1,//海上物体检测
		Video_Writer = 2,//视频录相
		PersonVehicle_Detector = 3,//人车检测
		ObjectOnSeaClasic_Detector = 4,//海上物体检测-传统
	};
	CImageProcessor(CImageStream* pOwner = nullptr);
	CImageProcessor(QJsonObject& json, CImageStream* pOwner = nullptr);
	virtual ~CImageProcessor();

	virtual bool apply(cv::Mat& img) = 0;


	//virtual bool apply(DeviceImage &img) { return true; }
	virtual QJsonObject toJson();//将对象转换为json对象,对象序列化、网络转发都使用json实现
	virtual QString modifyParam(QJsonObject& req);//设置参数，返回未成功的keys
	bool checkContinue(cv::Mat& img);//检查任务本次是否继续执行，供子类调用，一般图像无效、用户暂停、不在工作时间范围内的情况下返回false,否则返回true

	//bool checkContinue(DeviceImage &img);
	void setOwner(CImageStream* pOwner) { m_pOwner = pOwner; }//设置算法父节点
	CImageStream* getOwner() { return m_pOwner; }//获取算法父节点
	void Disable(void) {
		m_bAble = false;
		if (m_pTaskItem)
		{
			m_pTaskItem->setText(1, QStringLiteral("已暂停"));
		}
	}//使算法处于停止工作状态
	void Enable(void) { m_bAble = true; }//激活算法的工作状态
	void setAcitive(bool bActive = true) { m_bActive = bActive; }
	bool isActive(void) { return m_bActive; }
	bool IsEnabled(void) {
		if (!m_bAble) {
			m_renderArry.clear();
			m_strStatus = QStringLiteral("%1(任务暂停)").arg(m_strName);
		}
		return m_bAble;
	}//获取当前工作状态
	QString getDescrption(void) { return m_strDescrption; }//获取算法运算过程中的描述信息
	void setROI(cv::Rect& rectROI);//设置算法的ROI区域
	cv::Rect getROI(void) { return m_rectROI; }//设置算法ROI区域
	void resetROI(void) { m_bUseROI = false; }//重置算法的ROI区域,使当前的ROI区域无效
	QString Name(void) { return m_strName; }//获取实例名称
	QString status(void) { return m_strStatus; }//获取工作状态
	TASK_TYPE type(void) { return m_enumType; }//获取实例的类型
	void addWorkSpanTime(WorkSpanTime spanTime);//添加实例工作区间
	void getWorkSpanTimes(std::vector<WorkSpanTime>& spanList);//获取实例的所有工作区间
	void resetWorkSpanTime(void);//重置所有工作区间
	void setWorkSpanTimes(std::vector<WorkSpanTime>& spanList);//覆盖工作区间
	//bool makeNotice(QString strMessage, cv::Mat imgMessage, CMessage::MESSAGETYPE type, QString strLoc, QString strGroup);//产生一条告警通知
	//static cv::Mat fromGpuImage(DeviceImage & devImage);

	//std::deque<CMessage> m_alarmArry;//消息队列
	QTreeWidgetItem* m_pTaskItem;
	//显示相关


	std::deque<RenderInfo> m_renderArry;//渲染序列
	RenderInfo m_currentRenderInfo;//当前的渲染
	std::vector<cv::Point2f> m_ptPaintArrow;//箭头点n*6
	int m_nTodayAlarmCount;//任务今日告警数量
	int m_nMonthAlarmCount;//本月告警数量
	QDateTime m_timeTaskStart;//任务创建时间
	QString m_strTaskID;
protected:

	bool m_bActive;//是否当前活跃任务
	CImageStream* m_pOwner;//实例所属设备
	bool m_bAble;//是否暂停工作的标记
	QString m_strDescrption;//运行过程中的描述
	QString m_strStatus;//工作状态
	cv::Rect2f m_rectROI;//工作ROI区域
	bool m_bUseROI;
	QString m_strName;
	TASK_TYPE m_enumType;
	std::vector<WorkSpanTime> m_WorkSpanTimes;
	bool isWorkingTime(void);//判断当前是否在工作时间范围内

	void clearInfo(void) {

		m_currentRenderInfo.clearInfo();
		m_ptPaintArrow.clear();
	}

	//保存视频相关
	int m_nDelayFrames;
	bool m_bisSaving;
	std::deque<cv::Mat> m_imgQueue;//SDK方式或者软件方式的图像序列
	//std::deque<DeviceImage> m_devimgQueue;//硬件图像序列
	std::deque<RenderInfo>  m_saveVideoRenderArry;//保存图像的渲染信息
	//void pushImage(DeviceImage &img);
	void pushImage(cv::Mat& img);
	void saveVieo(QString strName);
	void saveVideo(long long strName);//用来发送给服务器的

	int m_alarmReportInterval;//秒,告警间隔
	void setReportInterval(int secsInterval);

	QDateTime m_timeLastSave;
	std::mutex m_Mutex;
	QString m_strSaveVideoName;
};
#endif
