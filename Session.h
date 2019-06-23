#ifndef INC_SESSION_H
#define INC_SESSION_H

#include <iostream>
#include <map>
#include <string>

class Session{
	public:
		std::map<std::string,float>values;//储存但前名字有效的Variable
		void set(std::string name,float val);
		void clear();
		friend std::ostream & operator << (std::ostream& out,const Session &sess);//输出
		friend std::istream & operator >> (std::istream& in,Session &sess);//输入
};

#endif//INC_SESSION_H
