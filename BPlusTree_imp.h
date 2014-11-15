//
//  BPlusTree.cpp
//  Minisql
//
//  Created by xuyuhao on 14/11/8.
//  Copyright (c) 2014年 xuyuhao. All rights reserved.
//

#ifndef __Minisql__TreeNode__Imp
#define __Minisql__TreeNode__Imp

#include <iostream>
using namespace std;

//******** The definition of the functions of the class TreeNode **********

template <class KeyType>
TreeNode<KeyType>::TreeNode(int m_degree,bool newLeaf):count(0),parent(NULL),nextLeafNode(NULL),isLeaf(newLeaf),degree(m_degree)
{
    for(size_t i = 0;i < degree+1;i ++)
    {
        childs.push_back(NULL);
        keys.push_back(KeyType());
        vals.push_back(offsetNumber());
    }
    childs.push_back(NULL);
}

template <class KeyType>
TreeNode<KeyType>::~TreeNode()
{
    
}


template <class KeyType>
bool TreeNode<KeyType>::isRoot()
{
    if(parent != NULL) return false;
    else return true;
}

template <class KeyType>
bool TreeNode<KeyType>::search(KeyType key,size_t &index)
{
    if(count == 0 ) // no values in the node
    {
        index = 0;
        return false;
    }
    else
    {
        // test if key are beyond the area of the keys array
        if(keys[count-1] < key)
        {
            index = count;
            return false;
        }
        else if(keys[0] > key)
        {
            index = 0;
            return false;
        } // end of test
        else if(count <= 20) // sequential search
        {
            for(size_t i = 0;i < count;i ++)
            {
                if(keys[i] == key)
                {
                    index = i;
                    return true;
                }
                else if(keys[i] < key)
                {
                    continue;
                }
                else if(keys[i] > key)
                {
                    index = i;
                    return false;
                }
            }
        } // end sequential search
        else if(count > 20) // too many keys, binary search. 2* log(n,2) < (1+n)/2
        {
            size_t left = 0, right = count - 1, pos = 0;
            while(right>left+1)
            {
                pos = (right + left) / 2;
                if(keys[pos] == key)
                {
                    index = pos;
                    return true;
                }
                else if(keys[pos] < key)
                {
                    left = pos;
                }
                else if(keys[pos] > key)
                {
                    right = pos;
                }
                
                
                
                
            } // end while
            
            // right == left + 1
            if(keys[left] >= key)
            {
                index = left;
                return (keys[left] == key);
            }
            else if(keys[right] >= key)
            {
                index = right;
                return (keys[right] == key);
            }
            else if(keys[right] < key)
            {
                index = right ++;
                return false;
            }
        } // end binary search
    }
    return false;
}

/**
 * Splite this node to two and the new node will be the next node.
 *
 * @param KeyType & the key reference returns the key that will go to the upper level
 *
 * @return TreeNode *
 *
 */
//TODO: minmumNode只适合奇数度，需要改进
template <class KeyType>
TreeNode<KeyType>* TreeNode<KeyType>::splite(KeyType &key)
{
    size_t minmumNode = (degree - 1) / 2;
    TreeNode* newNode = new TreeNode(degree,this->isLeaf);
    if(newNode == NULL)
    {
        cout << "Problems in allocate momeory of TreeNode in splite node of " << key << endl;
        exit(2);
    }
    
    if(isLeaf) // this is a leaf node
    {
        //TODO: 这里的下标不知道是不是正确，待验证
        key = keys[minmumNode + 1];
        for(size_t i = minmumNode + 1;i < degree;i ++) // copy the right hand of the keys to the new node
        {
            newNode->keys[i-minmumNode-1] = keys[i];
            keys[i] = KeyType();
            newNode->vals[i-minmumNode-1] = vals[i];
            vals[i] = offsetNumber();
        }
        newNode->nextLeafNode = this->nextLeafNode;
        this->nextLeafNode = newNode;
        
        newNode->parent = this->parent;
        newNode->count = minmumNode;
        this->count = minmumNode + 1;
    } // end leaf
    else if(!isLeaf)
    {
        key = keys[minmumNode];
        for(size_t i = minmumNode + 1;i < degree+1;i ++)
        {
            newNode->childs[i-minmumNode-1] = this->childs[i];
            newNode->childs[i-minmumNode-1]->parent = newNode;
            this->childs[i] = NULL;
        }
        for(size_t i = minmumNode + 1;i < degree;i ++)
        {
            newNode->keys[i-minmumNode-1] = this->keys[i];
            this->keys[i] = KeyType();
        }
        this->keys[minmumNode] = KeyType();
        newNode->parent = this->parent;
        newNode->count = minmumNode;
        this->count = minmumNode;
    }
    return newNode;
}

