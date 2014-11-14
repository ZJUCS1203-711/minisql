//
//  IndexManager.cpp
//  Minisql
//
//  Created by xuyuhao on 14/11/14.
//  Copyright (c) 2014年 xuyuhao. All rights reserved.
//

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
            itInt -> second->writtenbackToDiskAll();
            delete itInt->second;
        }
    }
    for(stringMap::iterator itString = indexStringMap.begin();itString != indexStringMap.end(); itString ++)
    {
        if(itString->second)
        {
            itString ->second-> writtenbackToDiskAll();
            delete itString->second;
        }
    }
    for(floatMap::iterator itFloat = indexFloatMap.begin();itFloat != indexFloatMap.end(); itFloat ++)
    {
        if(itFloat->second)
        {
            itFloat ->second-> writtenbackToDiskAll();
            delete itFloat->second;
        }
    }
}

void IndexManager::createIndex(string indexName,int type)
{
    int keySize = getKeySize(type);
//TODO:    int degree = getDegree(type);
    int degree = 7;
    if(type == TYPE_INT)
    {
        BPlusTree<int> *tree = new BPlusTree<int>(indexName,keySize,degree);
        indexIntMap.insert(intMap::value_type(indexName, tree));
    }
    else if(type == TYPE_FLOAT)
    {
        BPlusTree<float> *tree = new BPlusTree<float>(indexName,keySize,degree);
        indexFloatMap.insert(floatMap::value_type(indexName, tree));
    }
    else // string
    {
        BPlusTree<string> *tree = new BPlusTree<string>(indexName,keySize,degree);
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
    setKey(type, key);
    
    if(type == TYPE_INT)
    {
        intMap::iterator itInt = indexIntMap.find(indexName);
        if(itInt == indexIntMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return -1;
        }
        else
        {
            return itInt->second->search(kt.intTmp);
        }
    }
    else if(type == TYPE_FLOAT)
    {
        floatMap::iterator itFloat = indexFloatMap.find(indexName);
        if(itFloat == indexFloatMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return -1;
        }
        else
        {
            return itFloat->second->search(kt.floatTmp);

        }
    }
    else // string
    {
        stringMap::iterator itString = indexStringMap.find(indexName);
        if(itString == indexStringMap.end())
        {
            cout << "Error:in search index, no index " << indexName <<" exits" << endl;
            return -1;
        }
        else
        {
       //     itString->second->debug_print();
            return itString->second->search(key);
        }
    }
}

void IndexManager::insertIndex(string indexName,string key,offsetNumber blockOffset,int type)
{
    setKey(type, key);

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
            itInt->second->insertKey(kt.intTmp,blockOffset);
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
            itFloat->second->insertKey(kt.floatTmp,blockOffset);
            
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
            itString->second->insertKey(key,blockOffset);
            itString->second->debug_print();
        }
    }
}

void IndexManager::deleteIndexByKey(string indexName,string key,int type)
{
    setKey(type, key);

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
            itInt->second->deleteKey(kt.intTmp);
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
            itFloat->second->deleteKey(kt.floatTmp);
            
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
           // itString->second->debug_print();
            itString->second->deleteKey(key);
        }
    }
}

int IndexManager::getDegree(int type)
{
    int degree = bm.getBlockSize()/(getKeySize(type)+sizeof(offsetNumber));
    if(degree %2 == 0) degree -= 1;
    return degree;
}

int IndexManager::getKeySize(int type)
{
    if(type == TYPE_FLOAT)
        return sizeof(float);
    else if(type == TYPE_INT)
        return sizeof(int);
    else if(type > 0)
        return type + 1;
    else
    {
        cout << "ERROR: in getKeySize: invalid type" << endl;
        return -100;
    }
}

void IndexManager::setKey(int type,string key)
{
    stringstream ss;
    ss << key;
    if(type == this->TYPE_INT)
        ss >> this->kt.intTmp;
    else if(type == this->TYPE_FLOAT)
        ss >> this->kt.floatTmp;
    else if(type > 0)
        ss >> this->kt.stringTmp;
    else
        cout << "Error: in getKey: invalid type" << endl;

}






