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
#include <string>
using namespace std;



static BufferManager bm;
//**********************TreeNode***************************//
typedef int offsetNumber;

template <typename KeyType>
class TreeNode{
public:
    size_t count; // the count of keys
    TreeNode* parent;
    std::vector <KeyType> keys;
    
    std::vector <TreeNode*> childs;
    std::vector <offsetNumber> vals;
    
    TreeNode* nextLeafNode; //指向下一个叶子节点
    
    bool isLeaf; //是否叶子标识
    

private:
    int degree;
    
public:
    //创建新节点，参数为false表示创建枝干节点，否则为叶子节点
    TreeNode(int degree,bool newLeaf=false);
    ~TreeNode();
    //friend class BPlusTree<KeyType>
    
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


//**********************BplusTree***************************//

template <typename KeyType>
class BPlusTree
{
private:
    typedef TreeNode<KeyType>* Node;

    struct searchNodeParse
    {
        Node pNode; //找到节点的指针
        size_t index; // 节点关键字序号
        bool ifFound; // 是否找到
        
    };
private:
    string fileName;
    Node root;
    Node leafHead; //叶子指针起点
    size_t keyCount; //key数量
    size_t level; //层数
    size_t nodeCount; //节点数
    fileNode* file; // the filenode of this tree
    int keySize; // the size of key
    int degree; // the degree of the tree
    
public:
    BPlusTree(string m_name,int keySize,int degree);
    ~BPlusTree();

    offsetNumber search(KeyType& key); // search the value of specific key
    bool insertKey(KeyType &key,offsetNumber val);
    bool deleteKey(KeyType &key);
    
    void dropTree();
    
    //TODO:processes about disk
    void readFromDiskAll();
    void writtenbackToDiskAll();
    void readFromDisk(blockNode* btmp);

private:
    void init_tree();//初始化树
    bool adjustAfterinsert(Node pNode);
    bool adjustAfterDelete(Node pNode);
    //void deleteNode(Node pNode);
    void findToLeaf(Node pNode,KeyType key,searchNodeParse &snp);
    
//DEBUG
public:
    void debug_print();

    void debug_print_node(Node pNode);


};




#include "BPlusTree_imp.h" // the implement of BPlusTree function

#endif /* defined(__Minisql__BPlusTree__) */
