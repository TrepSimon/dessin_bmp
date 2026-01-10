#pragma once
#include <iostream>

enum ExpressionType {
	METHODE,
	PARAM,
	HELP,
};

class Token{
public:
	std::string expression;
	ExpressionType expressionType;

	Token(std::string, ExpressionType);
};

