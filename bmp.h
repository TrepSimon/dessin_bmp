#pragma once
#include <iostream>

#pragma pack(push,1)

struct bmpFileHeader {
    unsigned short signature;
    unsigned int fileSize;
    int resrved;
    int dataOffset;
};

struct bmpInfoHeader {
    int size, width, height;
    short planes, BPP;
    int compression, imgSize, XPPM, YPPM, color, iColor;
};

#pragma pack(pop)

class bmp{
public:
    bmpFileHeader file_header;
    bmpInfoHeader info_header;
    unsigned char* buffer;
    int width, height, taille;

    bmp(int, int);
    void fichier();
    void setPixel(int, int, unsigned char, unsigned char, unsigned char);
    void saveFile();
    bool pixelEstVide(int, int);

    

};

