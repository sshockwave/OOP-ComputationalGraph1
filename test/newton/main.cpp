#include "Graph.h"
#include <iostream>
using namespace std;
void solve_func(){
	Graph g;
	g.set_new_item(new Placeholder_Node("x"));
	int n;
	cin>>n;
	for(int i=n;i>=0;i--){
		float a;
		cin>>a;
		if(i==n){
			g.add_node(new Constant_Node(a,"a"),"f");
		}else{
			g.initialize_operator_2("f","f","x","*");
			g.set_new_item(new Constant_Node(a,"a"));
			g.initialize_operator_2("f","f","a","+");
		}
	}
	g.initialize_operator_1("g","f","GRAD");
	g.initialize_operator_2("f_d","g","x","AT");
	g.initialize_operator_2("x_next","f","f_d","/");
	g.initialize_operator_2("x_next","x","x_next","-");
	float x_val;
	cin>>x_val;
	const int epochs=5;
	for(int i=0;i<epochs;i++){
		g.item["x"]->set_value(x_val);
		auto tmp_ans=g.item["f_d"]->EVAL();
		if(tmp_ans!=nullptr){
			if(tmp_ans->get_value()!=0){
				tmp_ans=g.item["x_next"]->EVAL();
				if(tmp_ans!=nullptr){
					x_val=tmp_ans->get_value();
				}
			}
		}
		g.item["x_next"]->clear_buffer();
		if(i>0){
			cout<<" ";
		}
		cout<<fixed<<setprecision(4)<<x_val;
	}
	cout<<endl;
}
int main(){
	size_t test_cases;
	cin>>test_cases;
	for(size_t i=0;i<test_cases;++i){
		solve_func();
	}
}
