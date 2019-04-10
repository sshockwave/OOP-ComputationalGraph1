#pragma once
#include "Node.h"

namespace cgraph{
	class Expression{
		private:
			const Node::ptr ptr;
		public:
			Expression(Node::ptr);
			/**
			 * Expression::getPtr
			 * 
			 * Returns the pointer
			 */
			Node::ptr getPtr() const;
	};
}
