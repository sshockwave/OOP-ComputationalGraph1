#pragma once
#include "Expression.h"
#include <iostream>
#include <string>

//10%
cgraph::Expression operator + (cgraph::Expression,cgraph::Expression);
cgraph::Expression operator - (cgraph::Expression,cgraph::Expression);
cgraph::Expression operator * (cgraph::Expression,cgraph::Expression);
cgraph::Expression operator / (cgraph::Expression,cgraph::Expression);

//3%
cgraph::Expression sin(cgraph::Expression);
cgraph::Expression log(cgraph::Expression);
cgraph::Expression exp(cgraph::Expression);
cgraph::Expression tanh(cgraph::Expression);
cgraph::Expression sigmoid(cgraph::Expression);

//3%
cgraph::Expression print(cgraph::Expression,std::string,std::ostream& =std::cout);

//3%
cgraph::Expression operator > (cgraph::Expression,cgraph::Expression);
cgraph::Expression operator < (cgraph::Expression,cgraph::Expression);
cgraph::Expression operator >= (cgraph::Expression,cgraph::Expression);
cgraph::Expression operator <= (cgraph::Expression,cgraph::Expression);
cgraph::Expression operator == (cgraph::Expression,cgraph::Expression);

//3%
cgraph::Expression cond(cgraph::Expression,cgraph::Expression,cgraph::Expression);
