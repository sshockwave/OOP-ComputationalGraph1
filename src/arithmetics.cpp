#include "arithmetics.h"

namespace cgraph{
	class AddNode:public Node{
		private:
			ptr a,b;
		public:
			~AddNode(){}
			AddNode(ptr _a,ptr _b):a(_a),b(_b){}
			std::vector<ptr> getPrec() const{
				return {a,b};
			}
			float eval(std::vector<float>vec) const{
				return vec[0]+vec[1];
			}
	};
	Expression operator + (Expression a,Expression b){
		ptr r=std::make_shared<AddNode>(a.getPtr(),b.getPtr());
	}
}
