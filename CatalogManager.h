#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include <string>
#include <vector>
using namespace std;
class CatalogManager
{
public:
    int addIndex(string indexName,string tableName,string attributeName);
    int findFile(string fileName);//?
    int dropTable(string tableName);
    int dropIndex(string index);
    int deleteValue(string tableName);
    int deleteValue(string tableName, int deleteNum);// delete the number of record
    int insertRecord(string tableName, int recordNum);  // increment the number of record
    int getRecordNum(string tableName);
    int indexNameListGet(string tableName, vector<string>* indexNameVector);

    void addTable(string tableName, vector<Attribute>* attributeVector, string primaryKeyName = ""); 
    //使传进来的地址得到一个table的属性名称的vector
    //输出 是否得到成功
    //输入 table的名称，table的属性名称列表的地址



    int attributeGet(string tableName, vector<Attribute>* attributeVector);  
    int calcuteLenth(string tableName); 
    int calcuteLenth2(int type); 
    void recordStringGet(string tableName, vector<string>* recordContent, char* recordResult);
};

#endif