#include "Data_Node.h"

//数据+基类的实现

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
	reset_state();
	if(prev_Operation!=nullptr)
		prev_Operation->clear_buffer();
}//递归清空缓存
