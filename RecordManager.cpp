//
//  RecordManager.cpp
//  minisql
//
//  Created by 邓永辉 on 14/11/5.
//  Copyright (c) 2014年 邓永辉. All rights reserved.
//

#include <iostream>
#include "RecordManager.h"
#include "API.h"

/**
 *
 * create a table
 * @param tableName: name of table
 */
int RecordManager::tableCreate(string tableName)
{
    string tableFileName = tableFileNameGet(tableName);
    
    FILE *fp;
    fp = fopen(tableFileName.c_str(), "w+");
    if (fp == NULL)
    {
        return 0;
    }
    fclose(fp);
    return 1;
}

/**
 *
 * drop a table
 * @param tableName: name of table
 */
int RecordManager::tableDrop(string tableName)
{
    string tableFileName = tableFileNameGet(tableName);

    if (remove(tableFileName.c_str()))
    {
        return 0;
    }
    return 1;
}

/**
 *
 * create a index
 * @param indexName: name of index
 */
int RecordManager::indexCreate(string indexName)
{
    string indexFileName = indexFileNameGet(indexName);
    
    FILE *fp;
    fp = fopen(indexFileName.c_str(), "w+");
    if (fp == NULL)
    {
        return 0;
    }
    fclose(fp);
    return 1;
}

/**
 *
 * drop a index
 * @param indexName: name of index
 */
int RecordManager::indexDrop(string indexName)
{
    string indexFileName = indexFileNameGet(indexName);
    
    if (remove(indexFileName.c_str()))
    {
        return 0;
    }
    return 1;
}

/**
 *
 * insert a record to table
 * @param tableName: name of table
 * @param record: value of record
 * @return the position of block in the file(-1 represent error)
 */
int RecordManager::recordInsert(string tableName,char* record, int recordSize)
{
    fileNode *ftmp = bm.getFile(tableFileNameGet(tableName).c_str());
    blockNode *btmp = bm.getBlockHead(ftmp);
    while (true)
    {
        if (btmp == NULL)
        {
            return -1;
        }
        if (btmp->using_size <= BLOCK_SIZE - recordSize)
        {
            char* addressBegin;
            addressBegin = btmp->address + btmp->using_size;
            memcpy(addressBegin, record, recordSize);
            btmp->using_size += recordSize;
            bm.set_dirty(*btmp);
            return btmp->offsetNum;
            break;
        }
        else
        {
            btmp = bm.getNextBlock(ftmp, btmp);
        }
    }
    
    return -1;
}

int RecordManager::recordAllShow(string tableName, vector<Condition>* conditionVector)
{
    
    return  0;
}

/**
 *
 * print record of a table in a block
 * @param tableName: name of table
 * @param block: search record in the block
 * @param conditionVector: the conditions list
 * @return int: the number of the record meet requirements int the block(1 represent error)
 */
int RecordManager::recordBlockShow(string tableName, vector<Condition>* conditionVector, blockNode* block)
{
    //if block is null, return -1
    if (block == NULL)
    {
        return -1;
    }
    int count = 0;
    
    char* recordBegin = block->address;
    vector<Attribute> attributeVector;
    int recordSize = api->recordSizeGet(tableName);
    
    api->attributeGet(tableName, &attributeVector);
    
    while (recordBegin - block->address < block->using_size)
    {
        //if the recordBegin point to a record
        
        if(recordConditionFit(recordBegin, recordSize, &attributeVector, conditionVector))
        {
            count ++;
            recordPrint(recordBegin, recordSize, &attributeVector);
            cout << endl;
        }
        
        recordBegin += recordSize;
    }
    
    return count;
}

/**
 *
 * judge if the record meet the requirement
 * @param recordBegin: point to a record
 * @param recordSize: size of the record
 * @param attributeVector: the attribute list of the record
 * @param conditionVector: the conditions
 * @return bool: if the record fit the condition
 */
bool RecordManager::recordConditionFit(char* recordBegin,int recordSize, vector<Attribute>* attributeVector,vector<Condition>* conditionVector)
{
    int type;
    string attributeName;
    int typeSize;
    char content[255];
    
    char *contentBegin = recordBegin;
    for(int i = 0; i < attributeVector->size(); i++)
    {
        type = (*attributeVector)[i].type;
        attributeName = (*attributeVector)[i].name;
        typeSize = api->typeSizeGet(type);
        
        //init content (when content is string , we can get a string easily)
        memset(content, 0, 255);
        if (conditionVector != NULL)
        {
            memcpy(content, contentBegin, typeSize);
            for(Condition condition : *conditionVector)
            {
                if (condition.attributeName == attributeName)
                {
                    //if this attribute need to deal about the condition
                    if(!contentConditionFit(content, type, &condition))
                    {
                        //if this record is not fit the conditon
                        return false;
                    }
                }
            }
        }
        contentBegin += typeSize;
    }
    return true;
}

/**
 *
 * print value of record
 * @param recordBegin: point to a record
 * @param recordSize: size of the record
 * @param attributeVector: the attribute list of the record
 */
void RecordManager::recordPrint(char* recordBegin, int recordSize, vector<Attribute>* attributeVector)
{
    int type;
    string attributeName;
    int typeSize;
    char content[255];
    
    char *contentBegin = recordBegin;
    for(int i = 0; i < attributeVector->size(); i++)
    {
        type = (*attributeVector)[i].type;
        typeSize = api->typeSizeGet(type);
        
        //init content (when content is string , we can get a string easily)
        memset(content, 0, 255);
        
        memcpy(content, contentBegin, typeSize);

        contentPrint(content, type);

        contentBegin += typeSize;
    }
}

/**
 *
 * print value of content
 * @param content: point to content
 * @param type: type of content
 */
void RecordManager::contentPrint(char * content, int type)
{
    if (type == Attribute::TYPE_INT)
    {
        //if the content is a int
        int tmp = *((int *) content);   //get content value by point
        cout << tmp << " ";
    }
    else if (type == Attribute::TYPE_FLOAT)
    {
        //if the content is a float
        float tmp = *((float *) content);   //get content value by point
        cout << tmp << " ";
    }
    else
    {
        //if the content is a string
        cout << content << " ";
    }

}

/**
 *
 * judge if the content meet the requirement
 * @param content: point to content
 * @param type: type of content
 * @param condition: condition
 * @return bool: the content if meet
 */
bool RecordManager::contentConditionFit(char* content,int type,Condition* condition)
{
    if (type == Attribute::TYPE_INT)
    {
        //if the content is a int
        int tmp = *((int *) content);   //get content value by point
        return condition->ifRight(tmp);
    }
    else if (type == Attribute::TYPE_FLOAT)
    {
        //if the content is a float
        float tmp = *((float *) content);   //get content value by point
        return condition->ifRight(tmp);
    }
    else
    {
        //if the content is a string
        return condition->ifRight(content);
    }
    return true;
}

/**
 *
 * get a index's file name
 * @param indexName: name of index
 */
string RecordManager::indexFileNameGet(string indexName)
{
    return "INDEX_FILE_" + indexName;
}

/**
 *
 * get a table's file name
 * @param tableName: name of table
 */
string RecordManager::tableFileNameGet(string tableName)
{
    return "TABLE_FILE_" + tableName;
}