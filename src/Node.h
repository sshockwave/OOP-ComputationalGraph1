#pragma once
#include <vector>
#include <memory>
#include <tuple>

namespace cgraph{
	/**
	 * Node
	 *
	 * Basic ideas are similar to
	 * http://www.deepideas.net/deep-learning-from-scratch-i-computational-graphs/
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
			virtual ~Node()=0;
			/**
			 * yield_t
			 *
			 * Yield type for intermediate states.
			 */
			struct yield_t{
				std::vector<ptr>vec;
				float val;
			};
			/**
			 * Node::eval
			 *
			 * Calculate the node's value.
			 * If the vector passed does not contain enough values,
			 * the function shall return a non-empty vector that
			 * specifies the nodes to be calculated.
			 * The calculated values shall then be appended to the vector
			 * in respective order
			 * and the function will be called again and again
			 * until the returned vector is empty.
			 * The float returned in the final call will be used as the node's value.
			 */
			virtual yield_t eval(const std::vector<float>& ={}) const=0;
	};
}
