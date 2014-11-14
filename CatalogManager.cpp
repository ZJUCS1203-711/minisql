#include "CatalogManager.h"
#include "BufferManager.h"
#include "IndexInfo.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include "Attribute.h"
#define UNKNOWN_FILE 8
#define TABLE_FILE 9
#define INDEX_FILE 10
CatalogManager::CatalogManager() {
    // TODO Auto-generated constructor stub

}

CatalogManager::~CatalogManager() {
    // TODO Auto-generated destructor stub
}

int CatalogManager::dropTable(string tableName)
{
    if (remove(tableName.c_str()))
    {
        return 0;
    }
    return 1;
}
int CatalogManager::getIndexType(string indexName)
{
    fileNode *ftmp = bm.getFile("Indexs");
    blockNode *btmp = bm.getBlockHead(ftmp);
    if (btmp )
    {
        char* addressBegin;
        addressBegin = bm.get_content(*btmp);
        IndexInfo * i = (IndexInfo *)addressBegin;
        int flag = UNKNOWN_FILE;
        for(int j = 0 ;j<(bm.get_usingSize(*btmp)/sizeof(IndexInfo));j++)
        {
            if((*i).indexName==indexName)
            {
                return i->type;
            }
            i ++;
        }
        return -2;
    }

    return 0;
}
int CatalogManager::addIndex(string indexName,string tableName,string Attribute)
{
    fileNode *ftmp = bm.getFile("Indexs");
    blockNode *btmp = bm.getBlockHead(ftmp);
    IndexInfo i(indexName,tableName,Attribute);
    while (true)
    {
        if (btmp == NULL)
        {
            return 0;
        }
        if (bm.get_usingSize(*btmp) <= bm.getBlockSize() - sizeof(IndexInfo))
        {

            char* addressBegin;
            addressBegin = bm.get_content(*btmp) + bm.get_usingSize(*btmp);
            cout<<"address:"<<(int *)addressBegin<<endl;
            memcpy(addressBegin, &i, sizeof(IndexInfo));
            bm.set_usingSize(*btmp, bm.get_usingSize(*btmp) + sizeof(IndexInfo));
            bm.set_dirty(*btmp);
            return 1;
        }
        else
        {
            btmp = bm.getNextBlock(ftmp, btmp);
        }
    }

    return 0;
}
int CatalogManager::findFile(string fileName)
{
    fileNode *ftmp = bm.getFile("Indexs");
    blockNode *btmp = bm.getBlockHead(ftmp);
    if (btmp )
    {
        char* addressBegin;
        addressBegin = bm.get_content(*btmp);
        IndexInfo * i = (IndexInfo *)addressBegin;
        int flag = UNKNOWN_FILE;
        for(int j = 0 ;j<(bm.get_usingSize(*btmp)/sizeof(IndexInfo));j++)
        {
            if((*i).indexName==fileName)
            {
                flag = INDEX_FILE;
                break;
            }
            if((*i).tableName==fileName)
            {
                flag = TABLE_FILE;
                break;
            }
            i ++;
        }
        return flag;
    }

    return 0;
}
int CatalogManager::dropIndex(string index)
{
    fileNode *ftmp = bm.getFile("Indexs");
    blockNode *btmp = bm.getBlockHead(ftmp);
    if (btmp)
    {
        char* addressBegin;
        addressBegin = bm.get_content(*btmp);
        IndexInfo * i = (IndexInfo *)addressBegin;
        int j = 0;
        for(j = 0 ;j<(bm.get_usingSize(*btmp)/sizeof(IndexInfo));j++)
        {
            if((*i).indexName==index)
            {
                break;
            }
            i ++;
        }
        for(;j<(bm.get_usingSize(*btmp)/sizeof(IndexInfo)-1);j++)
        {
            (*i) = *(i + sizeof(IndexInfo));
            i ++;
        }
        bm.set_usingSize(*btmp, bm.get_usingSize(*btmp) - sizeof(IndexInfo));
        bm.set_dirty(*btmp);

        return 1;
    }

    return 0;
}
int CatalogManager::indexNameListGet(string tableName, vector<string>* indexNameVector)
{
    fileNode *ftmp = bm.getFile("Indexs");
    blockNode *btmp = bm.getBlockHead(ftmp);
    if (btmp )
    {
        char* addressBegin;
        addressBegin = bm.get_content(*btmp);
        IndexInfo * i = (IndexInfo *)addressBegin;
        for(int j = 0 ;j<(bm.get_usingSize(*btmp)/sizeof(IndexInfo));j++)
        {
            if((*i).tableName==tableName)
            {
                (*indexNameVector).push_back((*i).indexName);
            }
            i ++;
        }
        return 1;
    }

    return 0;
}

int CatalogManager::deleteValue(string tableName, int deleteNum)
{
    fileNode *ftmp = bm.getFile(tableName.c_str());
    blockNode *btmp = bm.getBlockHead(ftmp);

    if (btmp)
    {

        char* addressBegin = bm.get_content(*btmp) ;
        int recordNum = *addressBegin;
        if(recordNum<deleteNum)
        {
            cout<<"error in CatalogManager::deleteValue"<<endl;
            return 0;
        }
        else
            recordNum -= deleteNum;
        *addressBegin = recordNum;
        bm.set_dirty(*btmp);
        return recordNum;
    }
    return 0;
}
int CatalogManager::insertRecord(string tableName, int recordNum)
{
    fileNode *ftmp = bm.getFile(tableName.c_str());
    blockNode *btmp = bm.getBlockHead(ftmp);

    if (btmp)
    {

        char* addressBegin = bm.get_content(*btmp) ;
        int originalRecordNum = *addressBegin;
        originalRecordNum += recordNum;
        *addressBegin = originalRecordNum;
        bm.set_dirty(*btmp);
        return recordNum;
    }
    return 0;
}

