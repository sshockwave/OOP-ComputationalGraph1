#pragma once
#include "Expression.h"

namespace cgraph{
	/**
	 * Placeholder
	 *
	 * This class does nothing
	 * but holding a pointer
	 * which can be used as an index
	 */
	class Placeholder{
		public:
			Placeholder();
			operator Expression() const;
	};
	class Constant{
		public:
			Constant(float);
			operator Expression() const;
			/**
			 * Constant::value
			 *
			 * returns the value of the constant
			 */
			float value() const;
	};
	class Variable{
		private:
			float *fp;
			ptr p;
		public:
			Variable(float=0);
			operator Expression() const;
			float value() const;
			Variable& operator = (float);
	};
}
