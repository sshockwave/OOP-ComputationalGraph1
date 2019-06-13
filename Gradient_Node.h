
#ifndef GRAD_NODE_H
#define GRAD_NODE_H

#include <map>

class Gradient_Node:Basic_Node{
	~Gradient_Node();
    virtual Basic_Node* EVAL() = 0;
    virtual string get_name()= 0;
    virtual string get_type() = 0;
	virtual void clear_buffer() = 0;
    float get_value(){return value;};
	void set_value(float a) { value = a;assigned = true; };
};

#endif //INC_7_Graph_H
