#include"Variable_Node.h"

Variable_Node::Variable_Node(float x, string y)
{
	assigned = true;
    value = x;
    name = y;
    type = "Variable";
	prev_Operation = nullptr;
}

Basic_Node* Variable_Node::EVAL()
{
    return this;  
}
