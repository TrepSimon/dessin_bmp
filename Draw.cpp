#include "Draw.h"
#include <queue>
#define rouge 255,0,0
#define bleu 0,0,255
#define vert 0,255,0

Draw::Draw(){}

void Draw::swap_position(Position*& p2, Position*& p1) {
    Position* temp;

    temp = p1;
    p1 = p2;
    p2 = temp;

    temp = new Position(1, 2);
    delete temp;
}

void Draw::fill(bmp* b, int x, int y) {
    std::queue<Position*> liste;
    liste.push(new Position(x, y));

    while (!liste.empty()) {
        Position* courant = liste.front();
        int cx = courant->x, cy = courant->y;
        liste.pop();
        if (b->pixelEstVide(cx, cy)) {
            b->setPixel(cx, cy, rouge);

            liste.push(new Position(cx, cy + 1));
            liste.push(new Position(cx, cy - 1));
            liste.push(new Position(cx + 1, cy));
            liste.push(new Position(cx - 1, cy));
        }

        delete courant;
    }
    return;
}

#define ratio(ligne) ((float)(ligne - p1->y)) / delta_y
void Draw::ligne_vertical(bmp* b, Position* p1, Position* p2) {
    if (p1->y > p2->y)swap_position(p2, p1);

    int delta_x = p2->x - p1->x;
    int delta_y = p2->y - p1->y;

    for (int ligne = p1->y; ligne < p2->y; ligne++) {
        int x;

        x = round(ratio(ligne) * delta_x + p1->x);


        b->setPixel(x, ligne, rouge);
    }
}


void Draw::ligne_horizontal(bmp* b, Position* p1, Position* p2) {
    if (p1->x > p2->x)swap_position(p2, p1);

    int delta_x = p2->x - p1->x;
    int delta_y = p2->y - p1->y;
    float ratio;

    if (delta_y != 0) {
        ratio = (float)delta_y / (float)delta_x;
    }
    else ratio = 0;

    int k = p1->y;

    for (int col = p1->x; col < p2->x; col++) {
        int y;

        y = round(ratio * (col - p1->x) + k);


        b->setPixel(col, y, rouge);
    }
}

void Draw::ligne(bmp* b, Position* p1, Position* p2) {
    if (p1->x > p2->x)swap_position(p2, p1);

    ligne_horizontal(b, p1, p2);
    ligne_vertical(b, p1, p2);
}

void Draw::rectangle(bmp* b, Position* p1, Position* p2, bool toFill) {
    if (p1->x > p2->x)swap_position(p2, p1);

    Position* coin_droit = new Position(p2->x, p1->y);
    Position* coin_gauche = new Position(p1->x, p2->y);

    ligne(b, p1, coin_droit);
    ligne(b, coin_droit, p2);
    ligne(b, p2, coin_gauche);
    ligne(b, coin_gauche, p1);

    if (toFill) {
        int x = (p2->x + p1->x) / 2;
        int y = (p2->y + p1->y) / 2;
        fill(b, x, y);
    }
    delete coin_droit, coin_gauche;
}

void Draw::carre(bmp* b, Position* p1, Position* p2, bool toFill) {
    if (abs(p1->x - p2->x) != abs(p1->y - p2->y)) {
        std::cout << "impression d'un carre impossible\n";
        return;
    }

    rectangle(b, p1, p2, toFill);
}

void Draw::cercle(bmp* b, Position* centre, int rayon, bool toFill) {
    if ((centre->x + rayon) >= 500 || (centre->y + rayon) >= 500 || (centre->y - rayon) < 0 || (centre->x - rayon) < 0) {
        std::cout << "impression d'un cercle impossible\n";
        return;
    }

    Position* precedent = new Position(centre->x , centre->y + rayon);

    for (int angle = 0; angle < 360; angle++) {
        int x, y;
        double rad = angle * M_PI / 180;

        x = (rayon * sin(rad)) + centre->x;
        y = (rayon * cos(rad)) + centre->y;

        Position* courant = new Position(x, y);

        b->setPixel(x, y, rouge);
        ligne(b, precedent, courant);

        delete precedent;
        precedent = courant;
    }
    delete precedent;

    if (toFill)fill(b, centre->x, centre->y);
}

