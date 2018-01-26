//
// Created by root on 18-1-10.
//
/*
samples:

// 1： array
JsonWrapper a;
a[1] = 1;
a[-1] = 2;
a["a"] = 1; //err

std::cout<<"a: "<<a.ToString()<<endl;

// 2:  object
JsonWrapper b;
b["a"] = 1;
b["b"] = 2;
b[1] = 3;  //err

std::cout<<"b: "<<b.ToString()<<endl;

// 3: default copy constructor and shallow copy
JsonWrapper c(b);       // or  JsonWrapper c = b;

std::cout<<"c: "<<c.ToString()<< "  c.root: "<<c.GetObject()<<"  b.root: "<<b.GetObject()<<endl;

JsonWrapper d(b["a"]);  // note:  d.root = b.root

std::cout<<"d.root: "<<d.GetObject()<<"  b.root: "<<b.GetObject()<<endl;

JsonWrapper e;
e = b["a"];

std::cout<<"e: "<<e.ToString()<<"  e.root: "<<e.GetObject()<<"  b.root: "<<b.GetObject()<<endl;

// 4: deep copy
JsonWrapper f(&b);      // constructor with pointer
std::cout<<"f: "<<e.ToString()<<"  f.root: "<<f.GetObject()<<"  b.root: "<<b.GetObject()<<endl;

JsonWrapper g(nullptr); // constructor to create new json object
g = b["a"];             // deep copy
std::cout<<"g: "<<e.ToString()<<"  g.root: "<<g.GetObject()<<"  b.root: "<<b.GetObject()<<endl;

// 5: move copy
JsonWrapper h;
h = &a;                 // a will be null

std::cout<<"h: "<<h.ToString()<<"  a: "<<a.ToString()<<endl;

JsonWrapper i(h[1]);    //i.root = h.root

JsonWrapper j;
j = &i;                 //move copy

i = 3;

std::cout<<"h: "<<h.ToString()<<"  i: "<<i.ToString()<<"  j: "<<j.ToString()<<endl;
std::cout<<"h.root: "<<h.GetObject()<<"  i.root: "<<i.GetObject()<<"  j.root: "<<j.GetObject()<<endl;

 */

#ifndef IP_BASE_JSONWRAPPER_H
#define IP_BASE_JSONWRAPPER_H

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include <memory>

typedef std::shared_ptr<rapidjson::Document> SDocument;

class JsonWrapper
{
public:
    JsonWrapper();

    ~JsonWrapper();

    //仅复制指针，不会创建新对象
    JsonWrapper(const JsonWrapper&);

    //这个形式表示会完全拷贝，并创建新的对象 也可以利用  JsonWrapper c(nullptr);  来强制创建新对象
    JsonWrapper(JsonWrapper * rhs);

    //如果左值有json对象，则深拷贝； 否则只拷贝指针
    JsonWrapper &operator = (const JsonWrapper & rhs);

    //移动赋值, 会清空rhs的值
    JsonWrapper &operator = (JsonWrapper * rhs);

    //赋值为int
    JsonWrapper &operator = ( int value);

    //赋值为int64
    JsonWrapper &operator = ( int64_t value);

    //赋值为uint
    JsonWrapper &operator = ( uint32_t value);

    //赋值为uint64
    JsonWrapper &operator = ( uint64_t value);

    //赋值为bool
    JsonWrapper &operator = ( bool value);

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

    uint32_t GetUInt();
    uint64_t GetUInt64();

    bool GetBool();

    //对象是否含有属性
    bool HasMember(const char* index);

    bool RemoveMember(const char* index);

    bool Empty();

    //数组的长度
    size_t Size();

    //解析,会创建新的json对象
    bool Parse(const char *str);
    //转换成json字符串
    const char* ToString();

    rapidjson::Document* GetObject();

private:
    void _CreateDocument();

private:
    rapidjson::Value* val;
    SDocument         root;
    rapidjson::StringBuffer *buffer;
};



#endif //IP_BASE_JSONWRAPPER_H

