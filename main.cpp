#include<iostream>
#include "Interpreter.h"
#include "CatalogManager.h"
#include "RecordManager.h"
#include "IndexManager.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API.h"



void init()
{
    FILE *fp;
    fp = fopen("Indexs", "r");
    if (fp == NULL)
    {
        fclose(fp);
        fopen("Indexs", "w+");
        return;
    }
    fclose(fp);
}

int main(int argc,char * argv[])
{
    init();
    
    API api;
    CatalogManager cm;
    RecordManager rm;
    
    
    api.rm = &rm;
    api.cm = &cm;
    IndexManager im(&api);
    
    api.im = &im;
    rm.api = &api;
    
//        
    
    
//        api.tableDrop("student");
//
//    
//    vector<Attribute> attributeVector;
//    Attribute a1("v1", Attribute::TYPE_INT, false);
//    attributeVector.insert(attributeVector.end(), a1);
//    
//    Attribute a2("v2", Attribute::TYPE_FLOAT, false);
//    attributeVector.insert(attributeVector.end(), a2);
//
//    api.tableCreate("nyle", &attributeVector, "", 0);
    
//    api.indexCreate("index1", "nyle", "nyle2");
//
//    vector<string> content;
//    content.insert(content.end(), "11");
//    content.insert(content.end(), "2.22");
//
//    api.recordInsert("nyle", &content);
//
    
//    char t[2000];
//    memset(t, 0, 2000);
//    cm.recordStringGet("nyle", &content, t);
//    cout << content[0] << " " << content[1] << " " << content[2] << endl;
//    
//    cout << *((int*)t) << " " << *((float*)(t + 4)) << " " << *((float*)(t + 8));
    
//    rm.recordInsert("nyle", t, 12);
//    
//    vector<Condition> conditions;
//    Condition c("sno", "10", Condition::OPERATOR_MORE_EQUAL);
//    conditions.insert(conditions.begin(), c);
//
//
//    api.recordDelete("student", &conditions);
//
//
    vector<string> name;
    name.insert(name.begin(), "nyle2");
    api.recordShow("nyle", &name);
////
////    cout << "blockOffset : " << im.searchIndex(rm.indexFileNameGet("index1"), "444", Attribute::TYPE_FLOAT);
//    
    return 0;
}

