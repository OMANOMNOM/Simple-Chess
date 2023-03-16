#include "Pieces.h"

#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

// If piece is at said location, 
bool Pieces::GetPieceAtCoord(char Coord[2], Piece& outPiece)
{
	for (auto& piece : piecesArray)
	{
		if (piece->info[1] == Coord[1] && piece->info[2] == Coord[2])
		{
			outPiece = *piece;
			return true;
		}
	}
	return false;
}

Pieces::Pieces()
{
	Pawn* piece1 = new Pawn('0', '1');
	Pawn* piece2 = new Pawn('1', '1');
	Pawn* piece3 = new Pawn('2', '1');
	Pawn* piece4 = new Pawn('3', '1');
	Pawn* piece5 = new Pawn('4', '1');
	Pawn* piece6 = new Pawn('5', '1');
	Pawn* piece7 = new Pawn('6', '1');
	Pawn* piece8 = new Pawn('7', '1');

	Rook* piece9 = new Rook('0', '0');
	Knight* piece10 = new Knight('1', '0');
	Bishop* piece11 = new Bishop('2', '0');
	Queen* piece12 = new Queen('3', '0');
	King* piece13 = new King('4', '0');
	Bishop* piece14 = new Bishop('5', '0');
	Knight* piece15 = new Knight('6', '0');
	Rook* piece16 = new Rook('7', '0');

	piecesArray = std::vector<Piece*> { piece1, piece2, piece3, piece4, piece5, piece6, piece7, piece8,
		piece9, piece10, piece11, piece12, piece13, piece14, piece15, piece16 };

}
