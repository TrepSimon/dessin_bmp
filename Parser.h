#pragma once
#include <iostream>
#include <vector>
#include "Token.h"
#include "Position.h"

struct Data {
	Position* position;
	int parametreInt;
	bool parametreBool;
	std::string methode;
};

class Parser{
	std::vector<Token*> *tokens;
	std::vector<std::string> methodes = {"ligne", "rectangle", "carre", "cercle", "sin", "cos", "tan", "triangle_rectangle", "triangle_equilateral"};

	bool isPosition(const Token*, Position**);
	bool isInt(const Token*, int*);
	bool isBool(const Token*, bool*);

public:
	Parser();
	Parser(std::string);

	void changeExpression(std::string);
	ExpressionType getExpressionType(std::string);
	bool Valide(std::vector<Data*>*);
	
};

