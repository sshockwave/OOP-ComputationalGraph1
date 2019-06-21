#include "Operation_Node.h"
#include "Gradient_Node.h"
#include "Constant_Node.h"
//运算符基类的函数实现 
Operation_Node::Operation_Node(Basic_Node* b, Basic_Node* c, Basic_Node* d)
{
    prev_Datas.push_back(b);
    prev_Datas.push_back(c);
    prev_Datas.push_back(d);
}

Operation_Node::Operation_Node(Basic_Node* b, Basic_Node* c)
{
    prev_Datas.push_back(b);
    prev_Datas.push_back(c);
}

Operation_Node::Operation_Node(Basic_Node* b)
{
    prev_Datas.push_back(b);
}

void Operation_Node::clear_buffer()
{
	reset_state();
	for (int i = 0;i < prev_Datas.size();i++) {
		prev_Datas[i]->clear_buffer();
	}
}

//报错机制：return nullptr
//加法 
Basic_Node* Operation_Plus::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr){
    	return nullptr;
	} 
    Basic_Node* temp2 = prev_Datas[1]->EVAL();
    if(temp2 == nullptr) return nullptr;
   	float ans = temp1->get_value() + temp2->get_value();
    value = ans;
    return this;
}
void Operation_Plus::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	target_func->push_grad(prev_Datas[0],grad);
	target_func->push_grad(prev_Datas[1],grad);
}

//减法
Basic_Node* Operation_Minus::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    Basic_Node* temp2 = prev_Datas[1]->EVAL();
    if(temp2 == nullptr) return nullptr;
    float ans = temp1->get_value() - temp2->get_value();
    value = ans;
    return this;
}
void Operation_Minus::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	target_func->push_grad(prev_Datas[0],grad);
	Basic_Node* m1=new Constant_Node(-1,"-1");
	Basic_Node* mult=new Operation_Multiply(m1,grad);
	target_func->add_node(m1);
	target_func->add_node(mult);
	target_func->push_grad(prev_Datas[1],mult);
}

//乘法
Basic_Node* Operation_Multiply::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr)
    	return nullptr;
    Basic_Node* temp2 = prev_Datas[1]->EVAL();
    if(temp2 == nullptr) 
    	return nullptr;
	
    float ans = temp1->get_value() * temp2->get_value();
    value = ans;
    return this;
}

void Operation_Multiply::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	Basic_Node* tmp1=new Operation_Multiply(prev_Datas[1],grad);
	Basic_Node* tmp2=new Operation_Multiply(prev_Datas[0],grad);
	target_func->add_node(tmp1);
	target_func->add_node(tmp2);
	target_func->push_grad(prev_Datas[0],tmp1);
	target_func->push_grad(prev_Datas[1],tmp2);
}

//除法 
Basic_Node* Operation_Division::EVAL( ){
    Basic_Node* temp2 = prev_Datas[1]->EVAL();
    if(temp2 == nullptr) return nullptr;
    else if(temp2->get_value() == 0){
        std::cout << "ERROR: Division by zero" << std::endl;
        return nullptr;
    }
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    float ans = temp1->get_value() / temp2->get_value();
    value = ans;
    return this;
}
void Operation_Division::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	Basic_Node* v=new Operation_Division(grad,prev_Datas[1]);
	target_func->add_node(v);
	target_func->push_grad(prev_Datas[0],v);//dA/B
	v=new Operation_Division(v,prev_Datas[1]);
	target_func->add_node(v);
	v=new Operation_Multiply(v,prev_Datas[0]);
	target_func->add_node(v);
	Basic_Node* m1=new Constant_Node(-1,"minus one");
	target_func->add_node(m1);
	v=new Operation_Multiply(v,m1);
	target_func->add_node(v);
	target_func->push_grad(prev_Datas[1],v);//-A/B^2*dB
}

//正弦 
Basic_Node* Operation_Sin::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    float ans = sin(temp1->get_value() );
    value = ans;
    return this;
}
void Operation_Sin::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	Basic_Node* v=new Operation_Cos(prev_Datas[0]);
	target_func->add_node(v);
	v=new Operation_Multiply(v,grad);
	target_func->add_node(v);
	target_func->push_grad(prev_Datas[0],v);
}

//余弦
Basic_Node* Operation_Cos::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    float ans = cos(temp1->get_value() );
    value = ans;
    return this;
}
void Operation_Cos::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	Basic_Node* v=new Operation_Sin(prev_Datas[0]);
	target_func->add_node(v);
	v=new Operation_Multiply(v,grad);
	target_func->add_node(v);
	Basic_Node* m1=new Constant_Node(-1,"minus one");
	target_func->add_node(m1);
	v=new Operation_Multiply(v,m1);
	target_func->add_node(v);
	target_func->push_grad(prev_Datas[0],v);
}

