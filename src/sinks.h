#pragma once
#include "Expression.h"
#include <map>

namespace cgraph{
	class Placeholder{
		private:
			Node::ptr ptr;
		public:
			Placeholder();
			operator Expression() const;
			void set(num_t,Symbol) const;
			bool operator < (const Placeholder&) const;
	};

	class Constant{
		public:
			Constant(num_t);
			operator Expression() const;
			num_t eval() const;
			bool operator < (const Constant&) const;
	};

	class Variable{
		public:
			Variable(num_t=0);
			operator Expression() const;
			num_t eval() const;
			void set(num_t) const;
			Variable& operator = (num_t) const;
			bool operator < (const Variable&) const;
	};
}

float eval(cgraph::Expression,std::map<cgraph::Placeholder,cgraph::num_t> ={});
