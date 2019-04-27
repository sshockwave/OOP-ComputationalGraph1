#include "arithmetics.h"

using namespace cgraph;

class NodeAdd:public Node{
	private:
		//该节点的值=a+b
		ptr a,b;
	public:
		NodeAdd(ptr _a,ptr _b):a(_a),b(_b){}
		//返回计算这个节点需要的所有节点
		std::vector<ptr> getAllPreq()const{
			return {a,b};
		}
		//返回当前需要的而且还没被计算的节点
		std::vector<ptr> getPreq(Symbol sym)const{
			//还需要计算的节点放在list中
			std::vector<ptr>list;
			//如果a->visited==sym，说明a已经被计算好了
			if(a->visited!=sym){
				//a还没被计算好，应该要被计算
				list.push_back(a);
			}
			if(b->visited!=sym){
				//b同理
				list.push_back(b);
			}
			return list;
		}
		void eval(Symbol sym){
			if(a->getVersion()==version&&b->getVersion()==version){
				//这个节点的前驱节点的值没有变化
				//不需要重新计算
				return;
			}
			//重新计算值
			value=a->getValue()+b->getValue();
			//因为这一次计算中值更新了，版本号也必须跟着更新
			version=sym;
		}
};

cgraph::Expression operator + (cgraph::Expression a,cgraph::Expression b){
	return std::make_shared<NodeAdd>(a,b);
}

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
			version=p->getVersion();
			value=p->getValue();
			out<<"Print Operator: "<<name<<"="<<value<<std::endl;
		}
};

Expression print(Expression expr,std::string name,std::ostream & out){
	return std::make_shared<NodePrint>(static_cast<Node::ptr>(expr),name,out);
}
