
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
#define help_equi std::cout<<"triangle_equilateral x/y x/y true/false\n{forme} {position(int/int)} {position(int/int)} {booleen(va vers le haut(true)) sinon false}\nLes deux points doivent etre sur la meme ligne\n"
#define help_triangle_rec std::cout<<"triangle_rectangle x/y x/y\n{forme} {position(int/int)} {position(int/int)}\nles deux positions sont les deux angles qui ne sont pas a 90\nl'angle a 90 degre est genere vers le bas, a moins de ne pas avoir l'espace\n"
#define new_line std::cout<<"\n\n"

void dessiner_tout_help() {
    help_2_position("ligne");
    new_line;

    help_2_position("rectangle");
    new_line;

    help_2_position("carre");
    new_line;

    help_cercle;
    new_line;

    help_trigo("sinus");
    new_line;

    help_trigo("cosinus");
    new_line;

    help_trigo("tangente");
    new_line;

    help_triangle_rec;
    new_line;

    help_equi;
    new_line;

}

void dessiner(bmp* b, Draw* draw, std::vector<Data*>* parametre) {
    Methode methode = parametre->at(0)->methode;
    bool isHelper = methode == HELPER;

    if (isHelper && parametre->size() == 1) {
        dessiner_tout_help();
        return;
    }

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
            if (P1_position->y != P2_position->y) {
                std::cout << "les deux points doivent etre sur la meme ligne\n";
                break;
            }
            draw->triangle_equilateral(b, P1_position, P2_position, P_bool);
            break;
        }
    }
    else {
        Methode helpingMethode = param1->methode;
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
            help_triangle_rec;
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
            std::cout << "erreur de parsing\ncommande annule\n";
            continue;
        }


        dessiner(b, draw, parametre);

        b->saveFile();
    } while (input != "save");
    

    system("start c:\\temp\\a.bmp");

	delete b;
    delete parser;
    delete draw;
}

