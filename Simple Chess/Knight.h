#pragma once
#include "Piece.h"
class Knight :
    public Piece
{
public:
    Knight(char posX, char posY) {
        info[0] = 'N';
        info[1] = posX;
        info[2] = posY;
    }
};

