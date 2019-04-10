#pragma once
#include <vector>
#include <memory>

namespace cgraph{
	class Node;
	class Node{
		public:
			typedef std::shared_ptr<Node> ptr;
			virtual ~Node();
			virtual std::vector<ptr> getPrec() const=0;
			virtual float eval(std::vector<float>) const=0;
	};
}
