//
// Created by root on 18-1-8.
//

#include <iostream>
#include "JsonWrapper.h"

using namespace std;

int main()
{
    JsonWrapper w, w1, w2;
    w.Parse("[1]");
    cout<<w[0].GetInt()<<endl;

    w[1] = "2";
    w["a"] = 1; //err
    cout<<"w:"<<w.ToString()<<endl;

    w1["a"] = 1;
    w1["b"] = 2;

    w1["c"] = &w; //deep copy
    w1["d"] = w;  //move

    cout<<"w:"<<w.ToString()<<endl;

    cout<<"w1:"<<w1.ToString()<<endl;

    w[1] = w1;
    cout<<"w:"<<w.ToString()<<endl;

    return 0;
}
