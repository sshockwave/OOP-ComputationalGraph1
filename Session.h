#ifndef INC_SESSION_H
#define INC_SESSION_H

#include <iostream>
#include <map>
#include <string>

class Session{
	public:
		std::map<std::string,float>values;
		void set(std::string name,float val);
		void clear();
		friend std::ostream & operator << (std::ostream& out,const Session &sess);
		friend std::istream & operator >> (std::istream& in,Session &sess);
};

#endif//INC_SESSION_H