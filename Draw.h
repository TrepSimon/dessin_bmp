#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include "bmp.h"
#include <math.h>
#include "Position.h"

#define ratio(ligne) ((float)(ligne - p1->y)) / delta_y

class Draw{
    void swap_position(Position*&, Position*&);
    void ligne_vertical(bmp*, Position*, Position*);
    void ligne_horizontal(bmp*, Position*, Position*);
public:
    Draw();
    void ligne(bmp*, Position*, Position*);
    void carre(bmp*, Position*, Position*);
    void rectangle(bmp*, Position*, Position*);
    void cercle(bmp*, Position*, int);
    void sinus(bmp*, Position*, int, int);
    void cosinus(bmp*, Position*, int, int);
    void tangente(bmp*, Position*, int, int);
    void triangle_rectangle(bmp*, Position*, Position*);
    void triangle_equilateral(bmp*, Position*, Position*, bool);

};

