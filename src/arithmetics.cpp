#include "arithmetics.h"

namespace cgraph{
	class AddNode:public Node{
		private:
			ptr a,b;
		public:
			AddNode(ptr _a,ptr _b):a(_a),b(_b){}
	};
	Expression operator + (Expression a,Expression b){
		ptr r=std::make_shared<AddNode>(a.getPtr(),b.getPtr());
	}
}
