//
//  IndexManager.h
//  Minisql
//
//  Created by xuyuhao on 14/11/14.
//  Copyright (c) 2014年 xuyuhao. All rights reserved.
//

#ifndef __Minisql__IndexManager__
#define __Minisql__IndexManager__

#include <stdio.h>
#include <map>
#include <string>
#include "BPlusTree.h"

class IndexManager{
private:
    typedef map<string,BPlusTree<int> *> intMap;
    typedef map<string,BPlusTree<string> *> stringMap;
    typedef map<string,BPlusTree<float> *> floatMap;

    int static const TYPE_FLOAT = -1;
    int static const TYPE_INT = 0; // other values mean the size of the char.Eg, 4 means char(4);
    
    intMap indexIntMap;
    stringMap indexStringMap;
    floatMap indexFloatMap;
    
    int getDegree(int type);

public:
    IndexManager();
    ~IndexManager();

    void createIndex(string indexName,int type);
    
    void dropIndex(string indexName,int type);
    
    offsetNumber searchIndex(string indexName,string key,int type);

    void insertIndex(string indexName,string key,offsetNumber blockOffset,int type);
    
    void deleteIndexByKey(string indexName,string key,int type);
};



#endif /* defined(__Minisql__IndexManager__) */
