/************************些文件包括Interpreter类里面的函数实现****************************/
/************************作者:郭周东  时间：2009年11月************************************/

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <string>
#include <vector>
using namespace std;
class Interpreter{
public:
	int interpreter(string s);	

	string getWord(string s, int *st);
	
	Interpreter(){}
	~Interpreter(){}
};

#endif