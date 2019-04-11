#include "arithmetics.h"

using namespace cgraph;

class NodePrint:public Node{
	private:
		ptr p;
		std::string name;
		std::ostream& out;
	public:
		NodePrint(ptr _p,const std::string &_s,std::ostream& _o):p(_p),name(_s),out(_o){}
		std::vector<ptr> getPreq(Symbol sym) const{
			if(p->visited==sym) return {};
			return {p};
		}
		std::vector<ptr> getAllPreq() const{
			return {p};
		}
		void eval(Symbol sym){
			version=p->version;
			value=p->value;
			out<<"Print Operator: "<<name<<"="<<value<<std::endl;
		}
};

Expression print(Expression expr,std::string name,std::ostream & out){
	return static_cast<Node::ptr>(std::make_shared<NodePrint>(static_cast<Node::ptr>(expr),name,out));
}