template <class KeyType>
size_t TreeNode<KeyType>::add(KeyType &key)
{
    if(count == 0)
    {
        keys[0] = key;
        count ++;
        return 0;
    }
    else //count > 0
    {
        size_t index = 0; // record the index of the tree
        bool exist = search(key, index);
        if(exist)
        {
            cout << "Error:In add(Keytype &key),key has already in the tree!" << endl;
            exit(3);
        }
        else // add the key into the node
        {
            for(size_t i = count;i > index;i --)
                keys[i] = keys[i-1];
            keys[index] = key;
            
            for(size_t i = count + 1;i > index+1;i --)
                childs[i] = childs[i-1];
            childs[index+1] = NULL; // this child will link to another node
            count ++;

            return index;
        }
    }
}

template <class KeyType>
size_t TreeNode<KeyType>::add(KeyType &key,offsetNumber val)
{
    if(!isLeaf)
    {
        cout << "Error:add(KeyType &key,offsetNumber val) is a function for leaf nodes" << endl;
        return -1;
    }
    if(count == 0)
    {
        keys[0] = key;
        vals[0] = val;
        count ++;
        return 0;
    }
    else //count > 0
    {
        size_t index = 0; // record the index of the tree
        bool exist = search(key, index);
        if(exist)
        {
            cout << "Error:In add(Keytype &key, offsetNumber val),key has already in the tree!" << endl;
            exit(3);
        }
        else // add the key into the node
        {
            for(size_t i = count;i > index;i --)
            {
                keys[i] = keys[i-1];
                vals[i] = vals[i-1];
            }
            keys[index] = key;
            vals[index] = val;
            count ++;
            return index;
        }
    }
}

template <class KeyType>
bool TreeNode<KeyType>::removeAt(size_t index)
{
    if(index > count)
    {
        cout << "Error:In removeAt(size_t index), index is more than count!" << endl;
        return false;
    }
    else
    {
        if(isLeaf)
        {
            for(size_t i = index;i < count-1;i ++)
            {
                keys[i] = keys[i+1];
                vals[i] = vals[i+1];
            }
            keys[count-1] = KeyType();
            vals[count-1] = offsetNumber();
        }
        else // is nonleaf
        {
            for(size_t i = index;i < count-1;i ++)
                keys[i] = keys[i+1];

            for(size_t i = index+1;i < count;i ++)
                childs[i] = childs[i+1];
            
            keys[count-1] = KeyType();
            childs[count] = NULL;
        }
    
        count --;
        return true;
    }
}


//debug
template <class KeyType>
void TreeNode<KeyType>::debug_print()
{
    cout << "############DEBUG for node###############" << endl;

    cout << "Address: " << (void*)this << ",count: " << count << ",Parent: " << (void*)parent << ",isleaf: " << isLeaf << ",nextNode: " << (void*)nextLeafNode << endl;
    cout << "KEYS:{";
    for(size_t i = 0;i < count;i ++)
    {
        cout << keys[i] << " ";
    }
    cout << "}" << endl;
    if(isLeaf)
    {
        cout << "VALS:{";
        for(size_t i = 0;i < count;i ++)
        {
            cout << vals[i] << " ";
        }
        cout << "}" << endl;
    }
    else // nonleaf node
    {
        cout << "CHILDREN:{";
        for(size_t i = 0;i < count + 1;i ++)
        {
            cout << (void*)childs[i] << " ";
        }

        cout << "}" << endl;
    }
    cout << "#############END OF DEBUG IN NODE########"<< endl;
}


//******** The definition of the functions of the class BPlusTree **********



template <class KeyType>
BPlusTree<KeyType>::BPlusTree(string m_name,int keysize,int m_degree):fileName(m_name),keyCount(0),level(0),nodeCount(0),root(NULL),leafHead(NULL),keySize(keysize),file(NULL),degree(m_degree)
{
    init_tree();
    readFromDiskAll();
}

template <class KeyType>
BPlusTree<KeyType>:: ~BPlusTree()
{
    dropTree(root);
}

template <class KeyType>
void BPlusTree<KeyType>::init_tree()
{
    root = new TreeNode<KeyType>(degree,true);
    keyCount = 0;
    level = 1;
    nodeCount = 1;
    leafHead = root;
}

