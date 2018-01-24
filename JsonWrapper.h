//
// Created by root on 18-1-10.
//

#ifndef IP_BASE_JSONWRAPPER_H
#define IP_BASE_JSONWRAPPER_H

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"


class JsonWrapper
{
private:
    //为了效率，禁用默认拷贝函数  防止成为函数返回值等操作
    JsonWrapper(const JsonWrapper&) {}

public:
    JsonWrapper();

    ~JsonWrapper();

    //移动赋值  推荐使用
    JsonWrapper &operator = (JsonWrapper & rhs);
    //深拷贝
    JsonWrapper &operator = (JsonWrapper * rhs);

    //赋值为int
    JsonWrapper &operator = ( int value);

    //赋值为int64
    JsonWrapper &operator = ( int64_t value);

    //赋值为字符串
    JsonWrapper &operator = ( const char* value);

    //读取数组
    JsonWrapper operator[] (int index);

    //读取对象
    JsonWrapper operator[] (const char* index);

    //读取数据
    int GetInt();
    const char* GetString();
    uint32_t GetStringLength();
    int64_t GetInt64();
    double GetDouble();

    //对象是否含有属性
    bool HasMember(const char* index);

    //数组的长度
    size_t Size();

    //解析
    bool Parse(const char *str);
    //转换成json字符串
    const char* ToString();

    rapidjson::Document * GetObject();

private:
    rapidjson::Value* val;
    rapidjson::Document *root;
    rapidjson::StringBuffer *buffer;
};



#endif //IP_BASE_JSONWRAPPER_H

