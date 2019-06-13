
#ifndef GRAD_NODE_H
#define GRAD_NODE_H

#include "Basic_Node.h"
#include <vector>
#include <map>

class Gradient_Node:Basic_Node{
	protected:
		std::vector<Basic_Node*> abandoned;
		std::map<Basic_Node*,Basic_Node*>grad;
	public:
		~Gradient_Node();
		Basic_Node* EVAL();
		string get_name();
		string get_type();
		void clear_buffer();
};

#endif //INC_7_Graph_H