/**
 * Search the node to its leaf level to find the node contains the key
 *
 * @param Node
 * @param KeyType&
 * @param searchNodeParse&
 *
 * @return
 *
 */
template <class KeyType>
void BPlusTree<KeyType>::findToLeaf(Node pNode,KeyType key,searchNodeParse & snp)
{
    size_t index = 0;
    if(pNode->search(key,index)) // find the key in the node
    {
        if(pNode->isLeaf)
        {
            snp.pNode = pNode;
            snp.index = index;
            snp.ifFound = true;
        }
        else // the node is not a leaf, continue search until the leaf level
        {
            pNode = pNode -> childs[index + 1];
            while(!pNode->isLeaf)
            {
                pNode = pNode->childs[0];
            }
            snp.pNode = pNode;
            snp.index = 0;
            snp.ifFound = true;
        }
        
    }
    else // can not find the key in the node
    {
        if(pNode->isLeaf)
        {
            snp.pNode = pNode;
            snp.index = index;
            snp.ifFound = false;
        }
        else
        {
            findToLeaf(pNode->childs[index],key,snp);
        }
    }
}

template <class KeyType>
bool BPlusTree<KeyType>::insertKey(KeyType &key,offsetNumber val)
{
    searchNodeParse snp;
    findToLeaf(root,key,snp);
    if(snp.ifFound)
    {
        cout << "Error:in insert key to index: the duplicated key!" << endl;
        return false;
    }
    else
    {
        snp.pNode->add(key,val);
        if(snp.pNode->count == degree)
        {
            adjustAfterinsert(snp.pNode);
        }
        keyCount ++;
        return true;
    }
}

template <class KeyType>
bool BPlusTree<KeyType>::adjustAfterinsert(Node pNode)
{
    KeyType key;
    Node newNode = pNode->splite(key);
    nodeCount ++;
    
    if(pNode->isRoot()) // the node is the root
    {
        Node root = new TreeNode<KeyType>(degree,false);
        if(root == NULL)
        {
            cout << "Error: can not allocate memory for the new root in adjustAfterinsert" << endl;
            exit(1);
        }
        else
        {
            level ++;
            nodeCount ++;
            this->root = root;
            pNode->parent = root;
            newNode->parent = root;
            root->add(key);
            root->childs[0] = pNode;
            root->childs[1] = newNode;
            return true;
        }
    }// end root
    else // if it is not the root
    {
        Node parent = pNode->parent;
        size_t index = parent->add(key);
        
        parent->childs[index+1] = newNode;
        newNode->parent = parent;
        if(parent->count == degree)
            return adjustAfterinsert(parent);
        
        return true;
    }
}

/**
 * Search the tree to find the value of specific key
 *
 * @param KeyType&
 *
 * @return offsetnumber. The value of the key, -1 means not found in the tree
 *
 */
template <class KeyType>
offsetNumber BPlusTree<KeyType>::search(KeyType& key)
{
    if(!root) return -1;
    searchNodeParse snp;
    findToLeaf(root, key, snp);
    if(!snp.ifFound)
    {
        return -1; // Don't find the key in the tree;
    }
    else
    {
        return snp.pNode->vals[snp.index];
    }
    
}

template <class KeyType>
bool BPlusTree<KeyType>::deleteKey(KeyType &key)
{
    searchNodeParse snp;
    if(!root)
    {
        cout << "ERROR: In deleteKey, no nodes in the tree " << fileName << "!" << endl;
        return false;
    }
    else
    {
        findToLeaf(root, key, snp);
        if(!snp.ifFound)
        {
            cout << "ERROR: In deleteKey, no keys in the tree " << fileName << "!" << endl;
            return false;
        }
        else // find the key in the leaf node
        {
            if(snp.pNode->isRoot())
            {
                snp.pNode->removeAt(snp.index);
                keyCount --;
                return adjustAfterDelete(snp.pNode);
            }
            else
            {
                if(snp.index == 0 && leafHead != snp.pNode) // the key exist in the branch.
                {
                    // go to upper level to update the branch level
                    size_t index = 0;
                    
                    //TODO:在这里degree = 3 时有点问题
                    Node now_parent = snp.pNode->parent;
                    bool if_found_inBranch = now_parent->search(key,index);
                    while(!if_found_inBranch)
                    {
                        if(now_parent->parent)
                            now_parent = now_parent->parent;
                        else
                        {
                            break;
                        }
                        if_found_inBranch = now_parent->search(key,index);
                    }// end of search in the branch
                     
                    now_parent -> keys[index] = snp.pNode->keys[1];
                    
                    snp.pNode->removeAt(snp.index);
                    keyCount--;
                    return adjustAfterDelete(snp.pNode);
                    
                }
                else //this key must just exist in the leaf too.
                {
                    snp.pNode->removeAt(snp.index);
                    keyCount--;
                    return adjustAfterDelete(snp.pNode);
                }
            }
        }
    }
}

