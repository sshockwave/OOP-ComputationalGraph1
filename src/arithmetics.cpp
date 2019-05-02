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

class NodeSubtract :public Node {
private:
	ptr a, b;
public:
	NodeSubtract(ptr_a, ptr_b) :a(_a), b(_b) {}
	std::vector<ptr> getAllPreq()const {
		return { a,b };
	}
	std::vector<ptr> getPreq(Symbol sym)const {
		return { a,b };
	}
	void eval(Symbol sym) {
		value = a->getValue() - b->getvalue();
		version = sym;
	}
};
cgragh::Expression operator -(cgragh::Expression a, cgragh::Expression b) {
	return std::make_shared<NodeSubtract>(a, b);
}

class NodeMultiply :public Node {
private:
	ptr a, b;
public:
	NodeMultiply(ptr_a, ptr_b) :a(_a), b(_b) {}
	std::vector<ptr> getAllPreq()const {
		return { a,b };
	}
	std::vector<ptr> getPreq(Symbol sym)const {
		return { a,b };
	}
	void eval(Symbol sym) {
		value = a->getValue()*b->getvalue();
		version = sym;
	}
};
cgragh::Expression operator *(cgragh::Expression a, cgragh::Expression b) {
	return std::make_shared<NodeSubtract>(a, b);
}

