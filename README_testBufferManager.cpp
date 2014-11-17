//
//  main.cpp
//  Minisql
//
//  Created by xuyuhao on 14/10/29.
//  Copyright (c) 2014年 xuyuhao. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include "Minisql.h"
#include "BufferManager.h"
using namespace std;

int test_bufferManager(){
    cout << "这里是BufferManager的示例程序，正式使用时请删除本程序！" << endl;
    BufferManager bm;
    const char* fileName = "Student";
    
    
    fileNode *ftmp =  bm.getFile(fileName); // 获得文件节点
    blockNode *btmp = bm.getBlockHead(ftmp ); //获得文件节点的首个block节点
    
    /*
     if you want to lock the block node , you must also lock the file node.
     bm.set_pin(*btmp, true );
     bm.set_pin(*ftmp, true );
     */
    
    cout << "第一个block中的using_size " << bm.get_usingSize(*btmp) << endl;
    
    cout << "====begin===" << endl;
    
    int test = 100;
    char* test2 = (char*)&test;
    
    int recordLen = sizeof(test);
    while(1)
    {
        if(bm.get_usingSize(*btmp) <= bm.getBlockSize() - recordLen)
        {
            cout << "如果需要修改这个block，请使用set_dirty函数,如：bm.set_dirty(*btmp)" << endl;
            bm.set_dirty(*btmp);
            
            cout << "修改该block前, using_size:" << bm.get_usingSize(*btmp) << endl;
            strncpy(bm.get_content(*btmp)+bm.get_usingSize(*btmp), test2, recordLen);
            cout << "修改之后，请更改该block的using_size，如：btmp->using_size += recordLen" << endl;
            bm.set_usingSize(*btmp, bm.get_usingSize(*btmp)+recordLen);
            
            cout << "btmp -> fileName: " << btmp->fileName << endl;
            
            cout << "修改该block后, using_size:" << bm.get_usingSize(*btmp) << endl;
      
            break;
        }
        else
        {
            cout << "发现在上一个block中没有空余字节，获得下一个block，如：btmp = bm.getNextBlock(fileName, btmp)" << endl;
            btmp = bm.getNextBlock(ftmp, btmp);
        }
    }
    cout << "====exit==="<< endl;
    return 1;
}
/*
int main()
{
    test_bufferManager();
    return 0;
}
 */

