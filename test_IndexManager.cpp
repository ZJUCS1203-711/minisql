//
//  test_IndexManager.cpp
//  Minisql
//
//  Created by xuyuhao on 14/11/9.
//  Copyright (c) 2014年 xuyuhao. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include "API.h"
#include "CatalogManager.h"
#include "BPlusTree.h"
#include "IndexManager.h"
#include <stdlib.h>
#include "Attribute.h"
/*
void test_node()
{
    TreeNode<int> x = TreeNode<int>(10,true);
    for(size_t i = 0;i < 10;i ++)
    {
        int a = (int)i + 1;
        size_t index = x.add(a, a*10);
    }
    
    x.debug_print();
    int a= 0;
    TreeNode<int> *y = x.splite(a);
    x.debug_print();
    y->debug_print();
    cout << "a: " << a <<  endl;
    
}
*/

void test_tree()
{
    /*
    
    BPlusTree<int> x("Student");
    vector<int> a;
    vector<offsetNumber> b;
    int pool[] = {33,1,5,3,9,19,22,32,100,200,400,300,240,140,160,130,2000,44,88,99,333,555,55,66,123,312,321,101,245,299,290,230,1010,1130,1400,1500,2444};
    int num = 30;
    for(int i = 0;i < num;i ++)
    {
        a.push_back(pool[i]);
        b.push_back(i*2);
    }
    
    for(int i = 0;i < num;i ++)
    {
        cout << "插入" << a[i] << "时" << endl;
        x.insertKey(a[i], b[i]);
      //  x.debug_print();
    }
    
    int s1=100,s2=10000,p1=33,p2=9,p3 = 19,p4=140;
    cout << "searchkey:100:" <<x.search(s1) << endl;
    cout << "searchkey:10000:" << x.search(s2) << endl;
    cout << "searchkey:33:" << x.search(p1) << endl;
    cout << "searchkey:9:" << x.search(p2) << endl;
    cout << "searchkey:19:" << x.search(p3) << endl;
    cout << "searchkey:140:" << x.search(p4) << endl;
    

    x.debug_print();

    cout << endl << endl << "***********TEST DELETION************" << endl;
    
     // test case 1
    cout << "删100" <<endl;
    x.deleteKey(s1);
    x.debug_print();
    int s3 = 130,s4=1,s5=9;
    
    cout << "删130" <<endl;
    x.deleteKey(s3);
    x.debug_print();
    
    cout << "删1" << endl;
    x.deleteKey(s4);
    x.debug_print();
    
    cout << "删9" << endl;
    x.deleteKey(s5);
    x.debug_print();
    
    cout << "删160"<< endl;
    int q1 = 160,q2 = 300,q3 = 2000;
    x.deleteKey(q1);
    x.debug_print();
    
    cout << "删300" << endl;
    x.deleteKey(q2);
    x.debug_print();
    
    cout << "删2000" << endl;
    x.deleteKey(q3);
    x.debug_print();
    
    cout << "删240" << endl;
    int q4 = 240;
    x.deleteKey(q4);
    x.debug_print();
    
    cout << "删19" << endl;
    int q5 = 19;
    x.deleteKey(q5);
    x.debug_print();
    
    cout << "删22" << endl;
    int q6 = 22;
    x.deleteKey(q6);
    x.debug_print();
    
    // 正确
    cout << "删400" << endl;
    int q7 = 400;
    x.deleteKey(q7);
    x.debug_print();
    
    // 正确
    cout << "删200" << endl;
    int q8 = 200;
    x.deleteKey(q8);
    
    x.debug_print();
    cout << "删3" << endl;
    int q9 = 3;
    x.deleteKey(q9);
    x.debug_print();
    
    cout << "删33" << endl;
    int q10 = 33;
    x.deleteKey(q10);
    x.debug_print();
    
    cout << "删140" << endl;
    int q11 = 140;
    x.deleteKey(q11);
    x.debug_print();
    
    cout << "删32" << endl;
    int q12 = 32;
    x.deleteKey(q12);
    x.debug_print();
    
    cout << "删5" << endl;
    int q13 = 5;
    x.deleteKey(q13);
    x.debug_print();
     */
    
    
    //test case 2
    /*
    cout << "删100" <<endl;
    x.deleteKey(s1);
    x.debug_print();
    int s3 = 19,s4=1,s5=140;
    
    cout << "删19" <<endl;
    x.deleteKey(s3);
    x.debug_print();
    
    cout << "删1" << endl;
    x.deleteKey(s4);
    x.debug_print();
    
    cout << "删140" << endl;
    x.deleteKey(s5);
    x.debug_print();
    
    cout << "删160"<< endl;
    int q1 = 160,q2 = 300,q3 = 2000;
    x.deleteKey(q1);
    x.debug_print();
    
    cout << "删300" << endl;
    x.deleteKey(q2);
    x.debug_print();
    
    cout << "删2000" << endl;
    x.deleteKey(q3);
    x.debug_print();
    
    cout << "删240" << endl;
    int q4 = 240;
    x.deleteKey(q4);
    x.debug_print();
    
    cout << "删130" << endl;
    int q5 = 130;
    x.deleteKey(q5);
    x.debug_print();
    
    cout << "删22" << endl;
    int q6 = 22;
    x.deleteKey(q6);
    x.debug_print();
    
    // 正确
    cout << "删400" << endl;
    int q7 = 400;
    x.deleteKey(q7);
    x.debug_print();
    
    // 正确
    cout << "删200" << endl;
    int q8 = 200;
    x.deleteKey(q8);
    
    x.debug_print();
    cout << "删3" << endl;
    int q9 = 3;
    x.deleteKey(q9);
    x.debug_print();
    
    cout << "删33" << endl;
    int q10 = 33;
    x.deleteKey(q10);
    x.debug_print();
    
    cout << "删9" << endl;
    int q11 = 9;
    x.deleteKey(q11);
    x.debug_print();
    
    cout << "删32" << endl;
    int q12 = 32;
    x.deleteKey(q12);
    x.debug_print();
    
    cout << "删5" << endl;
    int q13 = 5;
    x.deleteKey(q13);
    x.debug_print();
    */
    
   /*
    
    //test case 3
    BPlusTree<int> x("Student");
    vector<int> a;
    vector<offsetNumber> b;
    int pool[] = {1444,1,5,3,555,19,290,32,100,200,66,300,240,1400,160,130,1000,44,88,99,333,9,55,400,123,312,321,101,245,299,22,230,1010,1130,170,1500,33};
    int num = 20;
    for(int i = 0;i < num;i ++)
    {
        a.push_back(pool[i]);
        b.push_back(i*2);
    }
    
    for(int i = 0;i < num;i ++)
    {
        cout << "插入" << a[i] << "时" << endl;
        x.insertKey(a[i], b[i]);
        //  x.debug_print();
    }
    
    int s1=100,s2=10000,p1= 1444,p2 = 555, p3 = 300;
    cout << "searchkey:100:" <<x.search(s1) << endl;
    cout << "searchkey:10000:" << x.search(s2) << endl;
    cout << "searchkey:1444:" << x.search(p1) << endl;
    cout << "serachkey:555:" << x.search(p2) << endl;
    cout << "searchkey>:300:" << x.search(p3) << endl;
    cout << endl << endl << "***********TEST DELETION************" << endl;
    
    x.debug_print();

    
    // test case 1
    cout << "删100" <<endl;
    x.deleteKey(s1);
    x.debug_print();
    int s3 = 130,s4=1,s5=9;
    
    cout << "删130" <<endl;
    x.deleteKey(s3);
    x.debug_print();
    
    cout << "删1" << endl;
    x.deleteKey(s4);
    x.debug_print();
    
    cout << "删9" << endl;
    x.deleteKey(s5);
    x.debug_print();
    
    cout << "删160"<< endl;
    int q1 = 160,q2 = 300,q3 = 1500;
    x.deleteKey(q1);
    x.debug_print();
    
    cout << "删300" << endl;
    x.deleteKey(q2);
    x.debug_print();
    
    cout << "删1500" << endl;
    x.deleteKey(q3);
    x.debug_print();
    
    cout << "删240" << endl;
    int q4 = 240;
    x.deleteKey(q4);
    x.debug_print();
    
    cout << "删19" << endl;
    int q5 = 19;
    x.deleteKey(q5);
    x.debug_print();
    
    cout << "删22" << endl;
    int q6 = 22;
    x.deleteKey(q6);
    x.debug_print();
    
    // 正确
    cout << "删400" << endl;
    int q7 = 400;
    x.deleteKey(q7);
    x.debug_print();
    
    // 正确
    cout << "删200" << endl;
    int q8 = 200;
    x.deleteKey(q8);
    
    x.debug_print();
    cout << "删3" << endl;
    int q9 = 3;
    x.deleteKey(q9);
    x.debug_print();
    
    cout << "删33" << endl;
    int q10 = 33;
    x.deleteKey(q10);
    x.debug_print();
    
    cout << "删312" << endl;
    int q11 = 312;
    x.deleteKey(q11);
    x.debug_print();
    
    cout << "删32" << endl;
    int q12 = 32;
    x.deleteKey(q12);
    x.debug_print();
    
    cout << "删5" << endl;
    int q13 = 5;
    x.deleteKey(q13);
    x.debug_print();
    */
/*
    //test case4
    BPlusTree<string> x("Student");
    vector<string> a;
    vector<offsetNumber> b;
    string pool[] = {"Ibb","asf","xcv","wre","ads","xcv","xie","qwe","abc","def","gck","iop","poi"};
    int num = 13;
    for(int i = 0;i < num;i ++)
    {
        a.push_back(pool[i]);
        b.push_back(i*2);
    }
    
    for(int i = 0;i < num;i ++)
    {
        cout << "插入" << a[i] << "时" << endl;
        x.insertKey(a[i], b[i]);
        //  x.debug_print();
    }
    x.debug_print();
    cout << "删Ibb" << endl;
    string q12 = "Ibb";
    x.deleteKey(q12);
    x.debug_print();
    
    cout << "删ads" << endl;
    string q13 = "ads";
    x.deleteKey(q13);
    x.debug_print();
    
    */
    /*
    //test case 5 for disk int
    cout << "test for read and write" << endl;
    BPlusTree<int> x("Consumer", sizeof(int));
    x.debug_print();
    
    vector<int> a;
    vector<offsetNumber> b;
    int pool[] = {33,1,5,3,9,19,22,32,100,200,400,300,240,140,160,130,2000,44,88,99,333,555,55,66,123,312,321,101,245,299,290,230,1010,1130,1400,1500,2444};
    int num = 33;
    for(int i = 0;i < num;i ++)
    {
        a.push_back(pool[i]);
        b.push_back(i*2);
    }
    for(int i = 0;i < num;i ++)
    {
        cout << "插入" << a[i] << "时" << endl;
        x.insertKey(a[i], b[i]);
        //  x.debug_print();
    }
    x.debug_print();
    x.writtenbackToDiskAll();
     */
    
    /*
    //test case 6 for float
    cout << "test for read and write" << endl;
    BPlusTree<float> x("Consumer", sizeof(float));
    x.debug_print();
    
    
    vector<float> a;
    vector<offsetNumber> b;
    float pool[] = {33,1,5,3,9,19,22,32,100,200,400,300,240,140,160,130,2000,44,88,99,333,555,55,66,123,312,321,101,245,299,290,230,1010,1130,1400,1500,2444};
    int num = 33;
    for(int i = 0;i < num;i ++)
    {
        a.push_back(pool[i]);
        b.push_back(i*2);
    }
    for(int i = 0;i < num;i ++)
    {
        cout << "插入" << a[i] << "时" << endl;
        x.insertKey(a[i], b[i]);
        //  x.debug_print();
    }
    x.debug_print();
    x.writtenbackToDiskAll();
*/
    
    /*
    //test case 7 for string
    cout << "test for read and write" << endl;
    BPlusTree<string> x("Consumer", 5, 5);
    x.debug_print();
    
    
    vector<string> a;
    vector<offsetNumber> b;
    string pool[] = {"adbc","qwdr","zxdv","qerr","poiu","oiuy","iuyt","uytr","ytre","trew","hjkl","ghjk","fghj","dfgh","sdfg","asdf","vcxz","bvcx","nbvc","mnbv"};
    int num = 10;
    for(int i = 0;i < num;i ++)
    {
        a.push_back(pool[i]);
        b.push_back(i*2);
    }
    for(int i = 0;i < num;i ++)
    {
        cout << "插入" << a[i] << "时" << endl;
        x.insertKey(a[i], b[i]);
        //  x.debug_print();
    }
    x.debug_print();
    string a1 = "qwdr", a2 = "qerr";
    cout << "搜qwdr:" << x.search(a1) << "搜qerr:" << x.search(a2) << endl;
    x.writtenbackToDiskAll();
   */
    
    
    //test case 8 for multipy key
    BPlusTree<string> x("Student", 4, 5);


    vector<string> a;
    vector<offsetNumber> b;
    string pool[] = {"adbc","qwdr","zxdv","qerr","poiu","oiuy","iuyt","uytr","ytre","trew","hjkl","ghjk","fghj","dfgh","sdfg","asdf","vcxz","bvcx","nbvc","mnbv","qazw","azws","sxed","xedc","dcrf","fvtg","gbyh","hnuj","jmik","olik","ujyh","tgrf","edws","wsqa","zxdr","zxcf","zxcg","zxch","xcvg","bnjk"};
    int num = 40;
    
    for(int i = 0;i < num;i ++)
    {
        a.push_back(pool[i]);
        b.push_back(i*2);
    }
    
    for(int i = 0;i < num;i ++)
    {
        cout << "插入" << a[i] << "时" << endl;
        x.insertKey(a[i], b[i]);
    //    x.debug_print();
    }
    /*
    for(int i = 20;i < num;i ++)
        x.deleteKey(a[i]);
    */
    for(int i = 0;i < 20;i ++)
    {
        cout << "search " << a[i] << ": " << x.search(a[i]) << endl;
    }
    x.debug_print();
    
    
}
/*
void testIndex()
{
    
    IndexManager im;
    
 
    // test case 1
    im.createIndex("Student", Attribute::TYPE_INT);
    cout << im.searchIndex("Student", "12" ,Attribute::TYPE_INT) << endl;
    im.insertIndex("Student", "12", 0, Attribute::TYPE_INT);
    cout << im.searchIndex("Student", "12" ,Attribute::TYPE_INT) << endl;
    im.deleteIndexByKey("Student", "12", Attribute::TYPE_INT);
    cout << im.searchIndex("Student", "12" ,Attribute::TYPE_INT) << endl;
    */
 /*
    im.createIndex("Customer", 4);
  //  cout <<  "search for 'abc':" << im.searchIndex("Customer", "abc", 4) << endl;

    
    vector<string> a;
    vector<offsetNumber> b;
    string pool[] = {"adbc","qwdr","zxdv","qerr","poiu","oiuy","iuyt","uytr","ytre","trew","hjkl","ghjk","fghj","dfgh","sdfg","asdf","vcxz","bvcx","nbvc","mnbv","qazw","azws","sxed","xedc","dcrf","fvtg","gbyh","hnuj","jmik","olik","ujyh","tgrf","edws","wsqa","zxdr","zxcf","zxcg","zxch","xcvg","bnjk"};
    int num = 40;
    
    
    for(int i = 0;i < num;i ++)
    {
        a.push_back(pool[i]);
        b.push_back(i*2);
    }
    
    for(int i = 0;i < num;i ++)
    {
        cout << "插入" << a[i] << "时" << endl;
        
     //   im.insertIndex("Customer", a[i], b[i], 4);
    }
    
    for(int i = 20;i < 40;i ++)
    {
    //    im.deleteIndexByKey("Customer", a[i], 4);
    }

    
    for(int i = 0;i < num;i ++)
    {
        cout << "search " << a[i] << ": " << im.searchIndex("Customer", a[i], 4) << endl;
    }
    
  
    cout << "delete 前：" << im.searchIndex("Customer", "qerr", 3) << endl;
    im.deleteIndexByKey("Customer", "qerr", 3);
    cout << "delete 后：" << im.searchIndex("Customer", "qerr", 3) << endl;
    cout << "搜索mnbv：" << im.searchIndex("Customer","mnbv",3) << endl;
    cout << "搜索dfgh：" << im.searchIndex("Customer","dfgh",3) << endl;
     */
    
   /*
    
}
*/
/*
int main()
{
   // test_node();
   // test_tree();
    API api;
    CatalogManager cm;
    api.cm = &cm;
    
    
    testIndex();
    
    return 0;
}
*/





