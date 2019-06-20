#include "Gradient_Node.h"
#include "Constant_Node.h"
#include "Graph.h"
#include <iostream>
#include <queue>

Gradient_Node::Gradient_Node(Basic_Node* target_func,Graph* g){
	graph=g;
	std::map<Basic_Node*,size_t>in_degree;
	std::queue<Basic_Node*>q;
	q.push(target_func);
	for(;!q.empty();){
		Basic_Node *x=q.front();
		q.pop();
		for(auto next:x->get_preq_nodes()){
			auto it=in_degree.find(next);
			if(it==in_degree.end()){
				q.push(next);
				in_degree[next]=1;
			}else{
				++it->second;
			}
		}
	}
	q.push(target_func);
	push_grad(target_func,new Constant_Node(1,"one"));
	for(;!q.empty();){
		Basic_Node *x=q.front();
		q.pop();
		x->propagate_grad(this);
		for(auto next:x->get_preq_nodes()){
			if(--in_degree[next]==0){
				q.push(next);
			}
		}
	}
}

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

Basic_Node* Gradient_Node::get_grad(Basic_Node* var){
	auto it=item.find(var);
	if(it==item.end()){
		auto zero=new Constant_Node(0,"zero");
		add_node(zero);
		return zero;
	}
	return it->second;
}

void Gradient_Node::push_grad(Basic_Node *target,Basic_Node *grad_val){
	if(target==nullptr)return;
	auto it=item.find(target);
	if(it==item.end()){
		item[target]=grad_val;
		return;
	}
	it->second=new Operation_Plus(it->second,grad_val);
	add_node(it->second);
}

void Gradient_Node::add_node(Basic_Node *x){
	graph->abandoned.push_back(x);
}
