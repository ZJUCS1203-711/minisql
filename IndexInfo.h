#ifndef minisql_IndexInfo_h
#define minisql_IndexInfo_h

#include <string>
using namespace std;

class IndexInfo
{
public:
	IndexInfo(string i,string t,string a)
	{indexName = i;tableName = t;Attribute = a;}
    string indexName;
    string tableName;
    string Attribute;
    int type;
};

#endif