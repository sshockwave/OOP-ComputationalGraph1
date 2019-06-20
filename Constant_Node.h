
#ifndef INC_7_CONSTANT_NODE_H
#define INC_7_CONSTANT_NODE_H
#include "Data_Node.h"
using std::string;

class Constant_Node:public Data_Node{
public:
    Constant_Node(){};
    Constant_Node(float x,string y);
    ~Constant_Node() {};
    Basic_Node* EVAL();
	void reset_state(){}
    
};


#endif //INC_7_CONSTANT_NODE_H
