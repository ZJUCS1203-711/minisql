//
//  IndexManager.cpp
//  Minisql
//
//  Created by xuyuhao on 14/11/14.
//  Copyright (c) 2014年 xuyuhao. All rights reserved.
//
/*
#include "IndexManager.h"
#include <iostream>
using namespace std;

IndexManager::IndexManager()
{
    
}

IndexManager::~IndexManager()
{
    //write back to the disk
    for(intMap::iterator itInt = indexIntMap.begin();itInt != indexIntMap.end(); itInt ++)
    {
        if(itInt->second)
        {
            delete itInt->second;
        }
    }
    for(stringMap::iterator itString = indexStringMap.begin();itString != indexStringMap.end(); itString ++)
    {
        if(itString->second)
        {
            delete itString->second;
        }
    }
    for(floatMap::iterator itFloat = indexFloatMap.begin();itFloat != indexFloatMap.end(); itFloat ++)
    {
        if(itFloat->second)
        {
            delete itFloat->second;
        }
    }
}

void IndexManager::createIndex(string indexName,int type)
{
    int degree = getDegree(type);
    if(type == TYPE_INT)
    {
        BPlusTree<int> *tree = new BPlusTree<int>(indexName,degree);
        indexIntMap.insert(intMap::value_type(indexName, tree));
    }
    else if(type == TYPE_FLOAT)
    {
        BPlusTree<float> *tree = new BPlusTree<float>(indexName,degree);
        indexFloatMap.insert(floatMap::value_type(indexName, tree));
    }
    else // string
    {
        BPlusTree<string> *tree = new BPlusTree<string>(indexName,degree);
        indexStringMap.insert(stringMap::value_type(indexName, tree));
    }
    
}

void IndexManager::dropIndex(string indexName,int type)
{
    if(type == TYPE_INT)
    {
        intMap::iterator itInt = indexIntMap.find(indexName);
        if(itInt == indexIntMap.end())
        {
            cout << "Error:in drop index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            delete itInt->second;
            indexIntMap .erase(itInt);
        }
    }
    else if(type == TYPE_FLOAT)
    {
        floatMap::iterator itFloat = indexFloatMap.find(indexName);
        if(itFloat == indexFloatMap.end())
        {
            cout << "Error:in drop index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            delete itFloat->second;
            indexFloatMap.erase(itFloat);
        }
    }
    else // string
    {
        stringMap::iterator itString = indexStringMap.find(indexName);
        if(itString == indexStringMap.end())
        {
            cout << "Error:in drop index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            delete itString->second;
            indexStringMap.erase(itString);
        }
    }

}

offsetNumber IndexManager::searchIndex(string indexName,string key,int type)
{
    if(type == TYPE_INT)
    {
        intMap::iterator itInt = indexIntMap.find(indexName);
        if(itInt == indexIntMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            return itInt->second->search((int)key);
        }
    }
    else if(type == TYPE_FLOAT)
    {
        floatMap::iterator itFloat = indexFloatMap.find(indexName);
        if(itFloat == indexFloatMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            return itFloat->second->search((float)key);

        }
    }
    else // string
    {
        stringMap::iterator itString = indexStringMap.find(indexName);
        if(itString == indexStringMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            return itString->second->search((string)key);
        }
    }
}

void IndexManager::insertIndex(string indexName,string key,offsetNumber blockOffset,int type)
{
    if(type == TYPE_INT)
    {
        intMap::iterator itInt = indexIntMap.find(indexName);
        if(itInt == indexIntMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            return itInt->second->insertKey((int)key),blockOffset);
        }
    }
    else if(type == TYPE_FLOAT)
    {
        floatMap::iterator itFloat = indexFloatMap.find(indexName);
        if(itFloat == indexFloatMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            return itFloat->second->insertKey((float)key),blockOffset)
            
        }
    }
    else // string
    {
        stringMap::iterator itString = indexStringMap.find(indexName);
        if(itString == indexStringMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            return itString->second->insertKey((string)key),blockOffset);
        }
    }
}

void IndexManager::deleteIndexByKey(string indexName,string key,int type)
{
    if(type == TYPE_INT)
    {
        intMap::iterator itInt = indexIntMap.find(indexName);
        if(itInt == indexIntMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            return itInt->second->deleteKey((int)key));
        }
    }
    else if(type == TYPE_FLOAT)
    {
        floatMap::iterator itFloat = indexFloatMap.find(indexName);
        if(itFloat == indexFloatMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            return itFloat->second->deleteKey((float)key);
            
        }
    }
    else // string
    {
        stringMap::iterator itString = indexStringMap.find(indexName);
        if(itString == indexStringMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return;
        }
        else
        {
            return itString->second->deleteKey(key);
        }
    }
}

int IndexManager::getDegree(int type)
{

}
*/