int CatalogManager::getRecordNum(string tableName)
{
    fileNode *ftmp = bm.getFile(tableName.c_str());
    blockNode *btmp = bm.getBlockHead(ftmp);

    if (btmp)
    {

        char* addressBegin = bm.get_content(*btmp) ;
        int recordNum = *addressBegin;
        return recordNum;
    }
    return 0;
}

int CatalogManager::addTable(string tableName, vector<Attribute>* attributeVector, string primaryKeyName = "",int primaryKeyLocation = 0)
{
    FILE *fp;
    fp = fopen(tableName.c_str(), "w+");
    if (fp == NULL)
    {
        return 0;
    }
    fclose(fp);
    fileNode *ftmp = bm.getFile(tableName.c_str());
    blockNode *btmp = bm.getBlockHead(ftmp);

    if (btmp )
    {
        char* addressBegin = bm.get_content(*btmp) ;
        *addressBegin = 0;// 0 record number
        addressBegin++;
        *addressBegin = primaryKeyLocation;//1 as what it says
        addressBegin++;
        *addressBegin = (*attributeVector).size();// 2 attribute number
        addressBegin++;
        //memcpy(addressBegin, attributeVector, (*attributeVector).size()*sizeof(Attribute));
        for(int i= 0;i<(*attributeVector).size();i++)
        {
            memcpy(addressBegin, &((*attributeVector)[i]), sizeof(Attribute));
            addressBegin += sizeof(Attribute);
        }
        bm.set_usingSize(*btmp, bm.get_usingSize(*btmp) + (*attributeVector).size()*sizeof(Attribute)+3);
        bm.set_dirty(*btmp);
        return 1;
    }
    return 0;
}

int CatalogManager::attributeGet(string tableName, vector<Attribute>* attributeVector)
{
    fileNode *ftmp = bm.getFile(tableName.c_str());
    blockNode *btmp = bm.getBlockHead(ftmp);

    if (btmp)
    {

        char* addressBegin = bm.get_content(*btmp) ;
        addressBegin += 2;
        int size = *addressBegin;
        addressBegin++;
        Attribute *a = (Attribute *)addressBegin;
        for(int i =0;i<size;i++)
        {
            attributeVector->push_back(*a);
            a ++;
        }

        return 1;
    }
    return 0;
}

int CatalogManager::calcuteLenth(string tableName)
{
    fileNode *ftmp = bm.getFile(tableName.c_str());
    blockNode *btmp = bm.getBlockHead(ftmp);

    if (btmp)
    {
        int singleRecordSize =  0;
        char* addressBegin = bm.get_content(*btmp) ;
        addressBegin += 2;
        int size = *addressBegin;
        addressBegin++;
        Attribute *a = (Attribute *)addressBegin;
        for(int i =0;i<size;i++)
        {
            if((*a).type==-1)
            {
                singleRecordSize += sizeof(float);
            }
            else if((*a).type == 0)
            {
                singleRecordSize += sizeof(int);
            }
            else if((*a).type>0)
            {
                singleRecordSize += (*a).type * sizeof(char);
            }
            else
            {
                cout<<"Catalog data damaged!"<<endl;
                return 0;
            }
            a ++;
        }

        return singleRecordSize;
    }
    return 0;
}

int CatalogManager::calcuteLenth2(int type){
    if (type == Attribute::TYPE_INT) {
        return sizeof(int);
    }
    else if (type == Attribute::TYPE_FLOAT)
    {
        return sizeof(float);
    }
    else{
        return (int) sizeof(char[type]);
    }
}      //這理我的type改成了int类型，而不是一个String，type类型见attribute.h

// 通过table名和recordContent得到这个table的record的字符传，写入传进的字符串
void CatalogManager::recordStringGet(string tableName, vector<string>* recordContent, char* recordResult)
{
    vector<Attribute> attributeVector;
    attributeGet(tableName, &attributeVector);
    char * contentBegin = recordResult;

    for(int i = 0; i < attributeVector.size(); i++)
    {
        Attribute attribute = attributeVector[i];
        string content = (*recordContent)[i];
        int type = attribute.type;
        int typeSize = calcuteLenth2(type);

        stringstream ss;
        ss << content;
        if (type == Attribute::TYPE_INT)
        {
            //if the content is a int
            int intTmp;
            ss >> intTmp;
            memcpy(contentBegin, ((char*)&intTmp), typeSize);
        }
        else if (type == Attribute::TYPE_FLOAT)
        {
            //if the content is a float
            float intTmp;
            ss >> intTmp;
            memcpy(contentBegin, ((char*)&intTmp), typeSize);
        }
        else
        {
            //if the content is a string
            memcpy(contentBegin, content.c_str(), typeSize);
        }

        contentBegin += typeSize;
    }
    return ;
}
