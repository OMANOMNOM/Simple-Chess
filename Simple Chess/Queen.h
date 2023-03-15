#pragma once
#include "Piece.h"
class Queen :
    public Piece
{
public:
    Queen(char posX, char posY) {
        info[0] = 'Q';
        info[1] = posX;
        info[2] = posY;
    }
};

