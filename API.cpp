//
//  API.cpp
//  minisql
//
//  Created by 邓永辉 on 14/11/5.
//  Copyright (c) 2014年 邓永辉. All rights reserved.
//

#include "API.h"
#include "RecordManager.h"
#include "CatalogManager.h"
#include "IndexManager.h"

#define UNKNOWN_FILE 8
#define TABLE_FILE 9
#define INDEX_FILE 10

CatalogManager *cm;
IndexManager* im;

/**
 *
 * drop a table
 * @param tableName: name of table
 */
void API::tableDrop(string tableName)
{
    if (!tableExist(tableName)) return;
    
    vector<string> indexNameVector;
    
    //get all index in the table, and drop them all
    indexNameListGet(tableName, &indexNameVector);
    for (int i = 0; i < indexNameVector.size(); i++)
    {
        cout << indexNameVector[i] << endl;
        
        indexDrop(indexNameVector[i]);
    }
    
    //delete a table file
    if(rm->tableDrop(tableName))
    {
        //delete a table information
        cm->dropTable(tableName);
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
    if (cm->findIndex(indexName) != INDEX_FILE)
    {
        cout << "There is no index " << indexName << endl;
        return;
    }
    
    //delete a index file
    if (rm->indexDrop(indexName))
    {
        
        //get type of index
        int indexType = cm->getIndexType(indexName);
        if (indexType == -2)
        {
            cout << "" << "error";
            return;
        }
        
        //delete a index information
        cm->dropIndex(indexName);
        
        //delete a index tree
        im->dropIndex(rm->indexFileNameGet(indexName), indexType);
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
    if (cm->findIndex(indexName) == INDEX_FILE)
    {
        cout << "There is index " << indexName << " already" << endl;
        return;
    }
    
    if (!tableExist(tableName)) return;
    
    vector<Attribute> attributeVector;
    cm->attributeGet(tableName, &attributeVector);
    int i;
    int type = 0;
    for (i = 0; i < attributeVector.size(); i++)
    {
        if (attributeName == attributeVector[i].name)
        {
            if (!attributeVector[i].ifUnique)
            {
                cout << "the attribute is not unique" << endl;
                
                return;
            }
            type = attributeVector[i].type;
            break;
        }
    }
    
    if (i == attributeVector.size())
    {
        cout << "there is not this attribute in the table" << endl;
        return;
    }
    
     //RecordManager to create a index file
    if (rm->indexCreate(indexName))
    {
        //CatalogManager to add a index information
        cm->addIndex(indexName, tableName, attributeName, type);
        
        //get type of index
        int indexType = cm->getIndexType(indexName);
        if (indexType == -2)
        {
            cout << "error";
            return;
        }
        
        //indexManager to create a index tress
        im->createIndex(rm->indexFileNameGet(indexName), indexType);
        
        //recordManager insert already record to index
        rm->indexRecordAllAlreadyInsert(tableName, indexName);
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
void API::tableCreate(string tableName, vector<Attribute>* attributeVector, string primaryKeyName,int primaryKeyLocation)
{
    if(cm->findTable(tableName) == TABLE_FILE)
    {
        cout << "There is a table " << tableName << " already" << endl;
        return;
    }
    
    //RecordManager to create a table file
    if(rm->tableCreate(tableName))
    {
        //CatalogManager to create a table information
        cm->addTable(tableName, attributeVector, primaryKeyName, primaryKeyLocation);
   
        cout << "Create table " << tableName << " successfully" << endl;
    }
    
    if (primaryKeyName != "")
    {
        //get a primary key
        string indexName = primaryIndexNameGet(tableName);
        indexCreate(indexName, tableName, primaryKeyName);
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
    if (cm->findTable(tableName) == TABLE_FILE)
    {
        int num = 0;
        vector<Attribute> attributeVector;
        attributeGet(tableName, &attributeVector);
        
        //print all attribute name
        tableAttributePrint(&attributeVector);
        
        blockNode* block = NULL;
        int blockOffset = -1;
        if (conditionVector != NULL)
        {
            for (Condition condition : *conditionVector)
            {
                if (condition.operate == Condition::OPERATOR_EQUAL)
                {
                    for (Attribute attribute : attributeVector)
                    {
                        if (attribute.index != "" && attribute.name == condition.attributeName)
                        {
                            blockOffset = im->searchIndex(rm->indexFileNameGet(attribute.index), condition.value, attribute.type);
                        }
                    }
                }
            }
        }
        
        if (blockOffset == -1)
        {
            //if we con't find the block by index,we need to find all block
            num = rm->recordAllShow(tableName, conditionVector);
        }
        else
        {
            fileNode *ftmp = bm.getFile(rm->tableFileNameGet(tableName).c_str());
            block = bm.getBlockByOffset(ftmp, blockOffset);
            //find the block by index,search in the block
            num = rm->recordBlockShow(tableName, conditionVector, block);
        }
        
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
    
    string indexName;
    
    //deal if the record could be insert (if index is exist)
    vector<Attribute> attributeVector;
    
    vector<Condition> conditionVector;
    
    attributeGet(tableName, &attributeVector);
    for (int i = 0 ; i < attributeVector.size(); i++)
    {
        indexName = attributeVector[i].indexNameGet();
        if (indexName != "")
        {
            //if the attribute has a index
            int blockoffest = im->searchIndex(rm->indexFileNameGet(indexName), (*recordContent)[i], attributeVector[i].type);
            
            if (blockoffest != -1)
            {
                //if the value has exist in index tree then fail to insert the record
                cout << "insert fail because index value exist" << endl;
                return;
            }
            
            
        }
        else if (attributeVector[i].ifUnique)
        {
            //if the attribute is unique but not index
            Condition condition(attributeVector[i].name, (*recordContent)[i], Condition::OPERATOR_EQUAL);
            conditionVector.insert(conditionVector.end(), condition);
        }
    }
    
    if (conditionVector.size() > 0)
    {
        for (int i = 0; i < conditionVector.size(); i++) {
            vector<Condition> conditionTmp;
            conditionTmp.insert(conditionTmp.begin(), conditionVector[i]);
            
            int recordConflictNum =  rm->recordAllFind(tableName, &conditionTmp);
            if (recordConflictNum > 0) {
                cout << "insert fail because unique value exist" << endl;
                return;
            }

        }
    }
    
    char recordString[2000];
    memset(recordString, 0, 2000);
    
    //CatalogManager to get the record string
    cm->recordStringGet(tableName, recordContent, recordString);
    
    //RecordManager to insert the record into file; and get the position of block being insert
    int recordSize = cm->calcuteLenth(tableName);
    int blockOffset = rm->recordInsert(tableName, recordString, recordSize);
    
    if(blockOffset >= 0)
    {
        recordIndexInsert(recordString, recordSize, &attributeVector, blockOffset);
        cm->insertRecord(tableName, 1);
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
    
    int num = 0;
    vector<Attribute> attributeVector;
    attributeGet(tableName, &attributeVector);

    blockNode* block = NULL;
    int blockOffset = -1;
    if (conditionVector != NULL)
    {
        for (Condition condition : *conditionVector)
        {
            if (condition.operate == Condition::OPERATOR_EQUAL)
            {
                for (Attribute attribute : attributeVector)
                {
                    if (attribute.index != "" && attribute.name == condition.attributeName)
                    {
                        blockOffset = im->searchIndex(rm->indexFileNameGet(attribute.index), condition.value, attribute.type);
                    }
                }
            }
        }
    }

    
    if (blockOffset == -1)
    {
        //if we con't find the block by index,we need to find all block
        num = rm->recordAllDelete(tableName, conditionVector);
    }
    else
    {
        fileNode *ftmp = bm.getFile(rm->tableFileNameGet(tableName).c_str());
        block = bm.getBlockByOffset(ftmp, blockOffset);
        //find the block by index,search in the block
        num = rm->recordBlockDelete(tableName, conditionVector, block);
    }
    
    cout << num << "records selected" << endl;
    
    //delete the number of record in in the table
    cm->deleteValue(tableName, num);
    cout << "delete " << num << " record in table " << tableName << endl;
}


/**
 *
 * get the number of the records in table
 * @param tableName: name of table
 */
int API::recordNumGet(string tableName)
{
    if (!tableExist(tableName)) return 0;
    
    return cm->getRecordNum(tableName);
}

/**
 *
 * get the size of a record in table
 * @param tableName: name of table
 */
int API::recordSizeGet(string tableName)
{
    if (!tableExist(tableName)) return 0;
    
    return cm->calcuteLenth(tableName);
}

/**
 *
 * get the size of a type
 * @param type:  type of attribute
 */
int API::typeSizeGet(int type)
{
    return cm->calcuteLenth2(type);
}

/**
 *
 * get the vector of a all name of index in the table
 * @param tableName:  name of table
 * @param indexNameVector:  a point to vector of indexName(which would change)
 */
int API::indexNameListGet(string tableName, vector<string>* indexNameVector)
{
    if (!tableExist(tableName)) {
        return 0;
    }
    return cm->indexNameListGet(tableName, indexNameVector);
}

void API::allIndexAddressInfoGet(vector<IndexInfo> *indexNameVector)
{
    cm->getAllIndex(indexNameVector);
    for (int i = 0; i < (*indexNameVector).size(); i++)
    {
        (*indexNameVector)[i].indexName = rm->indexFileNameGet((*indexNameVector)[i].indexName);
    }
}


/**
 *
 * get the vector of a attribute‘s type in a table
 * @param tableName:  name of table
 * @param attributeNameVector:  a point to vector of attributeType(which would change)
 */
int API::attributeGet(string tableName, vector<Attribute>* attributeVector)
{
    if (!tableExist(tableName)) {
        return 0;
    }
    return cm->attributeGet(tableName, attributeVector);
}

/**
 *
 * insert all index value of a record to index tree
 * @param recordBegin: point to record begin
 * @param attributeVector:  a point to vector of attributeType(which would change)
 */
void API::recordIndexInsert(char* recordBegin,int recordSize, vector<Attribute>* attributeVector,  int blockOffset)
{
    char* contentBegin = recordBegin;
    for (int i = 0; i < (*attributeVector).size() ; i++)
    {
        int type = (*attributeVector)[i].type;
        int typeSize = typeSizeGet(type);
        if ((*attributeVector)[i].index != "")
        {
            indexInsert((*attributeVector)[i].index, contentBegin, type, blockOffset);
        }
        
        contentBegin += typeSize;
    }
}

void API::indexInsert(string indexName, char* contentBegin, int type, int blockOffset)
{
    string content= "";
    stringstream tmp;
    //if the attribute has index
    ///这里传*attributeVector)[i].index这个index的名字, blockOffset,还有值
    if (type == Attribute::TYPE_INT)
    {
        int value = *((int*)contentBegin);
        tmp << value;
    }
    else if (type == Attribute::TYPE_FLOAT)
    {
        float value = *((float* )contentBegin);
        tmp << value;
    }
    else
    {
        char value[255];
        memset(value, 0, 255);
        memcpy(value, contentBegin, sizeof(char[type]));
        string stringTmp = value;
        tmp << stringTmp;
    }
    tmp >> content;
    im->insertIndex(rm->indexFileNameGet(indexName), content, blockOffset, type);
}

void API::recordIndexDelete(char* recordBegin,int recordSize, vector<Attribute>* attributeVector, int blockOffset)
{
    char* contentBegin = recordBegin;
    for (int i = 0; i < (*attributeVector).size() ; i++)
    {
        int type = (*attributeVector)[i].type;
        int typeSize = typeSizeGet(type);
        
        string content= "";
        stringstream tmp;
        
        if ((*attributeVector)[i].index != "")
        {
            //if the attribute has index
            ///这里传*attributeVector)[i].index这个index的名字, blockOffset,还有值
            if (type == Attribute::TYPE_INT)
            {
                int value = *((int*)contentBegin);
                tmp << value;
            }
            else if (type == Attribute::TYPE_FLOAT)
            {
                float value = *((float* )contentBegin);
                tmp << value;
            }
            else
            {
                char value[255];
                memset(value, 0, 255);
                memcpy(value, contentBegin, sizeof(char[type]));
                string stringTmp = value;
                tmp << stringTmp;
            }
        }
        
        contentBegin += typeSize;
    }

}


int API::tableExist(string tableName)
{
    if (cm->findTable(tableName) != TABLE_FILE)
    {
        cout << "There is no table " << tableName << endl;
        return 0;
    }
    else
    {
        return 1;
    }
}

string API::primaryIndexNameGet(string tableName)
{
    return  "PRIMARY_" + tableName;
}

void API::tableAttributePrint(vector<Attribute>* attributeVector)
{
    for (int i = 0; i < (*attributeVector).size(); i++)
    {
        cout << (*attributeVector)[i].name << " ";
    }
    cout << endl;
}

///**
// *
// * insert a value to index tree
// * @param indexName:  name of index
// * @param value: value that want to change
// */
//void API::indexValueInsert(string indexName, string value, int blockOffset)
//{
//    if(cm->findFile(indexName) != INDEX_FILE)
//    {
//         cout << "There is no index " << indexName << endl;
//        return;
//    }
//
//    im->indexValueInsert(indexName, value, blockOffset);
//}


