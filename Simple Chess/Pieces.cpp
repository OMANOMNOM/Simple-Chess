#include "Pieces.h"

#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

Pieces::Pieces()
{
	Pawn* piece1 = new Pawn('0', '0');
	Pawn* piece2 = new Pawn('0', '1');
	Pawn* piece3 = new Pawn('0', '2');
	Pawn* piece4 = new Pawn('0', '3');
	Pawn* piece5 = new Pawn('0', '4');
	Pawn* piece6 = new Pawn('0', '5');
	Pawn* piece7 = new Pawn('0', '6');
	Pawn* piece8 = new Pawn('0', '7');

	Rook* piece9 = new Rook('1', '0');
	Knight* piece10 = new Knight('1', '1');
	Bishop* piece11 = new Bishop('2', '2');
	Queen* piece12 = new Queen('3', '3');
	King* piece13 = new King('4', '4');
	Bishop* piece14 = new Bishop('5', '5');
	Knight* piece15 = new Knight('6', '6');
	Rook* piece16 = new Rook('7', '7');

	piecesArray = std::vector<Piece*> { piece1, piece2, piece3, piece4, piece5, piece6, piece7, piece8,
		piece9, piece10, piece11, piece12, piece13, piece14, piece15, piece16 };

}
