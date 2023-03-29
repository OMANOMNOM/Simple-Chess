#pragma once
#include "Piece.h"
class Pawn :
    public Piece
{
public:
    Pawn(char posX, char posY) {
        info[0] = 'P';
        info[1] = posX;
        info[2] = posY;
    }
};

