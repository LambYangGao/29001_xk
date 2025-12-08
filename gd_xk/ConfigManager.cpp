#include "ConfigManager.h"
//-------------辅助函数-------------
std::string ConfigManager::string_replace(std::string source, std::string find, std::string replace)
{
	std::string::size_type pos = 0;
	std::string::size_type a = find.size();
	std::string::size_type b = replace.size();
	while ((pos = source.find(find, pos)) != std::string::npos)
	{
		//source.replace(pos, a, replace);
		source.erase(pos, a);
		source.insert(pos, replace);
		pos += b;
	}
	return source;
}
////用于支持配置文件中的字符串转数字
//template <class T>
//void ConfigManager::convertFromString(T& value, const std::string& s) {
//	std::stringstream ss(s);
//	ss.precision(s.length());
//	ss >> value;
//}

//用于去除字符串多余的空格
std::string ConfigManager::trim(std::string text)
{
	if (!text.empty())
	{
		text.erase(0, text.find_first_not_of(" \n\r\t"));//去除字符串头部的空格
		text.erase(text.find_last_not_of(" \n\r\t") + 1);//去除字符串尾部的空格
	}
	return text;
}
//用于支持将多行的配置文件分割开来
void ConfigManager::Stringsplit(std::string str, const char split, std::vector<std::string>& strList)
{
	std::istringstream iss(str);	// 输入流
	std::string token;			// 接收缓冲区
	while (getline(iss, token, split))	// 以split为分隔符
	{
		strList.push_back(token);
	}
}
//用于支持将 key=value 格式的配置文件分割开来（只分割一次）
void ConfigManager::Stringsplit2(std::string str, const char split, std::vector<std::string>& strList)
{
	//string str = "key=value1 value2 #notes";
	size_t pos = str.find(split); // 3
	if (pos > 0 && pos < str.length()) {//用于分割key=value
		std::string p = str.substr(0, pos); // 123
		std::string q = str.substr(pos + 1); // 456,789
		strList.push_back(p);
		strList.push_back(q);
	}
	else {//用于不带# 注释时的分割
		strList.push_back(str);
	}
}

std::string ConfigManager::CharToStr(char* conttentChar)
{
	std::string tempStr = "";
	for (int i = 0; conttentChar[i]!='\0'; i++)
	{
		tempStr += conttentChar[i];
	}
	return tempStr;
}

bool ConfigManager::rewrite(std::string& filename, std::vector<std::string>& lineDatas)
{
	std::fstream file(filename, std::ios::out);

	if (!file.is_open())
	{
		std::cerr << filename << " open failed." << std::endl;
		return false;
	}
	for (const auto& str : lineDatas)
	{
		file << str << std::endl;
	}

	file.close();

	//std::ofstream os;     //创建一个文件输出流对象
	//        // os.open("../books.txt", std::fstream::out|std::fstream::app);//将对象与文件关联, app就是每次在文件后面继续添加内容
	//os.open(filename, std::fstream::out);//将对象与文件关联
	//for (const auto& str : lineDatas)
	//{
	//    os << str << endl;
	//}
	//os.close();
	return true;
}

bool ConfigManager::modifyContentInfile(std::string filename, std::string key, std::string content)
{
	if (!filename.empty())
	{
		std::fstream file(filename, std::ios::in);

		if (!file.is_open())
		{
			std::cerr << filename << " open failed." << std::endl;
			return false;
		}

		char buffer[1024]{ 0 };
		std::string ikey = "#";

		std::vector<std::string> lineDatas;
		while (!file.eof())
		{
			file.getline(buffer, 1024);
			if (CharToStr(buffer).find(key) != std::string::npos && CharToStr(buffer).find(ikey) == std::string::npos)
			{
				//char szLine[1024] = { 0 };
				//strcpy(szLine, content.c_str());
				lineDatas.push_back(std::move(content));

				continue;
			}

			lineDatas.push_back(buffer);
		}
		///< 回写
		if (rewrite(filename, lineDatas))
		{
			std::cerr << filename << " rewrite success." << std::endl;
		}
		else
		{
			std::cerr << filename << " rewrite  failed." << std::endl;
		}

		file.close();
	}
	return true;
}


