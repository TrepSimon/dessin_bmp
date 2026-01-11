
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

#define help_2_position(nom) std::cout<<nom << " x/y x/y\n{forme} {position(int/int)} {position(int/int)}\n"
#define help_cercle std::cout<<"cercle x/y r\n{forme} {position(int/int) {rayon(int)}\n"
#define help_trigo(nom) std::cout<< nom << " x/y r b\n{forme} {position(int/int)} {rayon(int)} {b(int)}\n"
#define help_equi std::cout<<"triangle_equilateral x/y x/y true/false\n{forme} {position(int/int)} {position(int/int)} {booleen(va vers le haut(true)) sinon false\n"

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

Methode get_methode(std::string methode) {
    if (methode == "ligne")return LIGNE;
    else if (methode == "rectangle") return RECTANGLE;
    else if (methode == "carre") return CARRE;
    else if (methode == "cercle") return CERCLE;
    else if (methode == "sinus") return SINUS;
    else if (methode == "cosinus") return COSINUS;
    else if (methode == "tangente") return TANGENTE;
    else if (methode == "triangle_rectangle") return TRIANGLE_RECTANGLE;
    else if (methode == "triangle_equilateral") return TRIANGLE_EQUILATERAL;
    else if (methode == "help")return HELPER;
    else return INVALIDE;
}

void dessiner(bmp* b, Draw* draw, std::vector<Data*>* parametre) {
    std::string methodeString = parametre->at(0)->methode;
    Methode methode = get_methode(methodeString);
    bool isHelper = methode == HELPER;
    Data *param1 = parametre->at(1);


    if(!isHelper){
        Data* param2 = parametre->at(2);

        switch (methode) {
        case LIGNE:
            draw->ligne(b, P1_position, P2_position);
            break;
        case RECTANGLE:
            draw->rectangle(b, P1_position, P2_position);
            break;
        case CARRE:
            draw->carre(b, P1_position, P2_position);
            break;
        case CERCLE:
            draw->cercle(b, P1_position, P2_int);
            break;
        case SINUS:
            draw->sinus(b, P1_position, P2_int, parametre->at(3)->parametreInt);
            break;
        case COSINUS:
            draw->cosinus(b, P1_position, P2_int, parametre->at(3)->parametreInt);
            break;
        case TANGENTE:
            draw->tangente(b, P1_position, P2_int, parametre->at(3)->parametreInt);
            break;
        case TRIANGLE_RECTANGLE:
            draw->triangle_rectangle(b, P1_position, P2_position);
            break;
        case TRIANGLE_EQUILATERAL:
            draw->triangle_equilateral(b, P1_position, P2_position, P_bool);
            break;
        }
    }
    else {
        Methode helpingMethode = get_methode(param1->methode);
        switch (helpingMethode) {
        case LIGNE:
            help_2_position("ligne");
            break;
        case RECTANGLE:
            help_2_position("rectangle");
            break;
        case CARRE:
            help_2_position("carre");
            break;
        case CERCLE:
            help_cercle;
            break;
        case SINUS:
            help_trigo("sinus");
            break;
        case COSINUS:
            help_trigo("cosinus");
            break;
        case TANGENTE:
            help_trigo("tangente");
            break;
        case TRIANGLE_RECTANGLE:
            help_2_position("triangle_rectangle");
            break;
        case TRIANGLE_EQUILATERAL:
            help_equi;
            break;
        }
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

