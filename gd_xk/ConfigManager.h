#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
class ConfigManager
{
private:
	std::string string_replace(std::string source, std::string find, std::string replace);
	//用于支持配置文件中的字符串转数字
	template <class T>
	void convertFromString(T& value, const std::string& s) {
		std::stringstream ss(s);
		ss.precision(s.length());
		ss >> value;
	}
	//用于去除字符串多余的空格
	std::string trim(std::string text);
	//用于支持将多行的配置文件分割开来
	void Stringsplit(std::string str, const char split, std::vector<std::string>& strList);
	//用于支持将 key=value 格式的配置文件分割开来（只分割一次）
	void Stringsplit2(std::string str, const char split, std::vector<std::string>& strList);


public:


	std::string CharToStr(char* conttentChar);
	bool rewrite(std::string& filename, std::vector<std::string>& lineDatas);
	bool modifyContentInfile(std::string filename,std::string key,std::string content);

	ConfigManager(void) {
	}
	ConfigManager(std::string fname) {
		parse_file(fname);
		if (read("print_cfg", 0) > 0) {//print_cfg>0时输出配置文件
			print();
		}
	}

	std::map<std::string, std::string> maps;
	//解析配置文件，并添加默认配置
	void parse_file(std::string fname) {
		std::string strdata;
		try {
			std::ifstream in(fname, std::ios::in);
			std::istreambuf_iterator<char> beg(in), end;
			strdata = std::string(beg, end);
			in.close();
			if (strdata.length() < 10) {
				std::cout << fname << " context is not correct! " << std::endl;
			}
		}
		catch (...) {
			std::cout << "Read " << fname << " error! " << std::endl;
		}

		std::vector<std::string> strList;
		Stringsplit(strdata, '\n', strList);
		//std::map<std::string, std::string> maps;
		for (int i = 0; i < strList.size(); i++) {
			std::vector<std::string> tmp1, tmp2;
			if (strList[i].length() >= 1) {
				Stringsplit2(strList[i], '#', tmp1);//用于清除注释  注释存储在trim(tmp1[1])中
				if (tmp1.size() >= 1) {
					Stringsplit2(tmp1[0], '=', tmp2);//把字符串分为两节
					if (tmp2.size() > 1) {
						maps.insert({ trim(tmp2[0]),trim(tmp2[1]) });//去除字符串多余的空格（包含 \n\r\t）
					}
				}
			}
		}
		return;
	}
	//用于输出配置文件，或保存配置文件
	void print(std::string file_name = "") {
		std::map<std::string, std::string>::iterator iter1;
		std::string str = "";
		for (iter1 = maps.begin(); iter1 != maps.end(); iter1++)
		{
			str += iter1->first + "=" + iter1->second + "\n";
		}
		if (file_name.length() == 0) {
			std::cout << str;
		}
		else {
			// 向文件里写数据
			std::ofstream os;     //创建一个文件输出流对象
			// os.open("../books.txt", std::fstream::out|std::fstream::app);//将对象与文件关联, app就是每次在文件后面继续添加内容
			os.open(file_name, std::fstream::out);//将对象与文件关联
			os << str;   //将输入的内容放入txt文件中
			os.close();
		}
	}
	//用于安全读取配置文件（只用config.find(key)->second写错了key会导致报错）
	std::string read(std::string key, std::string defaultv = "") {
		auto it = maps.find(key);
		if (it == maps.end()) {
			return defaultv;
		}
		else {
			return it->second;
		}
	}
	//用于安全读取配置文件 int类型（只用config.find(key)->second写错了key会导致报错）
	int read(std::string key, int defaultv = 0) {
		auto it = maps.find(key);
		if (it == maps.end()) {
			return defaultv;
		}
		else {
			std::string s = it->second;
			int res;
			convertFromString(res, s);
			return res;
		}
	}
	//用于安全读取配置文件 float类型（只用config.find(key)->second写错了key会导致报错）
	float read(std::string key, float defaultv = 0) {
		auto it = maps.find(key);
		if (it == maps.end()) {
			return defaultv;
		}
		else {
			std::string s = it->second;
			float res;
			convertFromString(res, s);
			return res;
		}
	}
	//用于配置文件赋值，当key不存在时为新增
	void set(std::string key, std::string value) 
	{
		//auto it = maps.find(key);
		//if (it != maps.end())
		//{
		//	maps.insert({ trim(key),trim(value) });//去除字符串多余的空格（包含 \n\r\t）
		//}
		//else
		{
			maps[key] = value;
		}
	}
};

