//
//  API.cpp
//  minisql
//
//  Created by 邓永辉 on 14/11/5.
//  Copyright (c) 2014年 邓永辉. All rights reserved.
//

#include "API.h"

#define UNKNOWN_FILE 8
#define TABLE_FILE 9
#define INDEX_FILE 10

RecordManager rm;
CatalogManager cm;
IndexManager im;

/**
 *
 * drop a table
 * @param tableName: name of table
 */
void API::tableDrop(string tableName)
{
    if (!tableExist(tableName)) return;
    
    //delete a table file
    if(rm.tableDrop(tableName))
    {
        //delete a table information
        cm.dropTable(tableName);
        cout << "Drop table " << tableName << " successfully" << endl;
    }
}

/**
 *
 * drop a index
 * @param indexName: name of index
 */
void API::indexDrop(string indexName)
{
    if (cm.findFile(indexName) != INDEX_FILE)
    {
        cout << "There is no index " << indexName << endl;
        return;
    }
    
    //delete a index file
    if (rm.indexDrop(indexName))
    {
        //delete a index information
        cm.dropIndex(indexName);
        
        //delete a index tree
        im.dropIndex(indexName);
        cout << "Drop index " << indexName << " successfully" << endl;
    }
}

/**
 *
 * create a index
 * @param indexName: name of index
 * @param tableName: name of table
 * @param attributeName: name of attribute in a table
 */
void API::indexCreate(string indexName, string tableName, string attributeName)
{
    if (cm.findFile(indexName) == INDEX_FILE)
    {
        cout << "There is index " << indexName << "already" << endl;
        return;
    }
    
     //RecordManager to create a index file
    if (rm.indexCreate(indexName))
    {
        //CatalogManager to add a index information
        cm.addIndex(indexName, tableName, attributeName);
        
        //indexManager to create a index tress
        im.indexCreate(indexName, tableName, attributeName);
        cout << "Create index " << indexName << " successfully" << endl;
    }
    else
    {
        cout << "Create index " << indexName << " fail" << endl;
    }
}

/**
 *
 * create a table
 * @param tableName: name of table
 * @param attributeVector: vector of attribute
 * @param primaryKeyName: primary key of a table (default: "")
 */
void API::tableCreate(string tableName, vector<Attribute>* attributeVector, string primaryKeyName)
{
    if(cm.findFile(tableName) == TABLE_FILE)
    {
        cout << "There is a table " << tableName << "already" << endl;
        return;
    }
    
    //RecordManager to create a table file
    if(rm.tableCreate(tableName))
    {
        //CatalogManager to create a table information
        cm.addTable(tableName, attributeVector, primaryKeyName);
        cout << "Create table " << tableName << " successfully" << endl;
    }
}

/**
 *
 * show all record of table and the number of the record
 * @param tableName: name of table
 */
void API::recordShow(string tableName)
{
    vector<Condition> conditionVector;
    recordShow(tableName, &conditionVector);
}

/**
 *
 * show the record matching the coditions in the table and the number of the record
 * @param tableName: name of table
 * @param conditionVector: vector of condition
 */
void API::recordShow(string tableName, vector<Condition>* conditionVector)
{
    if (cm.findFile(tableName) == TABLE_FILE)
    {
        int num;
        num = rm.recordShow(tableName, conditionVector);
        cout << num << " records selected" << endl;
    }
    else
    {
        cout << "There is no table " << tableName << endl;
    }
}

/**
 *
 * insert a record to a table
 * @param tableName: name of table
 * @param recordContent: Vector of these content of a record
 */
void API::recordInsert(string tableName, vector<string>* recordContent)
{
    if (!tableExist(tableName)) return;
    
    char recordString[2000];
    memset(recordString, 0, 2000);
    
    //CatalogManager to get the record string
    cm.recordStringGet(tableName, recordContent, recordString);
    
    //RecordManager to insert the record into file;
    if(rm.recordInsert(tableName, recordString))
    {
         cm.insertRecord(tableName, 1);
         cout << "insert record into table " << tableName << " successful" << endl;
    }
    else
    {
        cout << "insert record into table " << tableName << " fail" << endl;
    }
}

/**
 *
 * delete all record of table
 * @param tableName: name of table
 */
void API::recordDelete(string tableName)
{
    vector<Condition> conditionVector;
    recordDelete(tableName, &conditionVector);
}

/**
 *
 * delete the record matching the coditions in the table
 * @param tableName: name of table
 * @param conditionVector: vector of condition
 */
void API::recordDelete(string tableName, vector<Condition>* conditionVector)
{
    if (!tableExist(tableName)) return;
    
    //delete record in the table file
    int numberDelete = rm.recordDelete(tableName, conditionVector);
    
    //delete the number of record in in the table
    cm.deleteValue(tableName, numberDelete);
    cout << "delete " << numberDelete << " record in table " << tableName << endl;
}


/**
 *
 * get the number of the records in table
 * @param tableName: name of table
 */
int API::recordNumGet(string tableName)
{
    if (!tableExist(tableName)) return 0;
    
    return cm.getRecordNum(tableName);
}

/**
 *
 * get the size of a record in table
 * @param tableName: name of table
 */
int API::recordSizeGet(string tableName)
{
    if (!tableExist(tableName)) return 0;
    
    return cm.calcuteLenth(tableName);
}

/**
 *
 * get the size of a type
 * @param type:  type of attribute
 */
int API::typeSizeGet(int type)
{
    return cm.calcuteLenth2(type);
}

/**
 *
 * get the vector of a attribute‘s name in a table
 * @param tableName:  name of table
 * @param attributeNameVector:  a point to vector of attributeName(which would change)
 */
int API::attributeNameGet(string tableName, vector<string>* attributeNameVector)
{
    if (tableExist(tableName)) {
        return 0;
    }
    return cm.attributeNameGet(tableName, attributeNameVector);
}


/**
 *
 * get the vector of a attribute‘s type in a table
 * @param tableName:  name of table
 * @param attributeNameVector:  a point to vector of attributeType(which would change)
 */
int API::attributeTypeGet(string tableName, vector<string>* attributeTypeVector)
{
    if (tableExist(tableName)) {
        return 0;
    }
    return cm.attributeTypeGet(tableName, attributeTypeVector);
}


/**
 *
 * get the vector of a attribute‘s type in a table
 * @param tableName:  name of table
 * @param attributeNameVector:  a point to vector of attributeType(which would change)
 */
int API::attributeGet(string tableName, vector<Attribute>* attributeVector)
{
    if (tableExist(tableName)) {
        return 0;
    }
    return cm.attributeGet(tableName, attributeVector);
}

/**
 *
 * insert a value to index tree
 * @param indexName:  name of index
 * @param value: value that want to change
 */
void API::indexValueInsert(string indexName, string value)
{
    if(cm.findFile(indexName) != INDEX_FILE)
    {
         cout << "There is no index " << indexName << endl;
        return;
    }
    
    im.indexValueInsert(indexName, value);
}

int API::tableExist(string tableName)
{
    if (cm.findFile(tableName) != TABLE_FILE)
    {
        cout << "There is no table " << tableName << endl;
        return 0;
    }
    else
    {
        return 1;
    }
}
