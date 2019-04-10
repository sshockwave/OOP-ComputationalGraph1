#pragma once
#include "Node.h"
#include "Expression.h"
#include "floattypes.h"
#include <map>
#include <initializer_list>

namespace cgraph{
	/**
	 * Session
	 *
	 * A session stores the temporary results
	 * when evaluating an expression.
	 *
	 * A session shall be immutable.
	 * It takes a snapshot of the current state
	 * and shall not change in reponse to
	 * any modifications to variables nor placeholders.
	 */
	class Session{
		private:
			/**
			 * Session::cache
			 *
			 * Sessions caches results only.
			 *
			 * Values of placeholders are stored together
			 * for simpplicity.
			 *
			 * Resources should be freed
			 * when no where else has a reference,
			 * therefore weak pointers are adopted.
			 */
			std::map<std::weak_ptr<Node>,float,std::owner_less<std::weak_ptr<Node>>> cache;

		public:
			Session()=default;
			/**
			 * Session() initializer list
			 *
			 * Syntax sugar to constructing a session.
			 * e.g. Session sess={{a,3.2},{b,-2}};
			 */
			Session(std::initializer_list<std::pair<Placeholder,float>>);

			/**
			 * Session::define
			 *
			 * Define placeholder values.
			 * Throws if the placeholder value conflicts.
			 */
			void define(Placeholder,float);

			/**
			 * Session::join
			 *
			 * Import values from another session.
			 * Similar to `define`,
			 * `join` shall throws an exceptions
			 * if there are conflicts.
			 */
			void join(const Session&);

			/**
			 * Session::eval
			 * 
			 * Calculate and return the value of the expr
			 */
			float eval(Expression);

			/**
			 * Session::operator[]
			 *
			 * Alias for eval()
			 */
			float operator [] (Expression);

			/**
			 * Session::clean
			 *
			 * Remove expired values.
			 */
			void clean();

			/**
			 * Session::clear
			 *
			 * Empty session
			 */
			void clear();
	};
	/**
	 * eval(Expression,Session)
	 *
	 * Syntax sugar for evaluating an expression.
	 * E.g. eval(expr,{{a,13},{b,-3.5}})
	 */
	float eval(Expression,Session={});
}
