#pragma once
#include "Node.h"
#include <memory>

namespace cgraph{
	class Expression{
		private:
			const Node::ptr ptr;
		public:
			template<class T> Expression(std::shared_ptr<T>p):ptr(p){}
			operator Node::ptr();
			num_t eval(Symbol=Symbol()) const;
	};
}
namespace std{
	template<> struct owner_less<cgraph::Expression>{
		bool operator () (cgraph::Expression,cgraph::Expression) const;
	};
}
