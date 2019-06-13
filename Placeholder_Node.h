
#ifndef INC_7_PLACEHOLDER_NODE_H
#define INC_7_PLACEHOLDER_NODE_H
#include"Data_Node.h"

class Placeholder_Node :public Data_Node {
public:
    Placeholder_Node(){};
    Placeholder_Node(string x);
    Placeholder_Node(string x,Basic_Node* y);
    ~Placeholder_Node() {};
    Basic_Node* EVAL();
    string get_name() { return name; }
};


#endif //INC_7_PLACEHOLDER_NODE_H
