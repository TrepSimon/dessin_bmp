#pragma once
#include <iostream>

enum ExpressionType {
	METHODE,
	PARAM,
	HELP,
	OPTION,
};
enum Methode {
	LIGNE,
	RECTANGLE,
	CARRE,
	CERCLE,
	SINUS,
	COSINUS,
	TANGENTE,
	TRIANGLE_RECTANGLE,
	TRIANGLE_EQUILATERAL,
	HELPER,
	INVALIDE,
};

enum Option {
	FILL,
};


class Token{
public:
	std::string expression;
	ExpressionType expressionType;
	Methode nom_methode;

	Token(std::string, ExpressionType, Methode);
};

