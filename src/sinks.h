#pragma once
#include "Expression.h"
#include <map>

namespace cgraph{
	class Placeholder{
		private:
			class NodePlaceholder: public Node{
				public:
					void set(num_t,const Symbol&);
					void eval(Symbol) override;
			};
			std::shared_ptr<NodePlaceholder>ptr;
		public:
			Placeholder();
			operator Expression() const;
			void set(num_t v,const Symbol &s) const;
	};

	class Constant{
		private:
			Node::ptr ptr;
		public:
			Constant(num_t);
			operator Expression() const;
			num_t eval() const;
	};

	class Variable{
		public:
			Variable(num_t=0);
			operator Expression() const;
			num_t eval() const;
			void set(num_t) const;
			Variable& operator = (num_t) const;
	};
}

float eval(cgraph::Expression,std::map<cgraph::Placeholder,cgraph::num_t> ={});
