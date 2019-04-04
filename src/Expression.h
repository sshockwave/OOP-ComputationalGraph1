#pragma once
#include "Node.h"

namespace cgraph{
	class Expression{
		private:
			const ptr p;
		public:
			Expression(ptr);
			/**
			 * Expression::getPtr
			 * 
			 * Returns the pointer
			 */
			ptr getPtr() const;
	};
}
