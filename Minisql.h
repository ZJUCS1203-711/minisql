//
//  Minisql.h
//  Minisql
//
//  Created by xuyuhao on 14/11/2.
//  Copyright (c) 2014年 xuyuhao. All rights reserved.
//

#ifndef Minisql_Minisql_h
#define Minisql_Minisql_h
#include <stdio.h>

struct blockNode
{
    int offsetNum; // the offset number in the block list
    bool pin;  // the flag that this block is locked
    char *address; // the content address
    bool ifbottom; // flag that this is the end of the file node
    char* fileName; // the file which the block node belongs to
    friend class BufferManager;
    
private:
    blockNode * preBlock;
    bool reference; // the LRU replacement flag
    bool dirty; // the flag that this block is dirty, which needs to written back to the disk later
    blockNode * nextBlock;
    size_t using_size; // the byte size that the block have used. The total size of the block is BLOCK_SIZE

};

struct fileNode
{
    char *fileName;
    bool pin; // the flag that this file is locked
    blockNode *blockHead;
    fileNode * nextFile;
    fileNode * preFile;
};

#define MAX_FILE_NUM 40
#define MAX_BLOCK_NUM 100
#define BLOCK_SIZE 8192
#define MAX_FILE_NAME 30

#endif
