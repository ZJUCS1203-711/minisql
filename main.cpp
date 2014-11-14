//
//  main.cpp
//  minisql
//
//  Created by 邓永辉 on 14/11/3.
//  Copyright (c) 2014年 邓永辉. All rights reserved.
//
<<<<<<< HEAD
//
#include <iostream>
#include "API.h"
#include "RecordManager.h"
=======

#include <iostream>
#include "API.h"
>>>>>>> 1f361341e68562bf8f4529691f1ac6c493808195
using namespace std;

int main()
{
<<<<<<< HEAD
    API api;
    RecordManager rm;
    api.rm = &rm;
    rm.api = &api;
    
    
    rm.tableDrop("nyle");
    rm.tableCreate("nyle");

    int recordSize = sizeof(int) + sizeof(float) + sizeof(char[7]);
    
    //创建一个blockNode
    char file[8192];
    memset(file, 0, 8192);
    char * p = file;
    
    int intTmp = 29;
    char *tmp = (char*) &intTmp;
    memcpy(p, tmp, sizeof(int));
    p += sizeof(int);
    
    float a = 200.34;
    tmp =  (char*)&a;
    memcpy(p, tmp, sizeof(float));
    p += sizeof(float);
    
    char charTmp[7] = "dhar";
    memcpy(p , charTmp, sizeof(char[7]));
    p += sizeof(char[7]);
    
    for(int i = 0; i < 10000; i++)
        rm.recordInsert("nyle", file, recordSize);

    
//    创建条件列表 (nyle1 < 200 && nyle2 <> 200 && nyle3 == "dhar")
//    vector<Condition> conditionVector;
//    
//    Condition b;
//    b.attributeName = "nyle1";
//    b.value = "200";
//    b.operate = Condition::OPERATOR_LESS;
//    conditionVector.insert(conditionVector.end(), b);
//    
//    Condition b2;
//    b2.attributeName = "nyle2";
//    b2.value = "200";
//    b2.operate = Condition::OPERATOR_NOT_EQUAL;
//    conditionVector.insert(conditionVector.end(), b2);
//    
//    Condition b3;
//    b3.attributeName = "nyle3";
//    b3.value = "dhar";
//    b3.operate = Condition::OPERATOR_EQUAL;
//    conditionVector.insert(conditionVector.end(), b3);

    int num = rm.recordAllShow("nyle", NULL);
    cout << "print record count: " << num << endl;

    
    return 0;
}
=======
    cout << "Hello, World!\n";
    return 0;
    API api;
    vector<Condition> conditionVector;
    api.recordShow("aa", conditionVector);
    string a = "";
    a = "sdf";
    cout << a;
    
}
>>>>>>> 1f361341e68562bf8f4529691f1ac6c493808195
