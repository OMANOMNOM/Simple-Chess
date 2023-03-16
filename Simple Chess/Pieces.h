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
	bool GetPieceAtCoord(char Coord[2], Piece &outPiece);
	Pieces();
};

