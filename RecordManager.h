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
    
    int recordAllShow(string tableName, vector<Condition>* conditionVector);
    int recordBlockShow(string tableName, vector<Condition>* conditionVector, blockNode* block);

    int recordAllFind(string tableName, vector<Condition>* conditionVector);
    int recordBlockFind(string tableName, vector<Condition>* conditionVector, blockNode* block);
    
    int recordInsert(string tableName, char* record, int recordSize);
    
    int recordAllDelete(string tableName, vector<Condition>* conditionVector);
    int recordBlockDelete(string tableName,  vector<Condition>* conditionVector, blockNode* block);

    int indexDrop(string indexName);
    int indexCreate(string indexName);

    int tableCreate(string tableName);
    int tableDrop(string tableName);
    
    int indexRecordAllAlreadyInsert(string tableName,string indexName);
    int indexRecordBlockAlreadyInsert(string tableName,string indexName, blockNode* block);
    
    string tableFileNameGet(string tableName);
    string indexFileNameGet(string indexName);
private:
    bool recordConditionFit(char* recordBegin,int recordSize, vector<Attribute>* attributeVector,vector<Condition>* conditionVector);
    void recordPrint(char* recordBegin, int recordSize, vector<Attribute>* attributeVector);
    bool contentConditionFit(char* content, int type, Condition* condition);
    void contentPrint(char * content, int type);
};
#endif