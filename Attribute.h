//
//  Attribute.h
//  minisql
//
//  Created by 邓永辉 on 14/11/4.
//  Copyright (c) 2014年 邓永辉. All rights reserved.
//

#ifndef minisql_Attribute_h
#define minisql_Attribute_h

#include <string>
#include <iostream>
using namespace std;

class Attribute
{
public:
    string name;               //属性名称
    int type;                  //属性类别  (-1 为 float, 0 为 int, 其他正整数表示 char，数值为char的个数)
    bool ifUnique;             //属性是否唯一
    string index = "";         //索引名称 ,默认（不存在时）为""
    Attribute(string n, int t, bool i);
    
public:
    int static const TYPE_FLOAT = -1;
    int static const TYPE_INT = 0;
    string indexNameGet(){return index;}
    
    void print()
    {
        cout <<  "name: " << name << ";type: " << type << ";ifUnique: " << ifUnique << ";index: " << index << endl;
    }
};

#endif
