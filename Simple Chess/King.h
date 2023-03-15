#pragma once
#include "Piece.h"
class King :
    public Piece
{
public:
    King(char posX, char posY) {
        info[0] = 'K';
        info[1] = posX;
        info[2] = posY;
    }
};

