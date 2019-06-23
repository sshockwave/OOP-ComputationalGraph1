
#ifndef GRAD_NODE_H
#define GRAD_NODE_H

#include "Basic_Node.h"
#include <vector>
#include <map>

class Gradient_Node: public Basic_Node{
	protected:
		std::map<Basic_Node*,Basic_Node*>item;
		class Graph* graph;
	public:
		Gradient_Node(Basic_Node*,Graph*);//求导的目标函数和所属计算图
		Basic_Node* EVAL();
		string get_name();
		string get_type();
		void clear_buffer();
		Basic_Node* get_grad(Basic_Node*);//获取节点的偏导
		std::vector<Basic_Node*> get_preq_nodes(){return {};};
		void push_grad(Basic_Node *target,Basic_Node *grad_val);//给节点加上偏导值
		void add_node(Basic_Node*);//将新建的节点加入图的内存管理
};

#endif //GRAD_NODE_H
