#pragma once
#include "Piece.h"
class Rook :
    public Piece
{
public:
    Rook(char posX, char posY) {
        info[0] = 'R';
        info[1] = posX;
        info[2] = posY;
    }
};

