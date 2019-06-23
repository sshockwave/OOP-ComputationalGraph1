#include "Placeholder_Node.h"
Basic_Node* Placeholder_Node::EVAL( ){
	if (assigned) {
		return this;
	}
	else if (prev_Operation == nullptr) {
		std::cout << "ERROR: Placeholder missing" << std::endl;
		return nullptr;
	}
	else {
		Basic_Node* tmp = prev_Operation->EVAL();
		if(tmp == nullptr) return nullptr;
		value = tmp->get_value();
		assigned = true;
		return this;
	}
}//进行判断以及计算


Placeholder_Node::Placeholder_Node(string x){
	assigned = false;
    name = x;
    type = "Placeholder";
    prev_Operation = nullptr;
}

Placeholder_Node::Placeholder_Node(string x, Basic_Node* y) {
	assigned = false;
    name = x;
    type = "Placeholder";
    prev_Operation = y;
}
