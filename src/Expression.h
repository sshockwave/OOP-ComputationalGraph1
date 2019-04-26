#pragma once
#include "Node.h"
#include <memory>

namespace cgraph{
	class Expression{
		private:
			const Node::ptr ptr;
		public:
			template<class T> Expression(std::make_shared<T> p):ptr(p){}
			operator Node::ptr();
			num_t eval(Symbol=Symbol()) const;
	};
}
