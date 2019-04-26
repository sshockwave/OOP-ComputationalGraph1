#pragma once
#include "Expression.h"
#include <iostream>
#include <string>

cgraph::Expression operator + (cgraph::Expression,cgraph::Expression);

cgraph::Expression print(cgraph::Expression,std::string,std::ostream& =std::cout);

//TODO more operators
