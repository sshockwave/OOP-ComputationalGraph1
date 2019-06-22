#include"Graph.h"
#include<iomanip>
#include<fstream>
using std::stringstream;
using std::string;
using std::map;
using std::vector;
using std::cin;
using std::cout;
using std::fixed;
using std::setprecision;

void Graph::set_new_item(Data_Node* x){
	string name=x->get_name();
	auto it=item.find(name);
	if(it!=item.end()){
		abandoned.push_back(it->second);
	}
	item[name]=x;
}
void Graph::add_node(Basic_Node* x){
	abandoned.push_back(x);
}
void Graph::add_node(Basic_Node* x,string name){
	add_node(x);
	set_node(x,name);
}
void Graph::set_node(Basic_Node* x,string name){
	set_new_item(new Placeholder_Node(name, x));
}

void Graph::initialize_operator_1(string name, string a, string Operator)
{
    if (Operator == "SIN") {
		add_node(new Operation_Sin(item[a]),name);
    }
	else if (Operator == "COS") {
		add_node(new Operation_Cos(item[a]),name);
    }
    else if (Operator == "LOG") {
		add_node(new Operation_Log(item[a]),name);
    }
    else if (Operator == "TANH") {
		add_node(new Operation_Tanh(item[a]),name);
    }
    else if (Operator == "EXP") {
		add_node(new Operation_Exp(item[a]),name);
    }
    else if (Operator == "SIGMOID") {
		add_node(new Operation_Sigmoid(item[a]),name);
    }
    else if (Operator == "PRINT" || Operator == "Print") {
		add_node(new Operation_Print(item[a]),name);
    }
	else if (Operator == "GRAD"){
		add_node(new Gradient_Node(item[a],this),name);
	}
}

void Graph::initialize_operator_2(string name, string a, string b, string Operator)
{
    if (Operator == "+") {
		add_node(new Operation_Plus(item[a], item[b]),name);
    }
    else if (Operator == "-") {
		add_node(new Operation_Minus(item[a], item[b]),name);
    }
    else if (Operator == "*") {
		add_node(new Operation_Multiply(item[a], item[b]),name);
    }
    else if (Operator == "/") {
		add_node(new Operation_Division(item[a], item[b]),name);
    }
	else if (Operator == "AT") {
		Data_Node* ph=dynamic_cast<Data_Node*>(item[a]);
		if(ph==nullptr){
			cout<<"Error: Node "<<a<<" does not exist or does not match citeria."<<std::endl;
			return;
		}
		auto vec=ph->get_preq_nodes();
		if(vec.empty()){
			cout<<"Error: Node "<<a<<" does not exist or does not match citeria."<<std::endl;
		}
		Gradient_Node* grad=dynamic_cast<Gradient_Node*>(vec[0]);
		if(grad==nullptr){
			cout<<"Error: "<<a<<" is not a gradient node."<<std::endl;
			return;
		}
		//recycling should be handled by Gradient_Node
		set_node(grad->get_grad(item[b]),name);
	}
}

void Graph::initialize_operator_3(string name, string a, string b, string Operator)
{
    add_node(new Operation_Logic(item[a], item[b], Operator),name);
}

void Graph::initialize_operator_COND(string name, string a, string b, string c)
{
    add_node(new Operation_COND(item[a], item[b], item[c]),name);
}

//判断某个节点对应语句运算符的类型。一元/二元/逻辑/COND？ 返回值1/2/3/4
void Graph::crossroad(string s)
{
    vector<string> expressions;
    stringstream ss(s);
    string temp;
    int i = 0, location = 0, operation_type = 0;
    while (ss >> temp) {
        expressions.push_back(temp);
        if (temp == "SIN" || temp == "COS" || temp == "LOG" || temp == "TANH" || temp == "EXP" || temp == "SIGMOID" || temp == "PRINT" || temp == "Print" || temp == "GRAD") {
            location = i;
            operation_type = 1;
        }
        else if (temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "AT") {
            location = i;
            operation_type = 2;
        }
        else if (temp == ">" || temp == "<" || temp == ">=" || temp == "<=" || temp == "==" || temp == "!=") {
            location = i;
            operation_type = 3;
        }
        else if (temp == "COND") {
            location = i;
            operation_type = 4;
        }
        i++;
    }
    switch (operation_type) {
        case 1://初始化一元运算符
            initialize_operator_1(expressions[0], expressions[location + 1], expressions[location]);
            break;
        case 2://初始化二元运算符
            initialize_operator_2(expressions[0], expressions[location - 1], expressions[location + 1], expressions[location]);
            break;
        case 3://初始化逻辑运算符
            initialize_operator_3(expressions[0], expressions[location - 1], expressions[location + 1], expressions[location]);
            break;
        case 4://初始化COND
            initialize_operator_COND(expressions[0], expressions[location + 1], expressions[location + 2], expressions[location + 3]);
            break;
    }
}

