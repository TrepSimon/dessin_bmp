
#define _USE_MATH_DEFINES
#include <iostream>
#include "bmp.h"
#include "Parser.h"
#include "Draw.h"
#include <string>

#define P1_position param1->position
#define P2_position param2->position
#define P_bool parametre->at(3)->parametreBool
#define P2_int param2->parametreInt

void dessiner(bmp* b, Draw* draw, std::vector<Data*>* parametre) {
    std::string methode = parametre->at(0)->methode;
    Data *param1 = parametre->at(1);
    Data *param2 = parametre->at(2);


    if (methode == "ligne") {
        draw->ligne(b, P1_position, P2_position);
    }
    else if (methode == "rectangle") {
        draw->rectangle(b, P1_position, P2_position);
    }
    else if (methode == "carre") {
        draw->carre(b, P1_position, P2_position);
    }
    else if (methode == "cercle") {
        draw->cercle(b, P1_position, P2_int);
    }
    else if (methode == "sinus") {
        draw->sinus(b, P1_position, P2_int, parametre->at(3)->parametreInt);
    }
    else if (methode == "cosinus") {
        draw->cosinus(b, P1_position, P2_int, parametre->at(3)->parametreInt);
    }
    else if (methode == "tangente") {
        draw->tangente(b, P1_position, P2_int, parametre->at(3)->parametreInt);
    }
    else if (methode == "triangle_rectangle") {
        draw->triangle_rectangle(b, P1_position, P2_position);
    }
    else if (methode == "triangle_equilateral") {
        draw->triangle_equilateral(b, P1_position, P2_position, P_bool);
    }
    else if (methode == "help") {
        std::cout << "help\n";
    }
}


int main(){
    int w, h;
    w = 500;
    h = 500;
	bmp* b = new bmp(w, h);
    Parser* parser = new Parser();
    Draw* draw = new Draw();
    auto *parametre = new std::vector<Data*>();

    std::string input = "";
    
    std::cout << "--help {methode}" << std::endl;
    do{
        std::cout << "commande: ";
        
        std::getline(std::cin, input);

        if (input == "save")break;

        parser->changeExpression(input);

        for (auto data : *parametre) {
            delete data;
        }
        parametre->clear();

        if (!parser->Valide(parametre)) {
            std::cout << "erreur de parsing\n";
            continue;
        }

        dessiner(b, draw, parametre);

        b->saveFile();
    } while (input != "save");
    

	b->saveFile();

	delete b;
    delete parser;
    delete draw;
}

