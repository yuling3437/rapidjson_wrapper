# rapidjson_wrapper

1. 修改CMakeList.txt中的包含目录到rapidjson

2. cmake 

3. make

简化了原生rapidjson生成json串的复杂书写过程
支持了几种基本操作，获取值的操作可以自己后期增加


JsonWrapper w, w1, w2;

w.Prase("[1]");

w[1] = "2";

w["a"] = 1; //err

cout<<"w:"<<w.ToString()<<endl; //输出 w:[1,"2"]

w1["a"] = 1;

w1["b"] = 2;

w1["c"] = &w; //deep copy   w 不变

w1["d"] = w;  //move     w 变成 null

cout<<"w:"<<w.ToString()<<endl; //输出 w:null

cout<<"w1:"<<w1.ToString()<<endl; //输出 w1:{"a":1,"b":2,"c":[1,"2"],"d":[1,"2"]}

w[1] = w1;

cout<<"w:"<<w.ToString()<<endl; //输出 w:[{"a":1,"b":2,"c":[1,"2"],"d":[1,"2"]}]

