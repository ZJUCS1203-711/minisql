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
    
    clock_t start = 0, finish;

    cout<<"*******************Welcome to use our MiniSQL**********************"<<endl;
    cout<<"******************* Author: Deng & Xu & Woo **********************"<<endl;
    int fileRead = 0;
    //string fileName ="";
    ifstream file;
    Interpreter in;
    in.ap = &api;
    string s;
    int status = 0;
    while(1)
    {
        if(fileRead)
        {

            file.open(in.fileName.c_str());
            if(!file.is_open())
            {
                cout<<"Fail to open "<<in.fileName<<endl;
                fileRead = 0;
                continue;
            }
            while(getline(file,s,';'))
            {
                in.interpreter(s);
            }
            file.close();
            fileRead = 0;
            finish = clock();
            double duration = (double)(finish - start) / CLOCKS_PER_SEC;
            duration *= 1000;
            printf( "%2.1f milliseconds\n", duration );
        }
        else
        {

            cout<<"minisql>>";
            getline(cin,s,';');
            start = clock();
            status =  in.interpreter(s);
            if(status==2)
            {
                fileRead = 1;
            }
            else if(status==587)
            {
                break;
            }
            else{
                finish = clock();
                double duration = (double)(finish - start) / CLOCKS_PER_SEC;
                duration *= 1000;
                printf( "The duration is %2.1f milliseconds\n", duration );
            }
        }

    }
    
    return 0;

    
    
    
//        api.tableDrop("nyle");
//
//    
//    vector<Attribute> attributeVector;
//    Attribute a1("v1", Attribute::TYPE_INT, false);
//    attributeVector.insert(attributeVector.end(), a1);
//    
//    Attribute a2("v2", Attribute::TYPE_FLOAT, false);
//    attributeVector.insert(attributeVector.end(), a2);
//
//    api.tableCreate("dd", &attributeVector, "", 0);
    
//    api.indexCreate("index1", "nyle", "nyle2");
//
//    vector<string> content;
//    content.insert(content.end(), "11");
//    content.insert(content.end(), "2.22");
//
//    api.recordInsert("dd", &content);
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
//    Condition c("nyle2", "2.3", Condition::OPERATOR_EQUAL);
//    conditions.insert(conditions.begin(), c);
////
////
//    api.recordDelete("nyle", &conditions);
//
//    
//    api.recordShow("nyle", NULL);
////
////    cout << "blockOffset : " << im.searchIndex(rm.indexFileNameGet("index1"), "444", Attribute::TYPE_FLOAT);
//    
//    return 1;
}

