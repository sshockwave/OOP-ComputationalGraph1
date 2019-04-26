#pragma once
#include <stdexcept>
namespace cgraph{
	class Error: public std::runtime_error{
		using std::runtime_error::runtime_error;
	};
}
