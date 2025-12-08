#include "loginfo.h"
#include<iostream>
#include<QDateTime>

LogInfo::LogInfo(int maxFileLenKb, string filename)
{
    m_nMaxFileLenKb = maxFileLenKb;
    m_filename = filename;
}

LogInfo::~LogInfo()
{
    m_logFile.close();
}

std::string LogInfo::getTimeMarkFileName(string filename)
{
    //time_t currtt;
    //currtt = time(NULL);
    //struct tm *localt;
    //localt = localtime(&currtt);

    //char path[256];
    //getcwd(path,256);


    //std::string filename;
//    QDateTime currentTime = QDateTime::currentDateTime();
//    QString timeStr = currentTime.toString("yyyy-MM-dd-hh-mm-ss");

//    std::stringstream sst;
//    sst<<"/root/WrtLog/Info/logfile_"<<localt->tm_year<<"-"<<localt->tm_mon<<"-"<<localt->tm_mday<<"-"<<localt->tm_hour<<
//         "-"<<localt->tm_min<<"-"<<localt->tm_sec<<".txt";

    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeStr = currentTime.toString("yyyy-MM-dd-hh-mm-ss");

    std::stringstream sst;
    sst << filename << "-" << timeStr.toStdString() << ".txt";
    return sst.str();

}

string LogInfo::getShortTime()
{
    //time_t currtt;
    //currtt = time(NULL);
    //struct tm *localt;
    //localt = localtime(&currtt);
    //std::stringstream sst;
    //sst<<localt->tm_hour<<":"<<localt->tm_min<<":"<<localt->tm_sec<<" :";
    //return sst.str();

    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeStr = currentTime.toString("hh:mm:ss:zzz:");
    return timeStr.toStdString();
}

void LogInfo::writeLog(std::string inStr)
{
    logMutex.lock();
    //如果log日志文件大于5120KB,拷贝到新文件名log文件，清空原log内容
    if (bClearLogContent)
    {
        std::string filePathName = getTimeMarkFileName(m_filename);
        m_logFile.open(filePathName,ios::out | ios::trunc);
        bClearLogContent = false;
    }
    m_logFile.seekp(0,m_logFile.end);
    int logsize = m_logFile.tellp()/1024;
    //如果文本大于m_nMaxFileLenKbKB
    if (logsize > (m_nMaxFileLenKb-1))
    {
        m_logFile<<getShortTime()<<inStr<<std::endl;
        m_logFile.flush();

        m_logFile.close();
        //置清空标志
         bClearLogContent = true;
         logMutex.unlock();
         return;
    }

    m_logFile<<getShortTime()<<inStr<<std::endl;
    m_logFile.flush();

    logMutex.unlock();
}

void LogInfo::writeLog_withoutendl(std::string inStr)
{
    logMutex.lock();
    //如果log日志文件大于5120KB,拷贝到新文件名log文件，清空原log内容
    if (bClearLogContent)
    {
        std::string filePathName = getTimeMarkFileName(m_filename);
        m_logFile.open(filePathName, ios::out | ios::trunc);
        bClearLogContent = false;
    }
    m_logFile.seekp(0, m_logFile.end);
    int logsize = m_logFile.tellp() / 1024;
    //如果文本大于m_nMaxFileLenKbKB
    if (logsize > (m_nMaxFileLenKb - 1))
    {
        m_logFile << getShortTime() << inStr << std::endl;
        m_logFile.flush();

        m_logFile.close();
        //置清空标志
        bClearLogContent = true;
        logMutex.unlock();
        return;
    }

    m_logFile << getShortTime() << inStr ;
    m_logFile.flush();

    logMutex.unlock();
}

void LogInfo::start()
{
    std::string filePathName = getTimeMarkFileName(m_filename);
    m_logFile.open(filePathName, ios::out | ios::app);
}

void LogInfo::stop()
{
    m_logFile.close();
}
