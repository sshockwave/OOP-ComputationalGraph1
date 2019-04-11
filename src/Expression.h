#pragma once
#include "Node.h"

namespace cgraph{
	class Expression{
		private:
			const Node::ptr ptr;
		public:
			Expression(Node::ptr);
			operator Node::ptr();
			num_t eval(Symbol=Symbol()) const;
	};
}
