#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H
//#include "stdafx.h"
#include "Condition.h"
#include "Attribute.h"
#include "RecordManager.h"
#include "BufferManager.h"
#include "Minisql.h"
#include <string>
#include <vector>
using namespace std;
class API;
class RecordManager{
public:
	RecordManager(){}
    BufferManager bm;
    API *api;
    
    //返回 记录数
    //输出 table的符合条件的记录
    //输入 table的名称，条件列表
    int recordAllShow(string tableName, vector<Condition>* conditionVector);
    
    int recordBlockShow(string tableName, vector<Condition>* conditionVector, blockNode* block);

    int recordInsert(string tableName, char* record, int recordSize);
    
    //返回 记录数
    //删除 一个表的条件的符合条件记录
    //输入 table的名称, 和一个条件的列表
	int recordDelete(string tableName, vector<Condition>* conditionVector){return 1;}

    int indexDrop(string indexName);
    int indexCreate(string indexName);

    int tableCreate(string tableName);
    int tableDrop(string tableName);
    
private:
    bool recordConditionFit(char* recordBegin,int recordSize, vector<Attribute>* attributeVector,vector<Condition>* conditionVector);
    void recordPrint(char* recordBegin, int recordSize, vector<Attribute>* attributeVector);
    bool contentConditionFit(char* content, int type, Condition* condition);
    void contentPrint(char * content, int type);
    string tableFileNameGet(string tableName);
    string indexFileNameGet(string indexName);
};
#endif