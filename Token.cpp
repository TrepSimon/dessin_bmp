#include "Token.h"
 Token::Token(std::string expression, ExpressionType type) {
	this->expression = expression;
	expressionType = type;
}
