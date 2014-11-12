int CatalogManager::addIndex(string indexName,string tableName,string colName){return 1;}
int CatalogManager::findFile(string fileName){return  1;}
int CatalogManager::dropTable(string tableName){return 1;}
int CatalogManager::dropIndex(string index){return 1;}
int CatalogManager::deleteValue(string tableName){return 1;}
int CatalogManager::deleteValue(string tableName, int CatalogManager::deleteNum){return 1;}
int CatalogManager::insertRecord(string tableName, int CatalogManager::recordNum){return 1;}
int CatalogManager::getRecordNum(string tableName){return 2000;}
int CatalogManager::indexNameListGet(string tableName, vector<string>* indexNameVector){return 1;}

void addTable(string tableName, vector<Attribute>* attributeVector, string primaryKeyName = ""){}

//使传进来的地址得到一个table的属性名称的vector
//输出 是否得到成功
//输入 table的名称，table的属性名称列表的地址
int CatalogManager::attributeNameGet(string tableName, vector<string>* attributeNameVector){return 1;}

//使传进来的地址得到一个table的属性类型的vector
//输出 是否得到成功
//输入 table的名称，table的属性类型列表的地址
int CatalogManager::attributeTypeGet(string tableName, vector<string>* attributeTypeVector){return 1;}

//使传进来的地址得到一个table的属性的vector
//输出 是否得到成功
//输入 table的名称，table的属性列表的地址
int CatalogManager::attributeGet(string tableName, vector<Attribute>* attributeVector){return 1;}

int CatalogManager::calcuteLenth(string tableName){return 1;} //得到一个table的记录的大小
int CatalogManager::calcuteLenth2(int CatalogManager::type){
    if (type == Attribute::TYPE_INT) {
        return sizeof(int);
    }
    else if (type == Attribute::TYPE_FLOAT)
    {
        return sizeof(float);
    }
    else{
        return (int) sizeof(char[type]);
    }
}      //這理我的type改成了int类型，而不是一个String，type类型见attribute.h

// 通过table名和recordContent得到这个table的record的字符传，写入传进的字符串
void recordStringGet(string tableName, vector<string>* recordContent, char* recordResult){return ;}