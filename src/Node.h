#pragma once
#include <vector>
#include <memory>

namespace cgraph{
	class Node;
	typedef std::shared_ptr<Node>ptr;
	class Node{
		public:
			virtual ~Node();
			virtual std::vector<ptr> getPrec() const=0;
			virtual float eval(std::vector<float>) const=0;
	};
}