class NodeDivide :public Node {
private:
	ptr a, b;
public:
	NodeSubtract(ptr_a, ptr_b) :a(_a), b(_b) {}
	std::vector<ptr> getAllPreq()const {
		return { a,b };
	}
	std::vector<ptr> getPreq(Symbol sym)const {
		return { a,b };
	}
	void eval(Symbol sym) {
		if (b->getvalue() == 0) {
			throw Error("Division by zero");
		}
		else {
			value = a->getValue() / b->getvalue();
			version = sym;
		}
	}
};
cgragh::Expression operator /(cgragh::Expression, cgragh::Expression) {
	return std::make_shared<NodeDivide>(a, b);
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

cgragh::Expression sin(cgragh::Expression a) {
	return std::make_shared<NodeSin>(a);
}

class NodeLog :public Node {
private:
	ptr p;
public:
	NodeLog(ptr_p) :p(_p) {}
	std::vector<ptr> getAllPreq() const {
		return { p };
	}
	std::vector<ptr> getPreq(Symbol sym)const {
		if (p->visited == sym)return {};
		return { p };
	}
	void eval(Symbol sym) {
		if (p->getValue() <= 0) {
			throw Error("LOG operator's input must be positive");
		}
		else {
			value = log(p->getValue());
			version = sym;
		}
	}
}
cgragh::Expression log(cgragh::Expression) {
	return std::make_shared<NodeLog>(a);
}

class NodeExp :public Node {
private:
	ptr p;
public:
	NodeExp(ptr_p) :p(_p) {}
	std::vector<ptr> getAllPreq() const {
		return { p };
	}
	std::vector<ptr> getPreq(Symbol sym)const {
		if (p->visited == sym)return {};
		return { p };
	}
	void eval(Symbol sym) {
		value = exp(p->getValue());
		version = sym;
	}
}
cgragh::Expression exp(cgragh::Expression) {
	return std::make_shared<NodeExp>(a);
}

class NodeTanh :public Node {
private:
	ptr p;
public:
	NodeExp(ptr_p) :p(_p) {}
	std::vector<ptr> getAllPreq() const {
		return { p };
	}
	std::vector<ptr> getPreq(Symbol sym)const {
		if (p->visited == sym)return {};
		return { p };
	}
	void eval(Symbol sym) {
		value = 1.0 / (exp(p->getValue()) + exp(-p->getValue()));
		version = sym;
	}
}
cgragh::Expression tanh(cgragh::Expression) {
	return std::make_shared<NodeTanh>(a);
}

class NodeSigmoid :public Node {
private:
	ptr p;
public:
	NodeExp(ptr_p) :p(_p) {}
	std::vector<ptr> getAllPreq() const {
		return { p };
	}
	std::vector<ptr> getPreq(Symbol sym)const {
		if (p->visited == sym)return {};
		return { p };
	}
	void eval(Symbol sym) {
		if (p->getValue() > 0)value = 1.0;
		else if (p->getValue() == 0)value == 0.0;
		else value == -1.0;
		version = sym;
	}
}
cgragh::Expreesion sigmoid(cgragh::Expression) {
	return std::make_shared<NodeSIgmoid>(a);
}

class NodeCmp1 :public Node {
private:
	ptr a, b;
	public：
		NodeCmp1(ptr_a, ptr_b) :a(_a), b(_b) {}
	std::vector<ptr> getAllPreq()const {
		return { a,b };
	}
	std::vector<ptr>getPreg(Symbol sym)const {
		return{ a,b };
	}
	void eval(Symbol sym) {
		if (a->getValue() > b->getValue())value = 1.0;
		else value = 0.0;
		version = sym;
	}
}
cgragh::Expression operator > (cgragh::Expression a, cgragh::Expression b) {
	return std::make_shared<NodeCmp1>(a, b);
}

class NodeCmp2 :public Node {
private:
	ptr a, b;
	public：
		NodeCmp1(ptr_a, ptr_b) :a(_a), b(_b) {}
	std::vector<ptr> getAllPreq()const {
		return { a,b };
	}
	std::vector<ptr>getPreg(Symbol sym)const {
		return{ a,b };
	}
	void eval(Symbol sym) {
		if (a->getValue() < b->getValue())value = 1.0;
		else value = 0.0;
		version = sym;
	}
}
cgragh::Expression operator < (cgragh::Expression a, cgragh::Expression b) {
	return std::make_shared<NodeCmp2>(a, b);
}

class NodeCmp3 :public Node {
private:
	ptr a, b;
	public：
		NodeCmp1(ptr_a, ptr_b) :a(_a), b(_b) {}
	std::vector<ptr> getAllPreq()const {
		return { a,b };
	}
	std::vector<ptr>getPreg(Symbol sym)const {
		return{ a,b };
	}
	void eval(Symbol sym) {
		if (a->getValue() >= b->getValue())value = 1.0;
		else value = 0.0;
		version = sym;
	}
}
cgragh::Expression operator >= (cgragh::Expression a, cgragh::Expression b) {
	return std::make_shared<NodeCmp3>(a, b);
}

class NodeCmp4 :public Node {
private:
	ptr a, b;
	public：
		NodeCmp1(ptr_a, ptr_b) :a(_a), b(_b) {}
	std::vector<ptr> getAllPreq()const {
		return { a,b };
	}
	std::vector<ptr>getPreg(Symbol sym)const {
		return{ a,b };
	}
	void eval(Symbol sym) {
		if (a->getValue() <= b->getValue())value = 1.0;
		else value = 0.0;
		version = sym;
	}
}
cgragh::Expression operator <= (cgragh::Expression a, cgragh::Expression b) {
	return std::make_shared<NodeCmp4>(a, b);
}

class NodeCmp5 :public Node {
private:
	ptr a, b;
	public：
		NodeCmp1(ptr_a, ptr_b) :a(_a), b(_b) {}
	std::vector<ptr> getAllPreq()const {
		return { a,b };
	}
	std::vector<ptr>getPreg(Symbol sym)const {
		return{ a,b };
	}
	void eval(Symbol sym) {
		if (a->getValue() == b->getValue())value = 1.0;
		else value = 0.0;
		version = sym;
	}
}
cgragh::Expression operator == (cgragh::Expression a, cgragh::Expression b) {
	return std::make_shared<NodeCmp5>(a, b);
}

class NodeCond :public Node {
private:
	ptr a, b, c;
public:
	NodeCond(ptr_a, ptr_b, ptr_c) :a(_a), b(_b), c(_c) {};
	std::vector<ptr> getAllPreq()const {
		return { a,b,c };
	}
	std::vector<ptr>getPreg(Symbol sym)const {
		std::vector<ptr>list;
		if (a->visited != sym) {
			list.push_back(a);
		}
		if (b->visited != sym) {
			list.push_back(b);
		}
		if (c->visited != sym) {
			list.push_back(c);
		}
		return list;
	}
	void eval(Symbol sym) {
		if (a->getVersion() == version && b->getVersion() == version && b->getValue() == version) {
			return;
		}
		if (a->getValue() > 0) {
			value = b->getValue();
		}
		if (a->getValue() <= 0) {
			value = c->getValue();
		}
		version = sym;
	}
}
cgragh::Expression cond(cgragh::Expression a, cgragh::Expression b, cgragh::Expression c) {
	return std::make_shared<NodeCond>(a, b, c);
}















