#include "Expression.h"
#include "Error.h"
#include <stack>

namespace cgraph{
	Expression::Expression(Node::ptr p):ptr(p){}

	Expression::operator Node::ptr(){
		return ptr;
	}

	num_t Expression::eval(Symbol sym) const{
		std::stack<Node::ptr>stack;
		stack.push(ptr);
		for(;!stack.empty();){
			Node::ptr p=stack.top();
			if(p->visited==sym){
				stack.pop();
				continue;
			}
			bool hasNext=false;
			for(auto q:p->getPreq(sym)){
				if(q->visited!=sym){
					hasNext=true;
					stack.push(q);
				}
			}
			if(!hasNext){
				p->eval(sym);
				p->visited=sym;
				stack.pop();
			}
		}
		return ptr->value;
	}
}
