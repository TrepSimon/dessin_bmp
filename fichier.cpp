
#define _USE_MATH_DEFINES
#include <iostream>
#include "bmp.h"
#include "Parser.h"
#include "Draw.h"
#include <string>
#include "Fenetre.h"

#define paddingY 10
#define C_editHeight 30
#define C_baseWidth 500

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

using namespace app;

HWND edit, bitmap, console;
HBITMAP hMap;
int w, h;
int consoleHeight;
bool *isRunning;

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
#define paramLast parametre->at(parametre->size() - 1)
void dessiner(bmp* b, Draw* draw, std::vector<Data*>* parametre) {
    Methode methode = parametre->at(0)->methode;
    bool isHelper = methode == HELPER;
    bool hasOption = paramLast->option != NULL;
    bool toFill = false;

    if (isHelper && parametre->size() == 1) {
        dessiner_tout_help();
        return;
    }

    if (hasOption) {
        std::vector<Option>* options = paramLast->option;

        for (Option option : *options) {
            switch (option)
            {
            case FILL:
                toFill = true;
                break;
            }
        }
    }

    Data *param1 = parametre->at(1);


    if(!isHelper){
        Data* param2 = parametre->at(2);

        switch (methode) {
        case LIGNE:
            draw->ligne(b, P1_position, P2_position);
            break;
        case RECTANGLE:
            draw->rectangle(b, P1_position, P2_position, toFill);
            break;
        case CARRE:
            draw->carre(b, P1_position, P2_position, toFill);
            break;
        case CERCLE:
            draw->cercle(b, P1_position, P2_int, toFill);
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
            draw->triangle_rectangle(b, P1_position, P2_position, toFill);
            break;
        case TRIANGLE_EQUILATERAL:
            if (P1_position->y != P2_position->y) {
                std::cout << "les deux points doivent etre sur la meme ligne\n";
                break;
            }
            draw->triangle_equilateral(b, P1_position, P2_position, P_bool, toFill);
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

static void paintMethode(HDC fhdc) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(bitmap, &ps);

    HDC hdcCopy = CreateCompatibleDC(hdc);

    SelectObject(hdcCopy, hMap);

    StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);

    EndPaint(bitmap, &ps);
    DeleteDC(hdc);
    DeleteDC(hdcCopy);
}

static HWND createMethode(HWND parent) {
    consoleHeight = 300;
    int padding = 20;
    hMap = (HBITMAP)::LoadImage(
        NULL,
        L"C:\\temp\\a.bmp",
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE | LR_CREATEDIBSECTION
    );

    console = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | WS_HSCROLL, w + padding, paddingY, C_baseWidth, consoleHeight, parent, (HMENU)1, NULL, NULL);

    edit = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, w + padding, consoleHeight + paddingY, C_baseWidth, C_editHeight, parent, (HMENU)1, NULL, NULL);

    bitmap = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_BORDER | SS_BITMAP | WS_VISIBLE | WS_CLIPCHILDREN, 0, paddingY, C_baseWidth, 300, parent, NULL, NULL, NULL);

    return edit;
}

static void onCommand(HWND window) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(console, &ps);

    auto text = L"test";

    TextOut(hdc, 0, 0, text, lstrlenW(text));

    EndPaint(console, &ps);
    DeleteDC(hdc);
}

static void onResize(HWND parent, int width, int height) {
    int maxWidth = width / 2;
    int currentWidthBmp = (maxWidth > w) ? w : maxWidth;
    int currentHeightBmp = height <= h ? height : h;
    consoleHeight = paddingY + height - paddingY * 2 - C_editHeight;

    int editWindowX = currentWidthBmp;

    SetWindowPos(bitmap, NULL, 0, paddingY, currentWidthBmp, currentHeightBmp - paddingY * 2, SWP_NOMOVE | SWP_NOZORDER);

    SetWindowPos(edit, NULL, editWindowX, consoleHeight, width - currentWidthBmp - paddingY, C_editHeight,  SWP_NOZORDER);

    SetWindowPos(console, NULL, editWindowX, paddingY, width - currentWidthBmp - paddingY, consoleHeight, SWP_NOZORDER);
}

static LRESULT windowProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;

    switch (msg) {
        case WM_CLOSE:
            *isRunning = false;
            CloseWindow(window);
            break;
        case WM_PAINT:{
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(window, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            paintMethode(hdc);

            EndPaint(window, &ps);
            DeleteDC(hdc);
            break;
        }
        case WM_COMMAND: {

            onCommand(window);

            break;
        }
        case WM_CREATE: {
            edit = createMethode(window);
            break;
        }
        case WM_SIZE: {
            auto width = LOWORD(lParam);
            auto height = HIWORD(lParam);

            onResize(window, width, height);
            break;
        }
        default:
            result = DefWindowProcA(window, msg, wParam, lParam);
        }

    return result;
}


int main(){
    w = 500;
    h = 500;
	bmp* b = new bmp(w, h);
    Parser* parser = new Parser();
    Draw* draw = new Draw();
    auto *parametre = new std::vector<Data*>();
    Fenetre* window = new Fenetre();

    b->saveFile();

    window->addWindowProc(windowProc);

    *window->getRunning() = window->create_window(1000, 500, "fkf");

    isRunning = window->getRunning();

    while (*window->getRunning()) {
        window->update_window();
    }

    std::string input = "";
    
    std::cout << "--help {methode}" << std::endl;
    do{
        std::cout << "commande: ";
        
        std::getline(std::cin, input);

        if (input == "save")break;

        parser->changeExpression(input);

        for (auto data : *parametre) {
            if(data->option != NULL)delete data->option;
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

