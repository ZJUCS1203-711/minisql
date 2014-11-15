

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <vector>
using namespace std;
class Interpreter{
public:
	string fileName ;
	int interpreter(string s);	

	string getWord(string s, int *st);
	
	Interpreter(){}
	~Interpreter(){}
};

#endif