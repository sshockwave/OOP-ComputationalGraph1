
#ifndef INC_7_Graph_H
#define INC_7_Graph_H

#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<sstream>
#include<iomanip>
#include"Data_Node.h"
#include"Constant_Node.h"
#include"Operation_Node.h"
#include"Placeholder_Node.h"
#include"Variable_Node.h"
#include"Gradient_Node.h"
using std::string;
using std::map;

class Graph  //完成对整张计算图的操作
{
    vector<Basic_Node*> abandoned;  //重名结点中的老结点
    map<int, float> answers; //第几次执行的结果
public:
	map<Basic_Node*,float>set_variable;
    map<string, Data_Node*> item; //所有数据结点
    Graph(){};
    ~Graph();
	//add this node to memory management list
	void add_node(Basic_Node*);
	void add_node(Basic_Node *x,string name);
	//set the mapping only, don't add to memory management
	void set_node(Basic_Node *x,string name);
	//set this item with the name in the data_node
	void set_new_item(Data_Node*);

    void creat_nodes_1();
    void creat_nodes_2();
    void commands();
    void initialize_operator_1(string name, string a, string Operator);
    void initialize_operator_2(string name, string a, string b, string Operator);
    void initialize_operator_2_left(string name, string a, string b, string Operator);
    void initialize_operator_3(string name, string a, string b, string Operator);
    void initialize_operator_COND(string name, string a, string b, string c);
    void crossroad(string s);
    int string_to_int(string s);
	void reset_state();

    friend class Variable_Node;
};

#endif //INC_7_Graph_H
