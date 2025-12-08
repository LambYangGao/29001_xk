#ifndef LOGINFO_H
#define LOGINFO_H
#include <mutex>
#include <sstream>
#include <time.h>
#include <fstream>
using namespace std;

class LogInfo
{
public:
    LogInfo(int maxFileLenKb, string filename);
    ~LogInfo();

    void writeLog(std::string inStr);//
    void writeLog_withoutendl(std::string inStr);
    void start();
    void stop();
    std::string getTimeMarkFileName(string filename);
    std::string getShortTime();

public:
    std::mutex logMutex;
    bool bClearLogContent = false;//清空log内容标志
    ofstream m_logFile;
    int m_nMaxFileLenKb;
    string m_filename;
};

#endif // LOGINFO_H
