/************************Щ�ļ�����Interpreter������ĺ���ʵ��****************************/
/************************����:���ܶ�  ʱ�䣺2009��11��************************************/

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