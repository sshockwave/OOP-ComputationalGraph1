#include "Operation_Node.h"
#include "Gradient_Node.h"
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
	target_func->push_grad(prev_Datas[0],new Operation_Multiply(prev_Datas[1],grad));
	target_func->push_grad(prev_Datas[1],new Operation_Multiply(prev_Datas[0],grad));
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

//正弦 
Basic_Node* Operation_Sin::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    float ans = sin(temp1->get_value() );
    value = ans;
    return this;
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

//指数 
Basic_Node* Operation_Exp::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    float ans = exp(temp1->get_value() );
    value = ans;
    return this;
}

//双曲正切
Basic_Node* Operation_Tanh::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    float temp = exp(temp1->get_value() );
    value = (temp*temp - 1) / (temp*temp + 1);
    return this;
}

//Sigmoid
Basic_Node* Operation_Sigmoid::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    float temp = exp(temp1->get_value() );
    value = temp / (temp + 1);
    return this;
}

//Print运算符子类
Basic_Node* Operation_Print::EVAL( ){
    Basic_Node* temp1 = prev_Datas[0]->EVAL();
    if(temp1 == nullptr) return nullptr;
    std::cout << fixed << setprecision(4) << "PRINT operator: " << prev_Datas[0]->get_name() << " = " << temp1->get_value() << std::endl;
    value = temp1->get_value();
    return this;
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
