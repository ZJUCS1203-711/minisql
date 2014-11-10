//
//  BPlusTree.cpp
//  Minisql
//
//  Created by xuyuhao on 14/11/8.
//  Copyright (c) 2014年 xuyuhao. All rights reserved.
//

#include "BPlusTree.h"
#include <iostream>

using namespace std;

//******** The definition of the functions of the class TreeNode **********

template <class KeyType>
TreeNode<KeyType>::TreeNode(size_t m_degree,bool newLeaf):degree(m_degree),count(0),parent(NULL),nextLeafNode(NULL),isLeaf(newLeaf)
{
    for(size_t i = 0;i < degree;i ++)
    {
        childs.push_back(NULL);
        keys.push_back(KeyType());
        vals.push_back(offsetNumber());
    }
    childs.push_back(NULL);
}

template <class KeyType>
TreeNode<KeyType>::~TreeNode()
{}

template <class KeyType>
bool TreeNode<KeyType>::isRoot()
{
    if(parent) return true;
    else return false;
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
        else if(count > 20) // too many keys, binary search
        {
            size_t left = 0, right = count - 1, pos = 0;
            while(right>left)
            {
                pos = (right + left) / 2;
                if(keys[pos] == key)
                {
                    index = pos;
                    return true;
                }
                else if(keys[pos] < key)
                {
                    left = pos + 1;
                }
                else if(keys[pos] > key)
                {
                    right = pos - 1;
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
        } // end binary search
    }
    return false;
}

//TODO: minmumNode只适合偶数度，需要改进
template <class KeyType>
TreeNode<KeyType>* TreeNode<KeyType>::splite(KeyType &key)
{
    size_t minmumNode = (degree - 1) / 2;
    TreeNode* newNode = new TreeNode(this->degree,this->isLeaf);
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
        newNode->parent = this->parent;
        newNode->count = minmumNode;
        this->count = minmumNode;
    }
    return newNode;
}

template <class KeyType>
size_t TreeNode<KeyType>::add(KeyType &key)
{
    if(isLeaf)
    {
        cout << "Error:add(KeyType &key) is a function for nonleaf nodes" << endl;
        return -1;
    }
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
            count ++;
            
            for(size_t i = count + 1;i > index;i --)
                childs[i] = childs[i-1];
            childs[index] = NULL; // this child will link to another node
            
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
            keys[count] = KeyType();
            vals[count] = offsetNumber();
        }
        else // is nonleaf
        {
            for(size_t i = index;i < count-1;i ++)
                keys[i] = keys[i+1];

            for(size_t i = index;i < count;i ++)
                childs[i] = childs[i+1];
            
            keys[count] = KeyType();
            childs[count] = NULL;
        }
    
        count --;
        return true;
    }
}

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

//******** The definition of the functions of the class BplusTree **********










