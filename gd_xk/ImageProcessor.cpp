#include "ImageProcessor.h"
#include <QCoreApplication>
#include <opencv2/highgui.hpp>
//#include "DeviceWorkGroup.h"
//#include "QJsonUtil.h"
//#include "SystemInfo.h"

CImageProcessor::CImageProcessor(CImageStream *pOwner)
{
	m_bAble = true;
	m_bUseROI = false;
	m_strName = "";
	m_enumType = UnDefined;
	m_pOwner = pOwner;
	m_nDelayFrames = 0;
	m_bActive = false;
	m_nTodayAlarmCount = 0;
	m_nMonthAlarmCount = 0;
	m_timeLastSave = QDateTime(QDate(2000,1,1));
	if (m_pOwner)
	{
		//m_currentRenderInfo = RenderInfo(m_pOwner->getWorkGroup()->Name(),m_pOwner->Name());
	}
	m_timeTaskStart = QDateTime::currentDateTime();
	m_pTaskItem = nullptr;
	

}
CImageProcessor::CImageProcessor(QJsonObject &json, CImageStream *pOwner /* = nullptr */)
{
	m_bAble = true;
	m_bUseROI = false;
	m_pOwner = pOwner;
	m_nDelayFrames = 0;
	m_bActive = false;
	QJsonArray workTime=json["workSpans"].toArray();
	for (int i = 0; i < workTime.size();i++)
	{
		QJsonObject time = workTime[i].toObject();
		WorkSpanTime workTime;
		workTime.timeStart =QTime::fromString(time["timeBeigin"].toString()) ;
		workTime.timeStop = QTime::fromString(time["timeEnd"].toString());
		m_WorkSpanTimes.push_back(workTime);

	}
	m_enumType = (CImageProcessor::TASK_TYPE)json["type"].toInt();
	m_bAble = json["Enable"].toBool();
	m_strName = json["name"].toString();
	m_strDescrption = json["decription"].toString();
	m_nTodayAlarmCount = json["todayAlarmCount"].toInt(0);
	m_nMonthAlarmCount = json["monthAlarmCount"].toInt(0);
	m_strTaskID = json["taskID"].toString();
	m_timeTaskStart = QDateTime::fromString(json["taskCreateTime"].toString());
	if (m_nMonthAlarmCount==0)
	{
		m_nMonthAlarmCount = m_nTodayAlarmCount;
	}
	m_timeLastSave = QDateTime(QDate(2000, 1, 1));
	if (m_pOwner)
	{
		//m_currentRenderInfo = RenderInfo(m_pOwner->getWorkGroup()->Name(), m_pOwner->Name());
		m_currentRenderInfo = RenderInfo("test", "test");
	}
	m_pTaskItem = nullptr;
	
}

CImageProcessor::~CImageProcessor(void)
{

}

void CImageProcessor::setReportInterval(int secsInterval)
{
	m_alarmReportInterval = secsInterval;
}


void CImageProcessor::setROI(cv::Rect &rectROI)
{
	m_rectROI = rectROI;
	m_bUseROI = true;
}
void CImageProcessor::addWorkSpanTime(WorkSpanTime spanTime)
{
	m_WorkSpanTimes.push_back(spanTime);
}
void CImageProcessor::getWorkSpanTimes(std::vector<WorkSpanTime> &spanList)
{
	spanList = m_WorkSpanTimes;
}
void CImageProcessor::setWorkSpanTimes(std::vector<WorkSpanTime> &spanList)
{
	m_WorkSpanTimes = spanList;
}
//bool CImageProcessor::makeNotice(QString strMessage, cv::Mat imgMessage, CMessage::MESSAGETYPE type, QString strLoc, QString strGroup)
//{
//	m_alarmArry.push_back(CMessage(strMessage,imgMessage,type,strLoc,strGroup));
//	return true;
//}
void CImageProcessor::resetWorkSpanTime(void)
{
	m_WorkSpanTimes.clear();
}
bool CImageProcessor::isWorkingTime(void)
{
	if (m_WorkSpanTimes.size()==0)
	{
		return true;
	}
	QTime timeNow = QTime::currentTime();
	for (int i=0;i<m_WorkSpanTimes.size();i++)
	{
		if (timeNow>m_WorkSpanTimes[i].timeStart && timeNow<m_WorkSpanTimes[i].timeStop)
		{
			return true;
		}
	}
	return false;
}
bool CImageProcessor::checkContinue(cv::Mat &img)
{
	if (!isWorkingTime())
	{
		m_strStatus = QStringLiteral("%1(非工作时间)").arg(m_strName);
		if (m_pTaskItem)
		{
			m_pTaskItem->setText(1, QStringLiteral("非工作时间"));
		}
		return false;
	}
	if (!m_bAble)
	{
		m_strStatus = QStringLiteral("%1(任务暂停)").arg(m_strName);
		return false;
	}
	if (img.data == nullptr || img.rows<2 || img.cols<2)
	{
		return false;
	}
	m_strStatus = "";
	return true;
}

