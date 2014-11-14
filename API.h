#ifndef API_H
#define API_H

#include "Attribute.h"
#include "Condition.h"
#include "Minisql.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class IndexManager{
public:
    void indexCreate(string indexName, string tableName, string attributeName){return;}
    void dropIndex(string indexName){return;}
    void indexValueInsert(string indexName, string value, int blockOffset){return;}
    void indexValueGet(string indexName,string value, blockNode* block){return ;}
};

class CatalogManager;
class RecordManager;
class API{
public:
    RecordManager *rm;
    CatalogManager *cm;
	API(){}
	~API(){}
    
    
    void tableDrop(string tableName);
    void tableCreate(string tableName, vector<Attribute>* attributeVector, string primaryKeyName,int primaryKeyLocation);
    
    void indexDrop(string indexName);
	void indexCreate(string indexName, string tableName, string attributeName);
  
    void recordShow(string tableName);
	void recordShow(string tableName, vector<Condition>* conditionVector);

	void recordInsert(string tableName,vector<string>* recordContent);

	void recordDelete(string tableName);
	void recordDelete(string tableName, vector<Condition>* conditionVector);

	int recordNumGet(string tableName);
	int recordSizeGet(string tableName);

	int typeSizeGet(int type);
    
    
    int attributeGet(string tableName, vector<Attribute>* attributeVector);

    void indexValueInsert(string indexName, string value, int blockOffset);
    
    void indexInsert(string indexName, char* value, int type, int blockOffset);
    void recordIndexDelete(char* recordBegin,int recordSize, vector<Attribute>* attributeVector, int blockOffset);
    void recordIndexInsert(char* recordBegin,int recordSize, vector<Attribute>* attributeVector, int blockOffset);
    
private:
    int tableExist(string tableName);
    int indexNameListGet(string tableName, vector<string>* indexNameVector);
    string primaryIndexNameGet(string tableName);
    void tableAttributePrint(vector<Attribute>* attributeVector);
};

struct int_t{
	int value;
};

struct float_t{
	float value;
};
#endif