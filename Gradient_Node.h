
#ifndef GRAD_NODE_H
#define GRAD_NODE_H

#include "Basic_Node.h"
#include <vector>
#include <map>

class Gradient_Node: public Basic_Node{
	protected:
		std::map<Basic_Node*,Basic_Node*>item;
	public:
		std::vector<Basic_Node*> node_list;//this contains all nodes created
		Gradient_Node(Basic_Node*);
		~Gradient_Node();
		Basic_Node* EVAL();
		string get_name();
		string get_type();
		void clear_buffer();
		Basic_Node* get_grad(Basic_Node*);
		std::vector<Basic_Node*> get_preq_nodes(){return {};};
		void push_grad(Basic_Node *target,Basic_Node *grad_val);
};

#endif //GRAD_NODE_H
