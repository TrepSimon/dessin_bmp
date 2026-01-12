#include "Token.h"
 Token::Token(std::string expression, ExpressionType type, Methode nom) {
	this->expression = expression;
	expressionType = type;
	this->nom_methode = nom;
}
