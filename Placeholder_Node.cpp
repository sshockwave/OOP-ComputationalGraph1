#include "Placeholder_Node.h"
#include "Gradient_Node.h"
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
}

std::vector<Basic_Node*>Placeholder_Node::get_preq_nodes(){
	if(prev_Operation==nullptr)return {};
	return {prev_Operation};
}

void Placeholder_Node::propagate_grad(Gradient_Node* target_func){
	if(prev_Operation!=nullptr){
		target_func->push_grad(prev_Operation,target_func->get_grad(this));
	}
}


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
