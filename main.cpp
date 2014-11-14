#include<iostream>
#include "Interpreter.h"
#include <fstream>
int main(int argc,char * argv[])
{
    cout<<"*******************Welcome to use our MiniSQL**********************"<<endl;
    cout<<"******************* Author: Deng & Xu & Woo **********************"<<endl;
    int fileRead = 0;
    //string fileName ="";
    ifstream file;
    Interpreter in;
    string s;
    while(1)
    {
        if(fileRead)
        {
            file.open(in.fileName.c_str());
            if(!file.is_open())
            {
                cout<<"Fail to open "<<in.fileName<<endl;
                fileRead = 0;
                continue;
            }
            while(getline(file,s,';'))
            {
                in.interpreter(s);
            }
            fileRead = 0;
        }
        else
        {

            cout<<"minisql>>";
            getline(cin,s,';');

            if(in.interpreter(s)==2)
            {
                fileRead = 1;
            }
        }

    }
    return 1;
}
