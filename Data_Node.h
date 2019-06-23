
#ifndef INC_7_DATA_NODE_H
#define INC_7_DATA_NODE_H
#include <vector>
#include "Basic_Node.h"
#include "Operation_Node.h"
#include "Gradient_Node.h"

using std::vector;
using std::string;

//抽象类，数据类基类
class Data_Node:public Basic_Node{
protected:
    string name;
    string type;
    Basic_Node* prev_Operation;
public:
    Data_Node(){};
    string get_name();
    virtual string get_type();
    virtual Basic_Node* EVAL() = 0;
	virtual void clear_buffer();//清空缓存
	std::vector<Basic_Node*>get_preq_nodes(){
		if(prev_Operation==nullptr)return {};
		return {prev_Operation};
	}//获得前驱节点
	void propagate_grad(Gradient_Node* target_func)override{
		if(prev_Operation!=nullptr){
			target_func->push_grad(prev_Operation,target_func->get_grad(this));
		}
	}//将自身偏导传递给依赖的节点
 };


#endif //INC_7_DATA_NODE_H
