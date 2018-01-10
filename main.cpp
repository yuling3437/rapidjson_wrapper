//
// Created by root on 18-1-8.
//

#include <stdio.h>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include <iostream>
#include <Config.h>
#include "JsonWrapper.h"

using namespace std;
using namespace rapidjson;
Config* g_main_config;

void print_json(Value &v)
{
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    v.Accept(writer);
    printf("%s\n", buffer.GetString());
}

int main()
{
    JsonWrapper w, w1, w2;
    w.Prase("[1]");
//    cout<<w[0].GetInt()<<endl;
    w[1] = "2";
    w["a"] = 1;
    cout<<"w:"<<w.ToString()<<endl;

    w1["a"] = 1;
    w1["b"] = 2;

    w1["c"] = w;

    cout<<"w:"<<w.ToString()<<endl;

    cout<<"w1:"<<w1.ToString()<<endl;
//
//
//    Document doc(kArrayType);
//
//    doc.PushBack(Value(), doc.GetAllocator());
//    doc[0].SetInt(2);
//
////    cout<<v[1].IsInt()<<endl;
//
//    print_json(doc);

    return 0;
}
