
#ifndef INC_7_VARIABLE_NODE_H
#define INC_7_VARIABLE_NODE_H
#include"Data_Node.h"

class Variable_Node :public Data_Node
{
public:
    Variable_Node() {};
    Variable_Node(float x, string y);
    ~Variable_Node() {};
    Basic_Node* EVAL();
};

#endif //INC_7_VARIABLE_NODE_H
