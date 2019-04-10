#pragma once
#include <vector>
#include <memory>

namespace cgraph{
	/**
	 * Node
	 *
	 * Basic ideas are similar to
	 * http://www.deepideas.net/deep-learning-from-scratch-i-computational-graphs/
	 * Ported to C++.
	 */
	class Node{
		public:
			/**
			 * ptr
			 *
			 * Garbage collection ported to C++.
			 * Requires C++ 11.
			 */
			typedef std::shared_ptr<Node> ptr;
			virtual ~Node();
			/**
			 * Node::getPrec
			 *
			 * Get the list of input nodes.
			 */
			virtual std::vector<ptr> getPrec() const=0;
			/**
			 * Node::eval
			 *
			 * Calculate the node's value
			 * based on input values.
			 * The order of input values
			 * should be the same as the order
			 * given in getPrec.
			 * For nodes that are not yet calculated,
			 * the order of calculation should strictly follow
			 * the order in the vector.
			 */
			virtual float eval(std::vector<float>) const=0;
	};
}