void Draw::sinus(bmp* b, Position* centre, int rayon, int paramB) {
    Position* avant = new Position(0, centre->y);

    int x = 0;
    for (int angle = 0; angle < b->width; angle++) {
        int y;
        double rad = angle * M_PI / 180;

        y = (rayon * sin(rad * paramB)) + centre->y;

        ligne(b, avant, new Position(x, y));
        delete avant;
        avant = new Position(x, y);
        x++;
    }
    delete avant;
}

void Draw::cosinus(bmp* b, Position* centre, int rayon, int paramB) {
    Position* avant = new Position(0, centre->y + rayon);

    int x = 0;
    for (int angle = 0; angle < b->width; angle++) {
        int y;
        double rad = angle * M_PI / 180;

        y = (rayon * cos(rad * paramB)) + centre->y;

        ligne(b, avant, new Position(x, y));
        delete avant;
        avant = new Position(x, y);
        x++;
    }
    delete avant;
}

void Draw::tangente(bmp* b, Position* centre, int rayon, int paramB) {
    Position* avant = new Position(0, centre->y);

    int x = 0;
    for (int angle = 0; angle < b->width; angle++) {
        int y;
        double rad = angle * M_PI / 180;

        y = (rayon * tan(rad * paramB)) + centre->y;

        if (y > b->height) {
            y = b->height;
        }
        else if (y < 0) {
            y = 0;
        }

        if ((avant->y == 0 && y == 0) || (avant->y > 0 && y == 0)) {
            delete avant;
            avant = new Position(x, y);
            x++;
            continue;
        }

        ligne(b, avant, new Position(x, y));

        delete avant;
        avant = new Position(x, y);
        x++;
        b->saveFile();
    }
    delete avant;
}

void Draw::triangle_rectangle(bmp* b, Position* p1, Position* p2, bool toFill) {
    if (p1->y == p2->y)std::cout << "ne doit pas etre sur la meme ligne";

    if (p1->x > p2->x)swap_position(p2, p1);
    Position* angle_droit;

    //toujour avoir l'angle vers le bas
    if (p1->y > p2->y) {
        angle_droit = new Position(p1->x, p2->y);
    }
    else angle_droit = new Position(p2->x, p1->y);

    ligne(b, p1, p2);
    ligne(b, p1, angle_droit);
    ligne(b, p2, angle_droit);

    b->setPixel(p1->x, p1->y, rouge);
    b->setPixel(p2->x, p2->y, rouge);
    b->setPixel(angle_droit->x, angle_droit->y, rouge);

    if (toFill) {
        int x = (p1->x + angle_droit->x) / 2;
        int y = (p1->y + p2->y) / 2;
        fill(b, x, y);
    }

    delete angle_droit;
}

void Draw::triangle_equilateral(bmp* b, Position* p1, Position* p2, bool vers_haut, bool toFill) {
    if (p1->x > p2->x)swap_position(p2, p1);

    int delta_x = (p1->x - p2->x);
    int delta_y = (p1->y - p2->y);
    Position* p3;
    int x;
    int y;

    int longueur = sqrt(pow(delta_x, 2) + pow(delta_y, 2));

    x = p2->x - (longueur / 2);

    y = sqrt(abs(pow(longueur, 2) - pow(x, 2)));

    if (vers_haut) {
        if (p1->y + y <= 500) p3 = new Position(x, p1->y + y);
        else p3 = new Position(x, p1->y - y);
    }
    else {
        if (p1->y - y >= 0)p3 = new Position(x, p1->y - y);
        else p3 = new Position(x, p1->y + y);
    }

    ligne(b, p1, p2);
    ligne(b, p1, p3);
    ligne(b, p2, p3);

    b->setPixel(p3->x, p3->y, rouge);

    if (toFill) {
        int x = (p1->x + p2->x) / 2;
        int y = (p1->y + p3->y) / 2;
        fill(b, x, y);
    }
    delete p3;
}