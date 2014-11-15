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
//    clock_t start = 0, finish;
//
//    cout<<"*******************Welcome to use our MiniSQL**********************"<<endl;
//    cout<<"******************* Author: Deng & Xu & Woo **********************"<<endl;
//    int fileRead = 0;
//    //string fileName ="";
//    ifstream file;
//    Interpreter in;
//    string s;
//    while(1)
//    {
//        if(fileRead)
//        {
//
//            file.open(in.fileName.c_str());
//            if(!file.is_open())
//            {
//                cout<<"Fail to open "<<in.fileName<<endl;
//                fileRead = 0;
//                continue;
//            }
//            while(getline(file,s,';'))
//            {
//                in.interpreter(s);
//            }
//            fileRead = 0;
//            finish = clock();
//            double duration = (double)(finish - start) / CLOCKS_PER_SEC;
//            duration *= 1000;
//            printf( "%2.1f seconds\n", duration );
//        }
//        else
//        {
//
//            cout<<"minisql>>";
//            getline(cin,s,';');
//            start = clock();
//            long long haha =10000000;
//            while(haha>0)
//                haha--;
//            if(in.interpreter(s)==2)
//            {
//                fileRead = 1;
//            }
//            else{
//                finish = clock();
//                double duration = (double)(finish - start) / CLOCKS_PER_SEC;
//                duration *= 1000;
//                printf( "The duration is %2.1f milliseconds\n", duration );
//            }
//        }
//
//    }
    
    init();
    
    API api;
    CatalogManager cm;
    RecordManager rm;
    IndexManager im;
    
    api.rm = &rm;
    api.cm = &cm;
    api.im = &im;
    rm.api = &api;

    
//    vector<Attribute> attributeVector;
//    Attribute a1("nyle", Attribute::TYPE_INT, false);
//    attributeVector.insert(attributeVector.end(), a1);
//    
//    Attribute a2("nyle2", Attribute::TYPE_FLOAT, true);
//    attributeVector.insert(attributeVector.end(), a2);
//    
//    Attribute a3("nyle3", Attribute::TYPE_FLOAT, true);
//    attributeVector.insert(attributeVector.end(), a3);
////
//    api.tableCreate("nyle", &attributeVector, "", 0);
    
//      api.indexCreate("aaaa", "nyle", "nyle2");
//      im.createIndex("/Users/dengyonghui/tmp/INDEX_FILE_cccc", -1);
//    im.insertIndex("/Users/dengyonghui/tmp/INDEX_FILE_cccc", "1.11", 2, -1);
//    api.tableDrop("nyle");
//    api.indexDrop("cccc");
//    vector<string> a;
//    cm.indexNameListGet("nyle", &a);
//    for (int i = 0; i < a.size(); i++)
//    {
//        cout << a[i];
//    }
    
//    cout << cm.getIndexType("cccc");
    
//    vector<string> content;
//    content.insert(content.end(), "11");
//    content.insert(content.end(), "122.2");
//    content.insert(content.end(), "22.223");
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
    
    vector<Condition> conditions;
    Condition c("nyle3", "22.223", Condition::OPERATOR_EQUAL);
    conditions.insert(conditions.begin(), c);
    
    
    
    api.recordShow("nyle", NULL);

    
//    rm.recordAllShow("nyle", NULL);
    

    return 1;
    
}