QJsonObject CImageProcessor::toJson(void)
{
	QJsonArray workTime;
	for (int i=0;i<m_WorkSpanTimes.size();i++)
	{
		QJsonObject workSpan{
			{"timeBeigin",m_WorkSpanTimes[i].timeStart.toString()},
			{ "timeEnd",m_WorkSpanTimes[i].timeStop.toString() }
		};
		workTime.push_back(workSpan);
	}
	
	QJsonObject baseParam{
		{"type",m_enumType},
		{"Enable",m_bAble},
		{"name",m_strName},
		{"decription",m_strDescrption},
		{"workSpans",workTime},
		{"todayAlarmCount",m_nTodayAlarmCount},
		{"monthAlarmCount",m_nMonthAlarmCount},
		{"taskCreateTime",m_timeTaskStart.toString()},
		{"taskID",m_strTaskID}
	
	};
	return baseParam;
}

QString CImageProcessor::modifyParam(QJsonObject &req) {
	QString keys = "";
	QJsonObject speVal = req["specialVal"].toObject();
	/*if (QJsonUtil::KeysNotContain(speVal, QStringList() << "newTaskName") == "") {
		m_strName = speVal["newTaskName"].toString();
	}
	if (QJsonUtil::KeysNotContain(req, QStringList() << "Enable") == "") {
		m_bAble = req["Enable"].toBool();
	}*/
	QJsonArray workTime = req["workSpans"].toArray();
	m_WorkSpanTimes.clear();
	for (int i = 0; i < workTime.size(); i++)
	{
		QJsonObject time = workTime[i].toObject();
		WorkSpanTime workTime;
		workTime.timeStart = QTime::fromString(time["timeBeigin"].toString());
		workTime.timeStop = QTime::fromString(time["timeEnd"].toString());
		m_WorkSpanTimes.push_back(workTime);
	}
	return keys;
}

void CImageProcessor::pushImage(cv::Mat &img)
{
	QDateTime curTime = QDateTime::currentDateTime();
	m_Mutex.lock();

	if (m_imgQueue.size() > 66)

//	if (m_imgQueue.size() > 38)
	{
		m_imgQueue.pop_front();
	}
	if (m_bisSaving)
	{
		m_nDelayFrames++;
	}
	if ((img.cols > 1280) || (img.rows > 720))
	{
		cv::Mat img_clone = img.clone();
		cv::resize(img_clone, img_clone, cv::Size(1280, 720));
		m_imgQueue.push_back(img_clone);
	}
	else
	{
		m_imgQueue.push_back(img);
	}
	if (m_bisSaving && m_timeLastSave.msecsTo(curTime)>1000)
	{
		m_bisSaving = false;
		if (m_imgQueue.size() < 10)
		{
			m_Mutex.unlock();
			return;
		}
		if (!m_imgQueue[0].data || m_imgQueue[0].rows < 10 || m_imgQueue[0].cols < 10)
		{
			m_Mutex.unlock();
			return;
		}

		m_timeLastSave = QDateTime::currentDateTime();
		cv::VideoWriter videoWriter;

		videoWriter.open(m_strSaveVideoName.toLocal8Bit().data(), cv::VideoWriter::fourcc('H', '2', '6', '4'), 5, m_imgQueue[0].size());

		for (int i = 0; i < m_imgQueue.size()-2; i++)
		{
			if (!m_imgQueue[i].data || m_imgQueue[i].rows < 10 || m_imgQueue[i].cols < 10)
			{
				continue;
			}
			videoWriter << m_imgQueue[i];
		}
		
		videoWriter.release();
	
		m_nDelayFrames = 0;

	}
	m_Mutex.unlock();
}

void CImageProcessor::saveVieo(QString strName)
{
	m_timeLastSave = QDateTime::currentDateTime();
	m_bisSaving = true;
	m_strSaveVideoName = QStringLiteral("%1/LocalVideo/%2(%3).mp4").arg(QCoreApplication::applicationDirPath()).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss")).arg(strName);
	m_nDelayFrames = 0;
	
	
}

void CImageProcessor::saveVideo(long long strName)
{
	m_timeLastSave = QDateTime::currentDateTime();
	m_bisSaving = true;
	m_strSaveVideoName = QStringLiteral("%1/LocalVideo/%2.mp4").arg(QCoreApplication::applicationDirPath()).arg(strName);
	m_nDelayFrames = 0;
	
}
