#pragma once
#include <utility>

namespace cgraph{
	class Symbol{
		private:
			int *cnt;
		public:
			Symbol();
			Symbol(const Symbol&);
			~Symbol();
			void swap(Symbol&);
			Symbol& operator = (Symbol);
			bool operator < (const Symbol&) const;
			bool operator == (const Symbol&) const;
			bool operator != (const Symbol&) const;
	};
}

template<> void std::swap(cgraph::Symbol&,cgraph::Symbol&);
