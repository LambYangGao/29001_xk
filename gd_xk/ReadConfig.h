#ifndef READCONFIG_H_
#define READCONFIG_H_

class CReadConfig {
public:
	CReadConfig();
	virtual ~CReadConfig();

public:
	int ReadConf(char* file, char* AppName, char* KeyName, char* KeyVal);
	int WriteConf(char* file, char* AppName, char* KeyName, char* KeyVal);
private:
	int getPos(char* buf);
	char* trimSp(char* buf);


};
#endif