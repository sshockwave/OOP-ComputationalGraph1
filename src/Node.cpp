#include "Node.h"

namespace cgraph{
	Node::~Node(){}

	std::vector<Node::ptr> Node::getAllPreq() const{
		return {};
	}

	std::vector<Node::ptr> Node::getPreq(Symbol) const{
		return {};
	}

	Symbol Node::getVersion() const{
		return version;
	}
}
