#include "Gradient_Node.h"
#include <iostream>

Basic_Node* Gradient_Node::EVAL(){
	std::cout<<"Gradient nodes cannot be evaluated."<<std::endl;
	return nullptr;
}

string Gradient_Node::get_name(){
	return "grad_node";
}

string Gradient_Node::get_type(){
	return "Gradient";
}

void Gradient_Node::clear_buffer(){}
