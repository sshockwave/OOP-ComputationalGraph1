#include "Gradient_Node.h"
#include "Constant_Node.h"
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

void Gradient_Node::clear_buffer(){
	for(auto it:item){
		it.second->clear_buffer();
	}
}

Gradient_Node::~Gradient_Node(){
	for(auto pii:item){
		delete pii.second;
	}
	for(auto ptr:abandoned){
		delete ptr;
	}
}

Basic_Node* Gradient_Node::get_grad(Basic_Node* var){
	auto it=item.find(var);
	if(it==item.end()){
		auto zero=new Constant_Node(0,"zero");
		abandoned.push_back(zero);
		return zero;
	}
	return it->second;
}

void Gradient_Node::push_grad(Basic_Node *target,Basic_Node *grad_val){
	auto it=item.find(target);
	if(it==item.end()){
		item[target]=grad_val;
		return;
	}
	abandoned.push_back(it->second);
	it->second=new Operation_Plus(it->second,grad_val);
}
