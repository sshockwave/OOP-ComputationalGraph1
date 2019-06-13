#include "Data_Node.h"

//数据基类的实现

string Data_Node::get_name()
{
    return name;
}

string Data_Node::get_type()
{
    return type;
}

void Data_Node::clear_buffer()
{
	if (type == "Placeholder") {
		value = 0;
		assigned = false;
	}
	if(prev_Operation!=nullptr)
		prev_Operation->clear_buffer();
}
