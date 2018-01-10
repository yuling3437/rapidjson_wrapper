//
// Created by root on 18-1-10.
//

#include <iostream>
#include "JsonWrapper.h"

#include "rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

JsonWrapper::JsonWrapper():val(nullptr), root(nullptr), buffer(nullptr){

}

JsonWrapper::~JsonWrapper() {
    //销毁的是root节点，需要清除内存
    if (val == root)
    {
        delete root;
    }

    if(buffer)
    {
        delete buffer;
    }
}

JsonWrapper &JsonWrapper::operator=(JsonWrapper &rhs) {

    if(!root)
    {
        //root为空，视为纯赋值
        val = rhs.val;
        root = rhs.root;
    }
    else
    {
        //root不为空, 则只移动数据到左值
        //注意： 移动后rhs就会变成空json串,这是由于rappidjson追求效率的原因。
        *val = *rhs.val;
    }

    return *this;
}

JsonWrapper &JsonWrapper::operator=(JsonWrapper *rhs)
{
    if(!root)
    {
        //root为空，视为纯赋值
        val = rhs->val;
        root = rhs->root;
    }
    else
    {
        //深拷贝, 这里rhs的值不变
        val->CopyFrom(*rhs->val, root->GetAllocator());
    }

    return *this;
}


JsonWrapper &JsonWrapper::operator=(int value) {
    if(val)
        val->SetInt(value);
    return *this;
}

JsonWrapper &JsonWrapper::operator=(int64_t value) {
    if(val)
        val->SetInt64(value);
    return *this;
}

JsonWrapper &JsonWrapper::operator=(const char *value) {
    if(val)
        val->SetString(StringRef(value));
    return *this;
}

JsonWrapper JsonWrapper::operator[](int index)  {
    if(!root)
    {
        //初始化root为数组类型
        root = new Document(kArrayType);
        val = root;
    }

    if(val->IsNull())
    {
        val->SetArray();
    }

    JsonWrapper ret;
    ret.root = root;

    if(val && val->IsArray())
    {
        if(index < 0 || val->Size() <= index)
        {
            //添加一个空数组元素
            index = val->Size();
            val->PushBack(Value(), root->GetAllocator());
        }

        ret.val = &(*val)[index];
        return ret;
    }
    else
    {
        cerr << "not array, can not use int index" << endl;
        return ret;
    }
}

JsonWrapper JsonWrapper::operator[](const char *index)  {
    if(!root)
    {
        //初始化root为对象类型
        root = new Document(kObjectType);
        val = root;
    }

    if(val->IsNull())
    {
        val->SetObject();
    }

    JsonWrapper ret;
    ret.root = root;

    if(val && val->IsObject())
    {
        if(!val->HasMember(index))
        {
            //添加一个空对象
            val->AddMember(StringRef(index), Value(),root->GetAllocator());
        }

        ret.val = &(*val)[index];
        return ret;
    }
    else
    {
        cerr << "not object, can not use char* index" << endl;
        return ret;
    }
}

int JsonWrapper::GetInt() {
    if(val && val->IsInt())
        return val->GetInt();
    return 0;
}

const char *JsonWrapper::GetString() {
    if(val && val->IsString())
        return val->GetString();
    return ""; // ""比nullptr要安全, cout 遇到nullptr会中断显示
}

int64_t JsonWrapper::GetInt64() {
    if(val && val->IsInt64())
        return val->GetInt64();
    return 0;
}

double JsonWrapper::GetDouble() {
    if(val && val->IsDouble())
        return val->GetDouble();
    return 0;
}

bool JsonWrapper::Prase(const char *str) {
    root = new Document;
    root->Parse(str);
    if(!root->HasParseError())
    {
        val = root;
        return true;
    }
    return false;
}

const char *JsonWrapper::ToString() {
    if(!val)
        return "";

    if(!buffer)
        buffer = new StringBuffer();
    buffer->Clear();
    Writer<StringBuffer> writer(*buffer);
    val->Accept(writer);
    return buffer->GetString();
}
