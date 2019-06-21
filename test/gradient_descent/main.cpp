#include <iostream>
#include <cassert>
#include "Graph.h"

using namespace std;

const int max_epochs=30000;

inline float gradient_descent(Graph &g,vector<float>&a,vector<float>&step,float learn_rate,float momentum){
	g.reset_state();
	for(size_t i=0;i<a.size();i++){
		g.item["a_"+to_string(i)]->set_value(a[i]);
	}
	float sum=0;
	for(size_t i=0;i<a.size();i++){
		auto tmp_ans=g.item["d_a_"+to_string(i)]->EVAL();
		assert(tmp_ans!=nullptr);
		step[i]=tmp_ans->get_value()*learn_rate+step[i]*momentum;
		sum+=step[i]*step[i];
		a[i]-=step[i];
	}
	return sum;
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
	g.initialize_operator_1("grad_loss","loss","GRAD");
	for(int i=0;i<=n;i++){
		string id="a_"+to_string(i);
		g.initialize_operator_2("d_"+id,"grad_loss",id,"AT");
	}
	vector<float>a(n+1),grad(n+1);
	float last_loss;
	for(int epoch=1;epoch<=max_epochs;epoch++){
		float gradlen=gradient_descent(g,a,grad,0.0001,0.6);
		auto tmp_ans=g.item["loss"]->EVAL();
		assert(tmp_ans!=nullptr);
		float loss=tmp_ans->get_value()/point_cnt;
		cerr<<"loss="<<loss<<"\r";
		if(gradlen<1e-8&&epoch>1&&fabs(loss-last_loss)<1e-6)break;
		last_loss=loss;
	}
	for(size_t i=1;i<a.size();++i){
		cout<<a[i]<<" ";
	}
	cout<<a[0]<<endl;
}
