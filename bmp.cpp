#include "bmp.h"
#pragma warning(disable : 4996)

#define pixelVide 0
#define bufferSize(x, y) x * y * 3 
bmp::bmp(int width, int height) {

    this->width = width;
    this->height = height;
    taille = sizeof(char) * width * height * 3;
    buffer = (unsigned char*)malloc(taille);
    memset(buffer, 0 , width * height * 3);
}

void bmp::setPixel(int piX, int piY, unsigned char R, unsigned char G, unsigned char B)
{
    int pos;
    pos = piY * width * 3;
    pos += piX * 3;

    if (pos >= taille || pos < 0)return;
    
    buffer[pos + 0] = B;
    buffer[pos + 1] = G;
    buffer[pos + 2] = R;
}

bool bmp::pixelEstVide(int piX, int piY) {
    int pos;
    pos = piY * width * 3;
    pos += piX * 3;

    if (pos >= taille || pos < 0)return false;

    unsigned char blue = buffer[pos + 0];
    unsigned char green = buffer[pos + 1];
    unsigned char red = buffer[pos + 2];

    return blue == pixelVide && green == pixelVide && red == pixelVide;
}

void bmp::saveFile()
{
    bmpFileHeader bmpFH;
    bmpInfoHeader bmpIH;
    FILE* fbmp;
    int padding;

    padding = (4 - ((width * 3) % 4)) % 4;
    //cout << sizeof(short);
    bmpFH.signature = 'B' + 'M' * 256;
    bmpFH.fileSize = sizeof(bmpFileHeader);
    bmpFH.fileSize += sizeof(bmpInfoHeader);
    bmpFH.fileSize += sizeof(char) * (width * height * 3) + padding;
    bmpFH.resrved = 0;
    bmpFH.dataOffset = 0;

    bmpIH.size = sizeof(bmpInfoHeader);
    bmpIH.width = width;
    bmpIH.height = height;
    bmpIH.planes = 1;
    bmpIH.BPP = 24;
    bmpIH.compression = 0;
    bmpIH.imgSize = 0;
    bmpIH.XPPM = 0;
    bmpIH.YPPM = 0;
    bmpIH.color = 0;
    bmpIH.iColor = 0;

    fbmp = fopen("c:\\temp\\a.bmp", "wb");
    fwrite(&bmpFH, sizeof(bmpFileHeader), 1, fbmp);
    fwrite(&bmpIH, sizeof(bmpInfoHeader), 1, fbmp);

    fwrite(buffer, width * height * 3, 1, fbmp);
    fclose(fbmp);
}