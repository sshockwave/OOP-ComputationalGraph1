#include "Graph.h"
#include "Error.h"

namespace cgraph{
	void Graph::define(std::string name,Expression expr){
		expressions.insert(std::make_pair(name,expr));
	}
	void Graph::define(std::string name,Placeholder ph){
		define(name,static_cast<Expression>(ph));
		placeholders.insert(std::make_pair(name,ph));
	}
	void Graph::define(std::string name,Constant cnst){
		define(name,static_cast<Expression>(cnst));
		constants.insert(std::make_pair(name,cnst));
	}
	void Graph::define(std::string name,Variable varb){
		//var is a keyword in many languages
		define(name,static_cast<Expression>(varb));
		variables.insert(std::make_pair(name,varb));
	}

	template<class T>inline void removeFromMap(T &m,std::string name,Expression expr){
		auto it=m.find(name);
		Expression found=it->second;
		if(static_cast<Node::ptr>(found)==static_cast<Node::ptr>(expr)){
			m.erase(it);
		}
	}
	bool Graph::remove(std::string name){
		auto it=expressions.find(name);
		if(it==expressions.end()){
			return false;
		}
		removeFromMap(placeholders,name,it->second);
		removeFromMap(constants,name,it->second);
		removeFromMap(variables,name,it->second);
		symbols.erase(it->second);
		expressions.erase(it);
		return true;
	}
	bool Graph::remove(Expression expr){
		auto it=symbols.find(expr);
		if(it==symbols.end()){
			return false;
		}
		removeFromMap(expressions,it->second,it->first);
		removeFromMap(placeholders,it->second,it->first);
		removeFromMap(constants,it->second,it->first);
		removeFromMap(variables,it->second,it->first);
		symbols.erase(expr);
		return true;
	}

	std::string Graph::getName(Expression expr) const{
		auto it=symbols.find(expr);
		if(it==symbols.end()){
			throw Error("Expression not found");
		}
		return it->second;
	}
	Expression Graph::getExpression(std::string name) const{
		auto it=expressions.find(name);
		if(it==expressions.end()){
			throw Error("Expression \""+name+"\" not found");
		}
		return it->second;
	}
	Placeholder Graph::getPlaceholder(std::string name) const{
		auto it=placeholders.find(name);
		if(it==placeholders.end()){
			throw Error("Placeholders \""+name+"\" not found");
		}
		return it->second;
	}
	Constant Graph::getConstant(std::string name) const{
		auto it=constants.find(name);
		if(it==constants.end()){
			throw Error("Constant \""+name+"\" not found");
		}
		return it->second;
	}
	Variable Graph::getVariable(std::string name) const{
		auto it=variables.find(name);
		if(it==variables.end()){
			throw Error("Variable \""+name+"\" not found");
		}
		return it->second;
	}

	template<class T>std::vector<T> mapToVector(const std::map<std::string,T>&m){
		std::vector<T> vec;
		vec.reserve(m.size());
		for(const auto &it:m){
			vec.push_back(it.second);
		}
		return vec;
	}
	std::vector<Expression> Graph::getExpressionList() const{
		return mapToVector(expressions);
	}
	std::vector<Placeholder> Graph::getPlaceholderList() const{
		return mapToVector(placeholders);
	}
	std::vector<Constant> Graph::getConstantList() const{
		return mapToVector(constants);
	}
	std::vector<Variable> Graph::getVariableList() const{
		return mapToVector(variables);
	}
}
