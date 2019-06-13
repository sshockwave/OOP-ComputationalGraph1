
#ifndef GRAD_NODE_H
#define GRAD_NODE_H

#include "Basic_Node.h"
#include <vector>
#include <map>

class Gradient_Node:Basic_Node{
	protected:
		//See Graph.h, it's almost the same
		std::vector<Basic_Node*> abandoned;
		std::map<Basic_Node*,Basic_Node*>item;
	public:
		Gradient_Node(Basic_Node*);
		~Gradient_Node();
		Basic_Node* EVAL();
		string get_name();
		string get_type();
		void clear_buffer();
		Basic_Node* get_grad(Basic_Node*);
		void push_grad(Basic_Node *target,Basic_Node *grad_val);
};

#endif //GRAD_NODE_H
