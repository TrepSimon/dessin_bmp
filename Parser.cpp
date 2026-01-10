#include "Parser.h"

Parser::Parser(){
	tokens = new std::vector<Token*>();
}

Parser::Parser(std::string expression) {
	tokens = new std::vector<Token*>();

	changeExpression(expression);
}

void Parser::changeExpression(std::string expression) {
	tokens->clear();
	std::string currentExpression = "";

	for (char lettre : expression) {

		if (lettre != ' ')currentExpression += lettre;
		else {
			if (currentExpression == "")continue;
			ExpressionType type = getExpressionType(currentExpression);
			tokens->push_back(new Token(currentExpression, type));
			currentExpression.clear();
		}
	}
	ExpressionType type = getExpressionType(currentExpression);
	tokens->push_back(new Token(currentExpression, type));
}

ExpressionType Parser::getExpressionType(std::string expression) {

	if (expression == "--help")return HELP;

	for (std::string methode : methodes) {
		if (expression == methode)return METHODE;
	}

	return PARAM;
}

bool Parser::isPosition(const Token *token, Position **out) {
	std::string expression = token->expression;
	int x = 0, y = 0;
	int multiple = 1;
	bool countY = true;

	for (int idx = expression.size() - 1; idx >= 0; --idx) {
		char lettre = expression.at(idx);

		if (lettre >= '0' && lettre <= '9') {
			if (countY)y += (lettre - 48) * multiple;
			else x += (lettre - 48) * multiple;
		}
		else if (lettre == '/') {
			countY = false;
			multiple = 1;
			continue;
		}
		else {
			out = NULL;
			return false;
		}
		multiple *= 10;
	}
	*out = new Position(x, y);

	return true;
}

bool Parser::isInt(const Token* token, int* out) {
	if (token == NULL) {
		out = NULL;
		return false;
	}
	std::string expression = token->expression;
	int multiple = 1;
	*out = 0;

	for (int idx = expression.size() - 1; idx >= 0; --idx) {
		char lettre = expression.at(idx);
		if (lettre >= '0' && lettre <= '9')*out += (lettre - 48) * multiple;
		else {
			out = NULL;
			return false;
		}
	}
	return true;
}

bool Parser::isBool(const Token* token, bool *out) {
	if (token == NULL) {
		out = NULL;
		return false;
	}
	if (token->expression == "true") {
		*out = true;
		return true;
	}
	else if (token->expression == "false") {
		*out = false;
		return true;
	}
	else {
		out = NULL;
		return false;
	}
}
#define tokensIdx(x) tokens->at(x)->expressionType
bool Parser::Valide(std::vector<Data*> *parametre) {
	bool beginWithMethode = tokensIdx(0) == METHODE;
	bool beginWithHelp = tokensIdx(0) == HELP;
	if (!beginWithMethode && !beginWithHelp) {
		parametre = NULL;
		return false;
	}

	std::string methode = tokens->at(0)->expression;
	int size = tokens->size();


	if (beginWithHelp) {
		if (size > 2 || tokensIdx(1) != METHODE) {
			parametre = NULL;
			return false;
		}
		Data *retourHelp = new Data();
		Data* retourMethode = new Data();
		retourHelp->methode = "help";
		retourMethode->methode = tokens->at(1)->expression;
		parametre->push_back(retourHelp);
		parametre->push_back(retourMethode);
		return true;
	}

	Data *retour1 = new Data(), * retour2 = new Data(), * retour3 = new Data();
	bool has3Param = false;

	Token* param1 = tokens->at(1);
	Token* param2 = tokens->at(2);
	Token* param3 = NULL;
	if (tokens->size() > 3)param3 = tokens->at(3);

	if (methode == "ligne" || methode == "rectangle" || methode == "carre" || methode == "triangle_rectangle") {
		if (size != 3)return false;
		if(!(isPosition(param1, &retour1->position) && isPosition(param2, &retour2->position)))return false;
	}
	else if (methode == "cercle") {
		if (size != 3)return false;
		if (!isPosition(param1, &retour1->position) && isInt(param2, &retour2->parametreInt))return false;
	}
	else if (methode == "sin" || methode == "cos" || methode == "tan") {
		if (size != 4)return false;
		if (!isPosition(param1, &retour1->position) && isInt(param2, &retour2->parametreInt) && isInt(param3, &retour3->parametreInt))return false;
		has3Param = true;
	}
	else if (methode == "triangle_equilateral") {
		if (size != 4)return false;
		if (!(isPosition(param1, &retour1->position) && isPosition(param2, &retour2->position)) && !isBool(param3, &retour3->parametreBool))return false;
		has3Param = true;
	}
	Data *retourMethode = new Data();
	retourMethode->methode = methode;

	parametre->push_back(retourMethode);
	parametre->push_back(retour1);
	parametre->push_back(retour2);
	if (has3Param)parametre->push_back(retour3);
	else delete retour3;

	return true;
}