template <class KeyType>
bool BPlusTree<KeyType>::adjustAfterDelete(Node pNode)
{
    size_t minmumKey = (degree - 1) / 2;
    if(((pNode->isLeaf)&&(pNode->count >= minmumKey)) || ((degree != 3)&&(!pNode->isLeaf)&&(pNode->count >= minmumKey - 1)) || ((degree ==3)&&(!pNode->isLeaf)&&(pNode->count < 0))) // do not need to adjust
    {
        return  true;
    }
    if(pNode->isRoot())
    {
        cout << "if root" << endl;
        if(pNode->count > 0) //do not need to adjust
        {
            return true;
        }
        else
        {
            if(root->isLeaf) //the true will be an empty tree
            {
                cout << "if(root->isLeaf) //the true will be an empty tree" << endl;
                delete pNode;
                root = NULL;
                leafHead = NULL;
                level --;
                nodeCount --;
            }
            else // root will be the leafhead
            {
                cout << "else // root will be the leafhead" << endl;
                root = pNode -> childs[0];
                root -> parent = NULL;
                delete pNode;
                level --;
                nodeCount --;
            }
        }
    }// end root
    else
    {
        Node parent = pNode->parent,brother = NULL;
        if(pNode->isLeaf)
        {
            cout << "if1 if(pNode->isLeaf)" << endl;
            size_t index = 0;
            parent->search(pNode->keys[0],index);
            cout << "index:" << index << endl;

            if((parent->childs[0] != pNode) && (index + 1 == parent->count)) //choose the left brother to merge or replace
            {
                cout << "if(index + 1 == parent->count) //choose the left brother to merge or replace" << endl;
                brother = parent->childs[index];
                if(brother->count > minmumKey) // choose the most right key of brother to add to the left hand of the pnode
                {
                    cout << "if(brother->count > minmumKey) // choose the most right key of brother to add to the left hand of the pnode?" << endl;
                    for(size_t i = pNode->count;i > 0;i --)
                    {
                        pNode->keys[i] = pNode->keys[i-1];
                        pNode->vals[i] = pNode->vals[i-1];
                    }
                    pNode->keys[0] = brother->keys[brother->count-1];
                    pNode->vals[0] = brother->vals[brother->count-1];
                    brother->removeAt(brother->count-1);
                    
                    pNode->count ++;
                    parent->keys[index] = pNode->keys[0];
                    return true;
                    
                } // end add
                else // merge the node with its brother
                {
                    cout << "else // merge the node with its brother" << endl;
                    parent->removeAt(index);
                    
                    for(int i = 0;i < pNode->count;i ++)
                    {
                        brother->keys[i+brother->count] = pNode->keys[i];
                        brother->vals[i+brother->count] = pNode->vals[i];
                    }
                    brother->count += pNode->count;
                    brother->nextLeafNode = pNode->nextLeafNode;
                    
                    delete pNode;
                    nodeCount --;
                    
                    return adjustAfterDelete(parent);
                }// end merge
            
            }// end of the left brother
            else // choose the right brother
            {
                cout << "else // choose the right brother" << endl;
                if(parent->childs[0] == pNode)
                    brother = parent->childs[1];
                else
                    brother = parent->childs[index+2];
                if(brother->count > minmumKey)//// choose the most left key of brother to add to the right hand of the node
                {
                    cout << "if(brother->count > minmumKey)//// choose the most left key of brother to add to the right hand of the node" << endl;
                    pNode->keys[pNode->count] = brother->keys[0];
                    pNode->vals[pNode->count] = brother->vals[0];
                    pNode->count ++;
                    brother->removeAt(0);
                    if(parent->childs[0] == pNode)
                        parent->keys[0] = brother->keys[0];
                    else
                        parent->keys[index+1] = brother->keys[0];
                    return true;
                    
                }// end add
                else // merge the node with its brother
                {
                    cout << "brother->count:" << brother->count << endl;
                    cout << "else // merge the node with its brother " << endl;
                    for(int i = 0;i < brother->count;i ++)
                    {
                        pNode->keys[pNode->count+i] = brother->keys[i];
                        pNode->vals[pNode->count+i] = brother->vals[i];
                    }
                    if(pNode == parent->childs[0])
                        parent->removeAt(0);
                    else
                        parent->removeAt(index+1);
                    pNode->count += brother->count;
                    pNode->nextLeafNode = brother->nextLeafNode;
                    delete brother;
                    nodeCount --;
                    
                    return adjustAfterDelete(parent);
                }//end merge
            }// end of the right brother

        }// end leaf
        else // branch node
        {
            cout << "else1  // branch node" << endl;
            size_t index = 0;
            parent->search(pNode->childs[0]->keys[0],index);
            if((parent->childs[0] != pNode) && (index + 1 == parent->count)) // choose the left brother to merge or replace
            {
                cout << "if(index == parent->count) // choose the left brother to merge or replace" << endl;
                brother = parent->childs[index];
                if(brother->count > minmumKey - 1) // choose the most right key and child to add to the left hand of the pnode
                {
                    //modify the pnode
                    pNode->childs[pNode->count+1] = pNode->childs[pNode->count];
                    for(size_t i = pNode->count;i > 0;i --)
                    {
                        pNode->childs[i] = pNode->childs[i-1];
                        pNode->keys[i] = pNode->keys[i-1];
                    }
                    pNode->childs[0] = brother->childs[brother->count];
                    pNode->keys[0] = parent->keys[index];
                    pNode->count ++;
                    //modify the father
                    parent->keys[index]= brother->keys[brother->count-1];
                    //modify the brother and child
                    if(brother->childs[brother->count])
                    {
                        brother->childs[brother->count]->parent = pNode;
                    }
                    brother->removeAt(brother->count-1);
                   
                    return true;
                    
                }// end add
                else // merge the node with its brother
                {
                    cout << " else // merge the node with its brother"<< endl;
                    //modify the brother and child
                    brother->keys[brother->count] = parent->keys[index];
                    parent->removeAt(index);
                    brother->count ++;
                    
                    for(int i = 0;i < pNode->count;i ++)
                    {
                        brother->childs[brother->count+i] = pNode->childs[i];
                        brother->keys[brother->count+i] = pNode->keys[i];
                        brother->childs[brother->count+i]-> parent= brother;
                    }
                    brother->childs[brother->count+pNode->count] = pNode->childs[pNode->count];
                    brother->childs[brother->count+pNode->count]->parent = brother;
                    
                    brother->count += pNode->count;
                    
                    
                    delete pNode;
                    nodeCount --;
                    
                    return adjustAfterDelete(parent);
                }
                
            }// end of the left brother
            else // choose the right brother
            {
                cout << "else // choose the right brother" << endl;
                if(parent->childs[0] == pNode)
                    brother = parent->childs[1];
                else
                    brother = parent->childs[index+2];
                if(brother->count > minmumKey - 1)// choose the most left key and child to add to the right hand of the pnode
                {
                    //modifty the pnode and child
                    pNode->childs[pNode->count+1] = brother->childs[0];
                    pNode->keys[pNode->count] = brother->keys[0];
                    pNode->childs[pNode->count+1]->parent = pNode;
                    pNode->count ++;
                    //modify the fater
                    if(pNode == parent->childs[0])
                        parent->keys[0] = brother->keys[0];
                    else
                        parent->keys[index+1] = brother->keys[0];
                    //modify the brother
                    brother->childs[0] = brother->childs[1];
                    brother->removeAt(0);
                    
                    return true;
                }
                else // merge the node with its brother
                {
                    cout << "else // merge the node with its brother" << endl;
                    //modify the pnode and child
                    pNode->keys[pNode->count] = parent->keys[index];

                    if(pNode == parent->childs[0])
                        parent->removeAt(0);
                    else
                        parent->removeAt(index+1);

                    pNode->count ++;
                    
                    for(int i = 0;i < brother->count;i++)
                    {
                        pNode->childs[pNode->count+i] = brother->childs[i];
                        pNode->keys[pNode->count+i] = brother->keys[i];
                        pNode->childs[pNode->count+i]->parent = pNode;
                    }
                    pNode->childs[pNode->count+brother->count] = brother->childs[brother->count];
                    pNode->childs[pNode->count+brother->count]->parent = pNode;
                    
                    pNode->count += brother->count;
                    
                    
                    delete brother;
                    nodeCount --;
                    
                    return adjustAfterDelete(parent);
                    
                }
                
            }
        
        }
        
    }
    return false;
}

