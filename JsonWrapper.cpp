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

JsonWrapper::JsonWrapper(const JsonWrapper &r):buffer(nullptr) {
    //root初始为空
    root = r.root;
    val = r.val;
}

//纯深拷贝
JsonWrapper::JsonWrapper(JsonWrapper *rhs): buffer(nullptr) {
    _CreateDocument();
    if(rhs)
        val->CopyFrom(*rhs->val, root->GetAllocator());
}

JsonWrapper::~JsonWrapper() {
    if(buffer)
    {
        delete buffer;
    }
}

JsonWrapper &JsonWrapper::operator=(const JsonWrapper &r) {
    if(!root)
    {
        //root 为空，则可以只需要复制地址
        root = r.root;
        val = r.val;
    }
    else   //本身有值，则只能是拷贝
        val->CopyFrom(*r.val, root->GetAllocator());
    return *this;
}

JsonWrapper &JsonWrapper::operator=(JsonWrapper *rhs)
{
    //规范操作，这里不能只拷贝root和val的指针
    if(!root)
    {
        _CreateDocument();
    }

    //注意： 移动后rhs就会变成空json串,这是由于rappidjson追求效率的原因。
    if(rhs)
        *val = *rhs->val;

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


JsonWrapper &JsonWrapper::operator=(uint32_t value) {
    if(val)
        val->SetUint(value);
    return *this;
}

JsonWrapper &JsonWrapper::operator=(uint64_t value) {
    if(val)
        val->SetUint64(value);
    return *this;
}

JsonWrapper &JsonWrapper::operator=(bool value) {
    if(val)
        val->SetBool(value);
    return *this;
}

JsonWrapper &JsonWrapper::operator=(const char *value) {
    if(val)
        val->SetString(value, strlen(value), root->GetAllocator());
    return *this;
}

JsonWrapper JsonWrapper::operator[](int index)  {
    if(!root)
    {
        //初始化root为数组类型
        _CreateDocument();
    }

    JsonWrapper ret;
    ret.root = root;

    if(val->IsNull())
    {
        val->SetArray();
    }

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
        _CreateDocument();
    }

    JsonWrapper ret;
    ret.root = root;

    if(val->IsNull())
    {
        val->SetObject();
    }

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

uint32_t JsonWrapper::GetStringLength() {
    if(val && val->IsString())
        return val->GetStringLength();
    return 0;
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

uint32_t JsonWrapper::GetUInt() {
    if(val && val->IsUint())
        return val->GetUint();
    return 0;
}

uint64_t JsonWrapper::GetUInt64() {
    if(val && val->IsUint64())
        return val->GetUint64();
    return 0;
}

bool JsonWrapper::GetBool() {
    if(val && val->IsBool())
        return val->GetBool();
    return false;
}


bool JsonWrapper::Parse(const char *str) {
    _CreateDocument();
    root->Parse(str);
    if(!root->HasParseError())
    {
        return true;
    }
    return false;
}

const char *JsonWrapper::ToString() {
    if(!val)
        return "";

    if(!buffer)
        buffer = new StringBuffer();
    else
        buffer->Clear();
    Writer<StringBuffer> writer(*buffer);
    val->Accept(writer);
    return buffer->GetString();
}

bool JsonWrapper::HasMember(const char *index) {
    if(!val)
        return false;

    return val->HasMember(index);
}

bool JsonWrapper::RemoveMember(const char *index) {
    if(!val)
        return false;
    return val->RemoveMember(index);
}

bool JsonWrapper::Empty() {
    if(!root)
        return true;

    if(val->IsNull())
        return true;

    if(val->IsArray())
        return val->Empty();

    //其余情况视为有值
    return false;
}

size_t JsonWrapper::Size() {
    if(!val)
        return 0;

    if(val->IsNull())
    {
        val->SetArray();
    }

    return val->Size();
}

Document* JsonWrapper::GetObject() {
    if(!root)
    {
        _CreateDocument();
    }

    return (Document*)root.get();
}

void JsonWrapper::_CreateDocument() {
    root = SDocument(new Document);
    val = (Value*)root.get();
}

