#pragma once
#include <vector>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

// This is the container class that is repsonsible all the pieces belonging to a player. 
// 
class Pieces
{
public:
	std::vector<Piece*> piecesArray;

	// Get piece at grid 
	bool GetPieceAtCoord(char Coord[3], Piece &outPiece);
	bool KillPieceAtCoord(char Coord[3]);
	bool SetPosition(char curCoord[3], char newCoord[3]);
	Pieces();

	Pawn* piece1;
	Pawn* piece2;
	Pawn* piece3;
	Pawn* piece4;
	Pawn* piece5;
	Pawn* piece6;
	Pawn* piece7;
	Pawn* piece8;

	Rook* piece9;
	Knight* piece10;
	Bishop* piece11;
	Queen* piece12;
	King* piece13;
	Bishop* piece14;
	Knight* piece15;
	Rook* piece16;
};

