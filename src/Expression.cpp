#include "Expression.h"
#include "Error.h"
#include <stack>

bool std::owner_less<cgraph::Expression>::operator ()
	(cgraph::Expression a,cgraph::Expression b) const{
		static std::owner_less<cgraph::Node::ptr>cmp;
		return cmp(a,b);
	}
namespace cgraph{
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
		return ptr->getValue();
	}
}
