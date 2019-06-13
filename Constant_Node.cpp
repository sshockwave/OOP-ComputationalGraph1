#include "Constant_Node.h"
Constant_Node::Constant_Node(float x, string y) {
	assigned = true;
    value = x;
    name = y;
    type = "Constant";
	prev_Operation = nullptr;
};

Basic_Node* Constant_Node::EVAL() {
    return this;
}
