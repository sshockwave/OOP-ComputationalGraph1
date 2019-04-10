#include "arithmetics.h"

namespace cgraph{
	class NodeAdd:public Node{
		private:
			ptr a,b;
		public:
			~NodeAdd(){}
			NodeAdd(ptr _a,ptr _b):a(_a),b(_b){}
			std::vector<ptr> getPrec() const{
				return {a,b};
			}
			float eval(std::vector<float>vec) const{
				return vec[0]+vec[1];
			}
	};
	Expression operator + (Expression a,Expression b){
		Node::ptr r=std::make_shared<NodeAdd>(a.getPtr(),b.getPtr());
	}
}
