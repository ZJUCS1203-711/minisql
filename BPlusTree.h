//
//  BPlusTree.h
//  Minisql
//
//  Created by xuyuhao on 14/11/8.
//  Copyright (c) 2014年 xuyuhao. All rights reserved.
//

#ifndef __Minisql__BPlusTree__
#define __Minisql__BPlusTree__
#include <vector>
#include <stdio.h>
#include "BufferManager.h"
#include "Minisql.h"
using namespace std;

//**********************TreeNode***************************//
typedef int offsetNumber;

template <class KeyType>
class TreeNode{
private:
    size_t degree;
    size_t count; // the count of keys
    TreeNode* parent;
    vector <KeyType> keys;
    
    vector <TreeNode*> childs;
    vector <offsetNumber> vals;
    
    TreeNode* nextLeafNode; //指向下一个叶子节点
    
    bool isLeaf; //是否叶子标识
    
public:
    //创建新节点，参数为false表示创建枝干节点，否则为叶子节点
    TreeNode(size_t m_degree,bool newLeaf=false);
    ~TreeNode();
    
//TODO: 测试完之后改为private
public:
    bool isRoot();
    bool search(KeyType key,size_t &index);//查找一个key，返回对应的索引值
    TreeNode* splite(KeyType &key); //分裂节点
    size_t add(KeyType &key); //在枝干插入一个key,返回对应的索引值
    size_t add(KeyType &key,offsetNumber val); //在叶子节点插入一个key,返回对应的索引值
    bool removeAt(size_t index);

public:
    void debug_print();

};


//TODO: 定义b+树
//**********************BplusTree***************************//


#include "BPlusTree_imp.h"
#endif /* defined(__Minisql__BPlusTree__) */