//对数 
Basic_Node* Operation_Log::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    else if(temp1->get_value() <= 0){
       std::cout<<"ERROR: LOG operator's input must be positive"<<std::endl;
        return nullptr;
    }
    float ans = log(temp1->get_value() );
    value = ans;
    return this;
}
void Operation_Log::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	Basic_Node* v=new Operation_Division(grad,prev_Datas[0]);
	target_func->add_node(v);
	target_func->push_grad(prev_Datas[0],v);
}

//指数 
Basic_Node* Operation_Exp::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    float ans = exp(temp1->get_value() );
    value = ans;
    return this;
}
void Operation_Exp::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	Basic_Node* v=new Operation_Multiply(grad,this);
	target_func->add_node(v);
	target_func->push_grad(prev_Datas[0],v);
}

//双曲正切
Basic_Node* Operation_Tanh::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    float temp = exp(temp1->get_value() );
    value = (temp*temp - 1) / (temp*temp + 1);
    return this;
}
void Operation_Tanh::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	Basic_Node* v=new Operation_Multiply(this,this);
	target_func->add_node(v);
	v=new Operation_Multiply(grad,v);
	target_func->add_node(v);
	v=new Operation_Minus(grad,v);
	target_func->add_node(v);
	target_func->push_grad(prev_Datas[0],v);
}

//Sigmoid
Basic_Node* Operation_Sigmoid::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    float temp = exp(temp1->get_value() );
    value = temp / (temp + 1);
    return this;
}
void Operation_Sigmoid::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	Basic_Node* v=new Operation_Multiply(this,this);
	target_func->add_node(v);
	v=new Operation_Minus(this,v);
	target_func->add_node(v);
	v=new Operation_Multiply(grad,v);
	target_func->add_node(v);
	target_func->push_grad(prev_Datas[0],v);
}

//Print运算符子类
Basic_Node* Operation_Print::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    std::cout << fixed << setprecision(4) << "PRINT operator: " << prev_Datas[0]->get_name() << " = " << temp1->get_value() << std::endl;
    value = temp1->get_value();
    return this;
}
void Operation_Print::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	target_func->push_grad(prev_Datas[0],grad);
}

//逻辑运算符
Basic_Node* Operation_Logic::EVAL( ){
    Basic_Node* temp01 = prev_Datas[0]->EVAL();
    if(temp01 == nullptr) return nullptr;
    Basic_Node* temp02 = prev_Datas[1]->EVAL();
    if(temp02 == nullptr) return nullptr;

    float temp1 = temp01->get_value();
    float temp2 = temp02->get_value();
    if (temp1 == temp2) {
        if (type == "==" || type == "<=" || type == ">=")
            value = 1.0;
        else
            value = 0.0;
    }
    else if (temp1 > temp2) {
        if (type == ">" || type == ">=" || type == "!=")
            value = 1.0;
        else
            value = 0.0;
    }
    else if (temp1 < temp2) {
        if (type == "<" || type == "<=" || type == "!=")
            value = 1.0;
        else
            value = 0.0;
    }
    return this;
}
Basic_Node* Operation_COND::EVAL(){
    Basic_Node* temp01 = prev_Datas[0]->EVAL();
    if(temp01 == nullptr) return nullptr;
    Basic_Node* temp02 = prev_Datas[1]->EVAL();
    if(temp02 == nullptr) return nullptr;
    Basic_Node* temp03 = prev_Datas[2]->EVAL();
    if(temp03 == nullptr) return nullptr;

    float b_value = temp01->get_value();
    float c_value = temp02->get_value();
    float d_value = temp03->get_value();
    if (b_value > 0)
        value =  c_value;
    else
        value =  d_value;
    return this;
}

void Operation_COND::propagate_grad(Gradient_Node *target_func){
	Basic_Node* grad=target_func->get_grad(this);
	Basic_Node* zero=new Constant_Node(0,"zero");
	target_func->add_node(zero);
	{
		Basic_Node* val1=new Operation_COND(prev_Datas[0],grad,zero);
		target_func->add_node(val1);
		target_func->push_grad(prev_Datas[1],val1);
	}
	{
		Basic_Node* val2=new Operation_COND(prev_Datas[0],zero,grad);
		target_func->add_node(val2);
		target_func->push_grad(prev_Datas[2],val2);
	}
}