template <class KeyType>
void BPlusTree<KeyType>::dropTree(Node node)
{
    //TODO:删除每一个node
    if(!node->isLeaf) //if it has child
    {
        for(size_t i=0;i <= node->count;i++)
        {
            dropTree(node->childs[i] );
            node->childs[i] = NULL;
        }
    }
    delete node;
    nodeCount --;
    return;
}

template <class KeyType>
void BPlusTree<KeyType>::readFromDiskAll()
{
    file = bm.getFile(fileName.c_str());
    blockNode* btmp = bm.getBlockHead(file);
    while (true)
    {
        if (btmp == NULL)
        {
            return;
        }
        
        readFromDisk(btmp);
        if(btmp->ifbottom) break;
        btmp = bm.getNextBlock(file, btmp);
    }
    
}

template <class KeyType>
void BPlusTree<KeyType>::readFromDisk(blockNode* btmp)
{
    cout << "in read from disk" << endl;
    int valueSize = sizeof(offsetNumber);
    char* indexBegin = bm.get_content(*btmp);
    char* valueBegin = indexBegin + keySize;
    KeyType key;
    offsetNumber value;
    
    while(valueBegin - bm.get_content(*btmp) < bm.get_usingSize(*btmp))
    // there are available position in the block
    {
        cout << "in while" << endl;
        key = *(KeyType*)indexBegin;
        value = *(offsetNumber*)valueBegin;
        cout << "insert what:" << key << "***************" << "value:" << value << endl;
        insertKey(key, value);
        valueBegin += keySize + valueSize;
        indexBegin += keySize + valueSize;
    }
    cout << "out read from disk" << endl;
    
}

