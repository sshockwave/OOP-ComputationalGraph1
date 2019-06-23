#include "Session.h"

using namespace std;

void Session::set(string name,float val){
	values[name]=val;
}//建立由Variable名字到float的映射

void Session::clear(){
	values.clear();
}

ostream & operator << (ostream & out,const Session &sess){
	out<<sess.values.size()<<endl;
	for(const auto &it:sess.values){
		out<<it.first<<" "<<it.second<<endl;
	}
	return out;
}//输出

istream & operator >> (istream & in,Session &sess){
	size_t n;
	in>>n;
	for(size_t i=0;i<n;i++){
		string name;
		float val;
		in>>name>>val;
		sess.set(name,val);
	}
}//输入
