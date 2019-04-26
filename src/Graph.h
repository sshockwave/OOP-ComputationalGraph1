#pragma once
#include "sinks.h"
#include <map>
#include <string>

namespace cgraph{
	class Graph{
		private:
			std::map<Expression,std::string>symbols;
			std::map<std::string,Expression>expressions;
			std::map<std::string,Placeholder>placeholders;
			std::map<std::string,Constant>constants;
			std::map<std::string,Variable>variables;
		public:
			/**
			 * Graph::define
			 *
			 * If the variable did not exist,
			 * the function inserts the object and returns true.
			 */
			bool define(std::string,Expression);
			bool define(std::string,Placeholder);
			bool define(std::string,Constant);
			bool define(std::string,Variable);

			/**
			 * Graph::remove
			 *
			 * If the variable existed,
			 * the function removes the object and returns true.
			 */
			bool remove(std::string);
			bool remove(Expression);

			std::string getName(Expression);
			Expression getExpression(std::string);
			Placeholder getPlaceholder(std::string);
			Constant getConstant(std::string);
			Variable getVariable(std::string);

			std::vector<Expression> getNodeList();
			std::vector<Expression> getExpressionList();
			std::vector<Placeholder> getPlaceholderList();
			std::vector<Constant> getConstantList();
			std::vector<Variable> getVariableList();
	};
}
