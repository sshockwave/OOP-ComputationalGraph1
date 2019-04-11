#include "Symbol.h"

using namespace cgraph;

Symbol::Symbol():cnt(new int(1)){}

Symbol::Symbol(const Symbol& s):cnt(s.cnt){
	++*cnt;
}

Symbol::~Symbol(){
	--*cnt;
	if(*cnt==0){
		delete cnt;
	}
}

/*
 * See the copy-and-swap idiom
 * https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
 */
Symbol& Symbol::operator = (Symbol s){
	swap(s);
	return *this;
}

bool Symbol::operator < (const Symbol& s) const{
	return cnt<s.cnt;
}

bool Symbol::operator == (const Symbol& s) const{
	return cnt==s.cnt;
}

bool Symbol::operator != (const Symbol& s) const{
	return cnt!=s.cnt;
}

void Symbol::swap(Symbol& s){
	std::swap(cnt,s.cnt);
}

template<> void std::swap(cgraph::Symbol& a,cgraph::Symbol& b){
	a.swap(b);
}
