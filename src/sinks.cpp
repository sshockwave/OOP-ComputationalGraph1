#include "sinks.h"
#include "Error.h"

namespace cgraph{
	class NodePlaceholder: public Node{
		void eval(Symbol) override{
			throw Error("Placeholder missing");
		}
	};

	Placeholder::Placeholder():ptr(std::make_shared<NodePlaceholder>()){}

	Placeholder::operator Expression() const{
		return ptr;
	}

	void Placeholder::set(num_t value,Symbol sym) const{
		if(ptr->value!=value){
			ptr->version=sym;
		}
		ptr->value=value;
		ptr->visited=sym;
	}

	bool Placeholder::operator < (const Placeholder& b) const{
		return ptr<b.ptr;
	}
}

using namespace cgraph;

float eval(Expression expr,std::map<Placeholder,num_t>values){
	Symbol sym;
	for(auto it:values){
		it.first.set(it.second,sym);
	}
	return expr.eval(sym);
}