template <class KeyType>
void BPlusTree<KeyType>::writtenbackToDiskAll()
{
    cout << "In the written back to disk" << endl;
    cout << file->fileName << endl;
    blockNode* btmp = bm.getBlockHead(file);
    Node ntmp = leafHead;
    cout << ntmp << " " << ntmp->count << endl;
    int valueSize = sizeof(offsetNumber);
    while(ntmp != NULL)
    {
        bm.set_usingSize(*btmp, 0);
        bm.set_dirty(*btmp);
        for(int i = 0;i < ntmp->count;i ++)
        {
            cout << "in write" << endl;
            cout << "write what : " << ntmp->keys[i] << " keysize:" << keySize << " value:" << ntmp->vals[i] << "---------"<<endl;
            char* key = (char*)&(ntmp->keys[i]);
            char* value = (char*)&(ntmp->vals[i]);
            memcpy(bm.get_content(*btmp)+bm.get_usingSize(*btmp),key,keySize);
            bm.set_usingSize(*btmp, bm.get_usingSize(*btmp) + keySize);
            memcpy(bm.get_content(*btmp)+bm.get_usingSize(*btmp),value,valueSize);
            bm.set_usingSize(*btmp, bm.get_usingSize(*btmp) + valueSize);
        }
        
        btmp = bm.getNextBlock(file, btmp);
        ntmp = ntmp->nextLeafNode;
    }
    while(1)// delete the empty node
    {
        if(btmp->ifbottom)
            break;
        bm.set_usingSize(*btmp, 0);
        bm.set_dirty(*btmp);
        btmp = bm.getNextBlock(file, btmp);

    }
    cout << "Out the written back to disk" << endl;

    
    fileNode* ftmp = bm.getFile(file->fileName);
    blockNode* b2 =  bm.getBlockHead(ftmp);
    char * lim = bm.get_content(*b2);
    cout << "key " << *((float*)lim) << "value " << *((offsetNumber*)(lim+sizeof(float))) << endl;
}

//debug
template <class KeyType>
void BPlusTree<KeyType>::debug_print()
{
    cout << "############DEBUG FOR THE TREE############" << endl;
    cout << "name:" << fileName << " root:" << (void*)root << " leafHead:" << (void * )leafHead << " keycount:" << keyCount << " level:" << level << " nodeCount:" << nodeCount << endl;
    
    if(root)
        debug_print_node(root);
    cout << "#############END OF DEBUG FOR TREE########" << endl;
    
}

template <class KeyType>
void BPlusTree<KeyType>::debug_print_node(Node pNode)
{
    pNode->debug_print();
    if(!pNode->isLeaf)
        for(int i = 0 ;i < pNode->count+1;i ++)
            debug_print_node(pNode->childs[i]);
    
}



#endif /* defined(__Minisql__TreeNode__Imp) */


























