
#ifndef INC_7_OPERATION_NODE_H
#define INC_7_OPERATION_NODE_H
#include <vector>
#include <cmath>
#include<iomanip>
#include "Basic_Node.h"
using std::vector;
using std::fixed;
using std::setprecision;
using std::map;
//计算符基类
class Operation_Node :public Basic_Node {
protected:
    vector<Basic_Node*> prev_Datas;
public:
    Operation_Node() {};
    Operation_Node(Basic_Node* b);
    Operation_Node(Basic_Node* b, Basic_Node* c);
    Operation_Node(Basic_Node* b, Basic_Node* c, Basic_Node* d);//三种不同的构造函数
    ~Operation_Node() {};
    virtual Basic_Node* EVAL() = 0;   //计算
    string get_type() { return ""; }  //获取变量类型
    string get_name() { return ""; }  //获取变量名
	void clear_buffer();
	std::vector<Basic_Node*> get_preq_nodes() override{
		return prev_Datas;
	}//获取前驱节点
    
    
    //DEBUG:
	void get_prevs(){
		for(int i=0;i<prev_Datas.size();i++){
			std::cout<<prev_Datas[i]->get_type()<<":"<<prev_Datas[i]->get_name()<<std::endl; 
		}
	} 
};

//二元运算符

//加法计算符子类
class Operation_Plus:public Operation_Node{
public:
    Operation_Plus(){};
    ~Operation_Plus(){};
    Operation_Plus(Basic_Node* b, Basic_Node* c) :Operation_Node(b, c) {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};



//减法计算符子类
class Operation_Minus:public Operation_Node{
public:
    Operation_Minus(){};
    Operation_Minus(Basic_Node* b, Basic_Node* c) :Operation_Node(b, c) {};
    ~Operation_Minus() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};



//乘法计算符子类
class Operation_Multiply :public Operation_Node
{
public:
    Operation_Multiply() {};
    Operation_Multiply(Basic_Node* b, Basic_Node* c) :Operation_Node(b, c) {};
    ~Operation_Multiply() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};



//除法运算符子类
class Operation_Division :public Operation_Node
{
public:
    Operation_Division() {};
    Operation_Division(Basic_Node* b, Basic_Node* c) :Operation_Node(b, c) {};
    ~Operation_Division() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};

//Bind类运算子类
class Operation_Bind:public Operation_Node{
public:
	Operation_Bind(Basic_Node* b,Basic_Node* c) :Operation_Node(b, c) {};
	~Operation_Bind(){}
	Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};

//Assign类运算子类
class Operation_Assign:public Operation_Node{
	protected:
		map<Basic_Node*,float>&set_variable;
public:
	Operation_Assign(Basic_Node* b,Basic_Node* c,map<Basic_Node*,float>mp):Operation_Node(b, c),set_variable(mp) {};
	~Operation_Assign(){}
	Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};


//一元运算符

//正弦运算符子类
class Operation_Sin :public Operation_Node
{
public:
    Operation_Sin() {};
    Operation_Sin(Basic_Node* b) :Operation_Node(b) {};
    ~Operation_Sin() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};

//余弦运算符子类
class Operation_Cos :public Operation_Node
{
public:
    Operation_Cos() {};
    Operation_Cos(Basic_Node* b) :Operation_Node(b) {};
    ~Operation_Cos() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};

//对数运算符子类
class Operation_Log :public Operation_Node
{
public:
    Operation_Log() {}
    Operation_Log(Basic_Node* b) :Operation_Node(b) {};
    ~Operation_Log() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};



//指数运算符子类
class Operation_Exp :public Operation_Node
{
public:
    Operation_Exp() {};
    Operation_Exp(Basic_Node* b) :Operation_Node(b) {};
    ~Operation_Exp() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};



//双曲正切运算符子类
class Operation_Tanh :public Operation_Node
{
public:
    Operation_Tanh() {};
    Operation_Tanh(Basic_Node* b) :Operation_Node(b) {};
    ~Operation_Tanh() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};


//Sigmoid运算符子类
class Operation_Sigmoid :public Operation_Node
{
public:
    Operation_Sigmoid() {};
    Operation_Sigmoid(Basic_Node* b) :Operation_Node(b) {};
    ~Operation_Sigmoid() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};



//Print运算符子类
class Operation_Print :public Operation_Node
{
public:
    Operation_Print() {};
    Operation_Print(Basic_Node* b) :Operation_Node(b) {};
    ~Operation_Print() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};

//Assert运算符子类
class Operation_Assert:public Operation_Node{
public:
	Operation_Assert(){};
	Operation_Assert(Basic_Node* b):Operation_Node(b){};
	~Operation_Assert(){};
	Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override{}
};

//逻辑运算符子类
class Operation_Logic:public Operation_Node
{
    string type;
public:
    Operation_Logic() {};
    Operation_Logic(Basic_Node* b, Basic_Node* c, string s) :Operation_Node(b, c), type(s) {};
    ~Operation_Logic() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override{}
};

//Cond运算符子类
class Operation_COND :public Operation_Node
{
public:
    Operation_COND() {};
    Operation_COND(Basic_Node* b, Basic_Node* c, Basic_Node* d) :Operation_Node(b, c, d) {};
    ~Operation_COND() {};
    Basic_Node* EVAL();
	void propagate_grad(Gradient_Node *target_func)override;
};



#endif //INC_7_OPERATION_NODE_H
