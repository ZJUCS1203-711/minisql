#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include <string>
#include <vector>
#include "Attribute.h"
#include "BufferManager.h"
#include "IndexInfo.h"
using namespace std;
class CatalogManager {
public:
    BufferManager bm;
    CatalogManager();
    virtual ~CatalogManager();
    int addIndex(string indexName,string tableName,string attributeName,int type);//add index info
    int revokeIndexOnAttribute(string tableName,string AttributeName,string indexName);//as what it says
    int findTable(string tableName);//confirt the existence for a table
    int findIndex(string indexName);//confirm the existence for an index
    int dropTable(string tableName);//drop table info
    int dropIndex(string index);// drop index info
    int deleteValue(string tableName, int deleteNum);// delete the number of record
    int insertRecord(string tableName, int recordNum);  // increment the number of record
    int getRecordNum(string tableName);//get the current number of records in that table 
    int indexNameListGet(string tableName, vector<string>* indexNameVector);// all index for one table
    int getAllIndex(vector<IndexInfo> * indexs);//all index no matter on which table
    int setIndexOnAttribute(string tableName,string AttributeName,string indexName);//as what it says
    int addTable(string tableName, vector<Attribute>* attributeVector, string primaryKeyName ,int primaryKeyLocation );
    int getIndexType(string indexName);//a type of index
    int attributeGet(string tableName, vector<Attribute>* attributeVector);//the info of an attribute in a table
    int calcuteLenth(string tableName);//length of per record
    int calcuteLenth2(int type);// an enhanced edtion
    void recordStringGet(string tableName, vector<string>* recordContent, char* recordResult);//as what it says
};




#endif