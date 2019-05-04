#pragma once
#include "Symbol.h"
#include <vector>
#include <memory>

namespace cgraph{
	/**
	 * num_t
	 *
	 * The type to store numbers
	 */
	typedef float num_t;
	/**
	 * Node
	 */
	class Node{
		protected:
			/**
			 * Node::version
			 *
			 * The last version in which the node was updated.
			 */
			Symbol version;
			/**
			 * Node::value
			 *
			 * The value in the current round of calculation.
			 */
			num_t value;
		public:
			/**
			 * Node::visited
			 *
			 * Marks if this node has been visited
			 * in the current round of calculation.
			 */
			Symbol visited;
			/**
			 * ptr
			 *
			 * Garbage collection ported to C++.
			 * Requires C++ 11.
			 */
			typedef std::shared_ptr<Node> ptr;
			virtual ~Node();
			/**
			 * Node::getAllPreq
			 *
			 * Get all possible prerequisites for this node.
			 */
			virtual std::vector<ptr> getAllPreq() const=0;
			/**
			 * Node::getPreq
			 *
			 * Get prerequisites for this node.
			 * Be sure to calculate those first.
			 * Loop to check if all preq. are calculated.
			 * Potential usage: short-circuiting conditional statements.
			 */
			virtual std::vector<ptr> getPreq(Symbol=Symbol()) const=0;
			/**
			 * Node::eval
			 *
			 * Modified members: version, value
			 * Calculate and store the value into 'value'.
			 * If updated, set version to the symbol in the parameter.
			 */
			virtual void eval(Symbol=Symbol())=0;
			/**
			 * Node::getVersion
			 */
			Symbol getVersion() const;
			/**
			 * Node::getValue
			 *
			 * constexpr is disabled due to gcc bug
			 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66297
			 */
			num_t getValue() const;
	};
}
