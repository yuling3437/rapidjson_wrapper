//
// Created by root on 18-1-10.
//

#ifndef IP_BASE_JSONWRAPPER_H
#define IP_BASE_JSONWRAPPER_H

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

class JsonWrapper
{
public:
    JsonWrapper();;

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
    int64_t GetInt64();
    double GetDouble();

    //解析
    bool Prase(const char* str);
    //转换成json字符串
    const char* ToString();

private:
    rapidjson::Value* val;
    rapidjson::Document *root;
    rapidjson::StringBuffer *buffer;
};



#endif //IP_BASE_JSONWRAPPER_H
