
#ifndef INC_7_BASIC_NODE_H
#define INC_7_BASIC_NODE_H

#include<string>
#include<string.h>
#include<utility>
#include<map>
#include<iostream>
#include<vector>
using std::map;
using std::string;

//抽象类，基本结点
class Basic_Node{
protected:
    float value;
	bool assigned;//暂且认为只对数据节点有效，记录每次EVAL过程中，节点是否已被计算过一次
public:
    Basic_Node(){};
    virtual ~Basic_Node(){};
    virtual Basic_Node* EVAL() = 0;
    virtual string get_name()= 0;
    virtual string get_type() = 0;
	virtual void reset_state(){value=0;assigned=false;}
	virtual void clear_buffer() = 0;
    float get_value(){return value;};
	void set_value(float a) { value = a;assigned = true; };
	virtual std::vector<Basic_Node*> get_preq_nodes() = 0;
	virtual void propagate_grad(class Gradient_Node *target_func){
		std::cout<<"Error: Node of "<<get_type()<<" does not implement gradient calculation"<<std::endl;
	}

};


#endif //INC_7_BASIC_NODE_H