int Graph::string_to_int(const string s)
{
    int n = 0;
    for (int i = 0;i < s.size();i++)
        n = n * 10 + s[i] - 48;
    return n;
}

void Graph::creat_nodes_1()
{
    int n = 0;
    string s;
    getline(cin, s);
    string name;
    n = string_to_int(s);
    for (int i = 0;i < n;i++) {
        getline(cin, s);
        stringstream ss(s);
        ss >> s;
        name = s;
        ss >> s;
        if (s == "P") {
            Data_Node* tmp = new Placeholder_Node(name);
            item[name] = tmp;
        }
        else if (s == "C") {
            float a = 0;
            ss >> a;
            Data_Node* tmp = new Constant_Node(a, name);
            item[name] = tmp;
        }
        else if (s == "V") {
            float a = 0;
            ss >> a;
            Data_Node* tmp = new Variable_Node(a, name);
            item[name] = tmp;
        }
    }
}

void Graph::creat_nodes_2()
{
    string s;
    int n1 = 0;
    getline(cin, s);
    n1 = string_to_int(s);
    for (int i = 0;i < n1;i++) {
        getline(cin, s);
        crossroad(s);
    }
}


void Graph::commands()
{
    string s;
    int	n2 = 0;
    getline(cin, s);
    n2 = string_to_int(s);
    for (int i = 0;i < n2;i++) {
    	getline(cin,s);
    	stringstream ss(s);
        ss >> s;
        if (s == "EVAL") {
            ss >> s;
            string target = s;
            if (item[target]->get_type() == "Placeholder") {
                int n3 = 0;
               	ss >> n3;
                for (int i = 0;i < n3;i++) {
                    float value = 0;
                    ss >> s >> value;
					item[s]->set_value(value);
                }
            }
            Basic_Node*  ans =  item[target]->EVAL();
            if(ans != nullptr) {
                answers[i] = ans->get_value();
                cout << fixed << setprecision(4) << answers[i] << std::endl;
            }	
			reset_state();
        }
        else if (s == "SETCONSTANT") {
            string target;
            ss >> target;
            float val = 0.0;
            ss >> val;
            item[target]->set_value(val);
        }
        else if (s == "SETANSWER") {
            string target;
            ss >> target;
            int num = 0;
            ss >> num;
            item[target]->set_value(answers[num-1]);
        }
		else if (s == "SAVEFILE") {
			string filename;
			ss>>filename;
			std::fstream fout(filename);
			Session sess;
			save(sess);
			fout<<sess;
		}
		else if (s == "READFILE") {
			string filename;
			ss>>filename;
			std::fstream fin(filename);
			Session sess;
			fin>>sess;
			restore(sess);
		}

    }
}

Graph::~Graph()
{
    map<string, Data_Node*>::iterator iter = item.begin();
    while (iter != item.end()) {
        delete iter->second;
        iter++;
    }
    for (int i = 0;i < abandoned.size();i++) {
    	 delete abandoned[i];
    }
}

void Graph::reset_state(){
	for(auto it:item){
		it.second->reset_state();
	}
	for(auto it:abandoned){
		it->reset_state();
	}
}

void Graph::save(Session& sess){
	for(const auto &it:item){
		auto ptr=dynamic_cast<Variable_Node*>(it.second);
		if(ptr==nullptr)continue;
		sess.set(it.first,ptr->get_value());
	}
}

void Graph::restore(Session& sess){
	for(const auto &pii:sess.values){
		auto it=item.find(pii.first);
		if(it==item.end())continue;
		auto ptr=dynamic_cast<Variable_Node*>(it->second);
		if(ptr==nullptr)continue;
		ptr->set_value(pii.second);
	}
}
