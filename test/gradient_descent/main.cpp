#include <iostream>
#include <cassert>
#include "Graph.h"

using namespace std;

const int max_epochs=100;
const float step=0.001;

inline void gradient_descent(Graph &g,vector<float>&a){
	g.reset_state();
	for(size_t i=0;i<a.size();i++){
		g.item["a_"+to_string(i)]->set_value(a[i]);
	}
	for(size_t i=0;i<a.size();i++){
		auto tmp_ans=g.item["d_a_"+to_string(i)]->EVAL();
		assert(tmp_ans!=nullptr);
		a[i]-=step*tmp_ans->get_value();
	}
}
int main(){
	int n,point_cnt;
	cin>>n>>point_cnt;
	Graph g;
	g.add_node(new Constant_Node(0,"zero"),"loss");
	for(int i=0;i<=n;i++){
		string id="a_"+to_string(i);
		g.set_new_item(new Placeholder_Node(id));
	}
	for(int i=1;i<=point_cnt;i++){
		g.set_node(g.item["a_0"],"tmp_loss");
		for(int j=1;j<=n;j++){
			float v;
			cin>>v;
			string id="v_"+to_string(i)+"_"+to_string(j);
			g.set_new_item(new Constant_Node(v,id));
			g.initialize_operator_2("tmp_prod","a_"+to_string(j),id,"*");
			g.initialize_operator_2("tmp_loss","tmp_loss","tmp_prod","+");
		}
		float v;
		cin>>v;
		string id="y_"+to_string(i);
		g.set_new_item(new Constant_Node(v,id));
		g.initialize_operator_2("tmp_loss","tmp_loss",id,"-");
		g.initialize_operator_2("tmp_loss","tmp_loss","tmp_loss","*");
		g.initialize_operator_2("loss","loss","tmp_loss","+");
	}
	vector<float>a(n+1);
	g.initialize_operator_1("grad_loss","loss","GRAD");
	for(int i=0;i<=n;i++){
		string id="a_"+to_string(i);
		g.initialize_operator_2("d_"+id,"grad_loss",id,"AT");
	}
	for(int epoch=0;epoch<max_epochs;epoch++){
		gradient_descent(g,a);
		auto tmp_ans=g.item["loss"]->EVAL();
		assert(tmp_ans!=nullptr);
		float loss=tmp_ans->get_value()/point_cnt;
		cerr<<"loss="<<loss<<endl;
		if(loss<1e-6)break;
	}
	for(size_t i=1;i<a.size();++i){
		cout<<a[i]<<" ";
	}
	cout<<a[0]<<endl;
}
