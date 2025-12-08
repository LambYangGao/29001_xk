#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "readConfig.h"
#define bufSize 1024
#define MaxKeyLength 32

//enum bool
//{
//    false,
//    true
//};

CReadConfig::CReadConfig(void)
{

}
CReadConfig::~CReadConfig(void)
{

}

/* *
 * @param buf
 * @desc 删除buf中的制表符以及注释
 * */
char* CReadConfig::trimSp(char* buf)
{
    char tbuf[bufSize] = { '\0' };
    if (buf == NULL || strlen(buf) == 0)
    {
        return NULL;
    }
    int len = strlen(buf);
    int i = 0, j = 0;
    while (i < len)
    {
        //此处注释使用 //
        //若注释使用 # 则使用以下代码代替
        if (buf[i] == '#')
        {
            break;
        }


        if (iscntrl(buf[i]) == 0 && isspace(buf[i]) == 0)
        {
            tbuf[j] = buf[i];
            j++;
        }

        i++;
    }

    //将结果复制到buf
    memset(buf, '\0', len);
    strncpy(buf, tbuf, strlen(tbuf));
    return buf;
}

/***
 * @param buf
 * @desc 获取 = 在字符串中的位置
*/
int CReadConfig::getPos(char* buf)
{
    if (buf == NULL || strlen(buf) == 0)
    {
        return -1;
    }
    int len = strlen(buf);
    int i = 0;
    while (i < len)
    {
        if (buf[i] == '=')
        {
            break;
        }
        i++;
    }
    return i++;
}

/* *
 * @param file
 * @param AppName
 * @param KeyName
 * @param KeyVal
 * @desc  从文件‘file’中的[AppName]中读取属性KeyName的值KeyVal
 * */
int CReadConfig::ReadConf(char* file, char* AppName, char* KeyName, char* KeyVal)
{
    char buf[bufSize] = { '\0' };
    int find_app_name = false;
    int vallen = 0;

    if (file == NULL || strlen(file) == 0) //文件名（路径）检查
    {
        return -1;
    }
    FILE* fp = fopen(file, "r"); //打开文件

    if (fp == NULL) //文件句柄检查
    {
        return -1;
    }

    while (fgets(buf, bufSize, fp) != NULL)
    {
        char* tbuf = trimSp(buf);
        int pos = getPos(tbuf);
        int len = strlen(tbuf);

        //printf("string:%s\n", tbuf);

        //查找到 [NAME]
        if (len > 0 && len == pos && tbuf[0] == '[' && tbuf[len - 1] == ']')
        {
            //存放NAME
            char* t_appname = (char*)malloc(len - 1);
            memset(t_appname, '\0', len - 1);
            strncpy(t_appname, tbuf + 1, len - 2);

            //查找到AppName
            if (strncmp(t_appname, AppName, strlen(t_appname)) == 0)
            {
                find_app_name = true;
            }
            else
            {
                find_app_name = false;
            }

            //注意释放空间，防止内存泄露
            free(t_appname);
        }
        else
        {
            //属性名 与 属性值
            if (len > 0 && pos != len && find_app_name)
            {
                char* val = tbuf + pos + 1;//属性值
                tbuf[pos] = '\0';//将=替换为\0  用以分割属性名 与 属性值
                char* key = tbuf;//属性名

                //查找到属性名
                if (strncmp(key, KeyName, strlen(key)) == 0)
                {
                    //将值复制到 KeyVal
                    strncpy(KeyVal, val, strlen(val));
                    vallen = strlen(val);
                    break;
                }
            }
        }
    }
    //关闭文件句柄
    if (fp != NULL)
    {
        fclose(fp);
    }

    return vallen;
}

/* *
 * @param file
 * @param AppName
 * @param KeyName
 * @param KeyVal
 * @desc  将文件‘file’中的[AppName]中对应属性KeyName的值改为KeyVal
 * */
int CReadConfig::WriteConf(char* file, char* AppName, char* KeyName, char* KeyVal)
{
    char buf[bufSize] = { '\0' };
    int find_app_name = false;

    if (file == NULL || strlen(file) == 0) //文件名（路径）检查
    {
        return -1;
    }
    FILE* fp = fopen(file, "r+"); //打开文件

    if (fp == NULL) //文件句柄检查
    {
        return -1;
    }

    while (fgets(buf, bufSize, fp) != NULL)
    {
        char* tbuf = trimSp(buf);
        int pos = getPos(tbuf);
        int len = strlen(tbuf);

        //printf("string:%s\n", tbuf);

        //查找到 [NAME]
        if (len > 0 && len == pos && tbuf[0] == '[' && tbuf[len - 1] == ']')
        {
            //存放NAME
            char* t_appname = (char*)malloc(len - 1);
            memset(t_appname, '\0', len - 1);
            strncpy(t_appname, tbuf + 1, len - 2);

            //查找到AppName
            if (strncmp(t_appname, AppName, strlen(t_appname)) == 0)
            {
                find_app_name = true;
            }
            else
            {
                find_app_name = false;
            }

            //注意释放空间，防止内存泄露
            free(t_appname);
        }
        else
        {
            //属性名 与 属性值
            if (len > 0 && pos != len && find_app_name)
            {
                char* val = tbuf + pos + 1;//属性值
                tbuf[pos] = '\0';//将=替换为\0  用以分割属性名 与 属性值
                char* key = tbuf;//属性名
                int ll = len - pos + 1;
                //查找到属性名
                if (strncmp(key, KeyName, strlen(key)) == 0)
                {
                    //将KeyVal复制到 属性值位置
                    int cc = strlen(KeyVal);
                    fseek(fp, -ll, SEEK_CUR);
                    fwrite(KeyVal, cc, 1, fp);
                    int a = strlen(val) - strlen(KeyVal);
                    if (a > 0)
                    {
                        char b[100] = { '\0' };
                        fwrite(b, a, 1, fp);
                    }
                    break;
                }
            }
        }
    }
    //关闭文件句柄
    if (fp != NULL)
    {
        fclose(fp);
    }

    return 1;
}