#ifndef API_H
#define API_H
#include "RecordManager.h"

#include "Attribute.h"
#include "Condition.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class IndexManager{
public:
    void indexCreate(string indexName, string tableName, string attributeName){return;}
    void dropIndex(string indexName){return;}
    void indexValueInsert(string indexName, string value){return;}
};
class CatalogManager
{
public:
    //--------------------api need to change
    int addIndex(string indexName,string tableName,string colName){return 1;}
    int findFile(string fileName){return  1;}
    int dropTable(string tableName){return 1;}
    int dropIndex(string index){return 1;}
    int deleteValue(string tableName){return 1;}
    int deleteValue(string tableName, int deleteNum){return 1;}
    int insertRecord(string tableName, int recordNum){return 1;}
    int getRecordNum(string tableName){return 2000;}
    
    
    
    //--------------我修改比较大的
    void addTable(string tableName, vector<Attribute>* attributeVector, string primaryKeyName = ""){}
    
    //使传进来的地址得到一个table的属性名称的vector
    //输出 是否得到成功
    //输入 table的名称，table的属性名称列表的地址
    int attributeNameGet(string tableName, vector<string>* attributeNameVector){return 1;}
    
    //使传进来的地址得到一个table的属性类型的vector
    //输出 是否得到成功
    //输入 table的名称，table的属性类型列表的地址
    int attributeTypeGet(string tableName, vector<string>* attributeTypeVector){return 1;}
    
    //使传进来的地址得到一个table的属性的vector
    //输出 是否得到成功
    //输入 table的名称，table的属性列表的地址
    int attributeGet(string tableName, vector<Attribute>* attributeVector){return 1;}
    
    int calcuteLenth(string tableName){return 1;} //得到一个table的记录的大小
    int calcuteLenth2(int type){return 1;}      //這理我的type改成了int类型，而不是一个String，type类型见attribute.h
    
    // 通过table名和recordContent得到这个table的record的字符传，写入传进的字符串
    void recordStringGet(string tableName, vector<string>* recordContent, char* recordResult){return ;}
};

class API{
public:
	RecordManager rm;
	API(){}
	~API(){}
    
    
    void tableDrop(string tableName);
    void tableCreate(string tableName, vector<Attribute>* attributeVector, string primaryKeyName = "no");
    
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
    
    int attributeNameGet(string tableName, vector<string>* attributeNameVector);
	int attributeTypeGet(string tableName, vector<string>* attributeTypeVector);
    int attributeGet(string tableName, vector<Attribute>* attributeVector);

    void indexValueInsert(string indexName, string value);
    
    //输出 二叉树的一个节点（待修改）
    //输入 索引名称,value
    int indexBlockGet(string indexName, string value);
    
private:
    int tableExist(string tableName);
};

struct int_t{
	int value;
};

struct float_t{
	float value;
};
#endif