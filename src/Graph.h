#pragma once
#include "sinks.h"
#include <map>
#include <string>

namespace std{
	template<> struct owner_less<cgraph::Expression>{
		bool operator () (cgraph::Expression,cgraph::Expression) const;
	};
}
namespace cgraph{
	class Graph{
		private:
			std::map<Expression,std::string,std::owner_less<Expression>>symbols;
			std::map<std::string,Expression>expressions;
			std::map<std::string,Placeholder>placeholders;
			std::map<std::string,Constant>constants;
			std::map<std::string,Variable>variables;
		public:
			/**
			 * Graph::define
			 *
			 * If the variable exists,
			 * the function overrides it.
			 */
			void define(std::string,Expression);
			void define(std::string,Placeholder);
			void define(std::string,Constant);
			void define(std::string,Variable);

			/**
			 * Graph::remove
			 *
			 * If the variable existed,
			 * the function removes the object and returns true.
			 */
			bool remove(std::string);
			bool remove(Expression);

			std::string getName(Expression) const;
			Expression getExpression(std::string) const;
			Placeholder getPlaceholder(std::string) const;
			Constant getConstant(std::string) const;
			Variable getVariable(std::string) const;

			std::vector<Expression> getExpressionList() const;
			std::vector<Placeholder> getPlaceholderList() const;
			std::vector<Constant> getConstantList() const;
			std::vector<Variable> getVariableList() const;
	};
}
