#include "cgraph.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

inline void invalidInput(std::string msg){
	std::cout<<"Invalid input: "<<msg<<std::endl;
	exit(0);
}

cgraph::Graph G;
inline cgraph::Expression parseExpr(std::string expr){
	std::vector<std::string>token;
	{
		std::stringstream ss(expr);
		for(std::string cur;ss>>cur;token.push_back(cur));
	}
	if(token.size()<2u){
		invalidInput("too few arguments in expression '"+expr+"'");
	}
	if(token[0]=="SIN"){
		return sin(G.getExpression(token[1]));
	}
	if(token[0]=="LOG"){
		return log(G.getExpression(token[1]));
	}
	if(token[0]=="EXP"){
		return exp(G.getExpression(token[1]));
	}
	if(token[0]=="TANH"){
		return tanh(G.getExpression(token[1]));
	}
	if(token[0]=="SIGMOID"){
		return sigmoid(G.getExpression(token[1]));
	}
	if(token[0]=="PRINT"){
		return print(G.getExpression(token[1]),token[1]);
	}
	if(token[0]=="COND"){
		if(token.size()<4u){
			invalidInput("too few arguments in expression '"+expr+"'");
		}
		return cond(G.getExpression(token[1]),G.getExpression(token[2]),G.getExpression(token[3]));
	}
	//a op b
	if(token.size()!=3u){
		invalidInput("incorrect number of arguments in expression '"+expr+"'");
	}
	if(token[1]=="+"){
		return G.getExpression(token[0])+G.getExpression(token[2]);
	}
	if(token[1]=="-"){
		return G.getExpression(token[0])-G.getExpression(token[2]);
	}
	if(token[1]=="*"){
		return G.getExpression(token[0])*G.getExpression(token[2]);
	}
	if(token[1]=="/"){
		return G.getExpression(token[0])/G.getExpression(token[2]);
	}
	if(token[1]==">"){
		return G.getExpression(token[0])>G.getExpression(token[2]);
	}
	if(token[1]=="<"){
		return G.getExpression(token[0])<G.getExpression(token[2]);
	}
	if(token[1]==">="){
		return G.getExpression(token[0])>=G.getExpression(token[2]);
	}
	if(token[1]=="<="){
		return G.getExpression(token[0])<=G.getExpression(token[2]);
	}
	if(token[1]=="=="){
		return G.getExpression(token[0])==G.getExpression(token[2]);
	}
	invalidInput("can not parse expr '"+expr+"'");
}
inline cgraph::num_t startEval(){
	std::string name;
	int phcnt;
	std::cin>>name>>phcnt;
	cgraph::ph_map mp;
	for(int i=1;i<=phcnt;i++){
		std::string name;
		cgraph::num_t value;
		std::cin>>name>>value;
		mp[G.getPlaceholder(name)]=value;
	}
	return eval(G.getExpression(name),mp);
}
int main(){
	int tot;
	//Read placeholders & constants
	for(std::cin>>tot;tot--;){
		std::string name;
		char type;
		std::cin>>name>>type;
		if(type=='P'){
			cgraph::Placeholder ph;
			G.define(name,ph);
		}else if(type=='C'){
			cgraph::num_t value;
			std::cin>>value;
			cgraph::Constant cnst(value);
			G.define(name,cnst);
		}else{
			invalidInput(std::string("unexpected sink type ")+type);
		}
	}
	//Read nodes
	for(std::cin>>tot;tot--;){
		std::string name;
		char equalCh;
		std::cin>>name>>equalCh;
		if(equalCh!='='){
			invalidInput(std::string("unexpected ")+equalCh+", expected '='");
			exit(0);
		}
		std::string str;
		std::getline(std::cin,str);
		try{
			G.define(name,parseExpr(str));
		}catch(cgraph::Error e){
			invalidInput(e.what());
		}
	}
	//Process operations
	int q;
	std::cin>>q;
	std::map<int,cgraph::num_t>outputs;
	std::cout.setf(std::ios::fixed,std::ios::floatfield);
	std::cout.precision(4);
	for(int i=1;i<=q;i++){
		std::string op;
		std::cin>>op;
		if(op=="EVAL"){
			try{
				outputs[i]=startEval();
				std::cout<<outputs[i]<<std::endl;
			}catch(cgraph::Error e){
				std::cout<<"ERROR: "<<e.what()<<std::endl;
			}
		}else{
			invalidInput("Unexpected operation "+op);
		}
	}
}
