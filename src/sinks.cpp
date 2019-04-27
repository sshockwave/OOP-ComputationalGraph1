#include "sinks.h"
#include "Error.h"

namespace cgraph{
	void Placeholder::NodePlaceholder::set(num_t v,const Symbol& s){
		if(value!=v){
			value=v;
			version=s;
		}
		visited=s;
	}

	void Placeholder::NodePlaceholder::eval(Symbol){
		throw Error("Placeholder missing");
	}

	Placeholder::Placeholder():ptr(std::make_shared<NodePlaceholder>()){}

	Placeholder::operator Expression() const{
		return ptr;
	}

	void Placeholder::set(num_t v,const Symbol &s) const{
		ptr->set(v,s);
	}

	bool Placeholder::operator < (const Placeholder& b) const{
		return ptr<b.ptr;
	}

	class NodeConstant{
	};
}

using namespace cgraph;

num_t eval(Expression expr,std::map<Placeholder,num_t>values){
	Symbol sym;
	for(auto it:values){
		it.first.set(it.second,sym);
	}
	return expr.eval(sym);
}
