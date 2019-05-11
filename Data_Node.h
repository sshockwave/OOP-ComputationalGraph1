
#ifndef INC_7_DATA_NODE_H
#define INC_7_DATA_NODE_H
#include <vector>
#include "Basic_Node.h"
#include "Operation_Node.h"

using std::vector;
using std::string;

//抽象类，数据类基类
class Data_Node:public Basic_Node{
protected:
    string name;
    string type;
    Basic_Node* prev_Operation;
public:
    Data_Node(){};
    ~Data_Node();
    string get_name();
    virtual string get_type();
    virtual Basic_Node* EVAL() = 0;
	virtual void clear_buffer();
 };


#endif //INC_7_DATA_NODE_H
