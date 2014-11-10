//
//  main.cpp
//  minisql
//
//  Created by 邓永辉 on 14/11/3.
//  Copyright (c) 2014年 邓永辉. All rights reserved.
//

#include <iostream>
#include "API.h"
#include "RecordManager.h"
using namespace std;

int main()
{
    cout << "Hello, World!\n";
    cout << "hello nyle" << endl;
    
    API api;
    RecordManager rm;
    api.rm = &rm;
    rm.api = &api;
    
//    rm.tableDrop("nyle");
//    rm.tableCreate("nyle");

//    char file[8192];
//    char * p = file;
//    
//    int intTmp = 21;
//    char *tmp = (char*) &intTmp;
//    memcpy(p, tmp, sizeof(int));
//    p += sizeof(int);
//    
//    float a = 200;
//    tmp =  (char*)&a;
//    memcpy(p, tmp, sizeof(float));
//    p += sizeof(float);
//    
//    char charTmp[7] = "aaa";
//    memcpy(p , charTmp, sizeof(char[7]));
//    p += sizeof(char[7]);
//    
//    int recordSize = sizeof(int) + sizeof(float) + sizeof(char[7]);
//    
//    rm.recordInsert("nyle", file, recordSize);
    
// cout <<  rm.recordAllDelete("nyle", NULL);
    
    vector<Condition> conditionVector;
    Condition condtion;
    condtion.attributeName = "nyle1";
    condtion.operate = Condition::OPERATOR_LESS;
    condtion.value = "21";
    conditionVector.insert(conditionVector.end(), condtion);
    
    int num = rm.recordAllFind("nyle", &conditionVector);
    cout << num << "record print";
    
    return 0;
}
