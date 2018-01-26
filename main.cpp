//
// Created by root on 18-1-8.
//

#include <iostream>
#include "JsonWrapper.h"

using namespace std;

int main()
{
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

    return 0;
}
