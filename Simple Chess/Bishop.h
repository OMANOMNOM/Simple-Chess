#pragma once
#include "Piece.h"
class Bishop :
    public Piece
{
public: 
    Bishop(char posX, char posY) {
        info[0] = 'B';
        info[1] = posX;
        info[2] = posY;

    }
};

