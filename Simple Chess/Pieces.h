#pragma once
#include <vector>
#include "Piece.h"


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
};

