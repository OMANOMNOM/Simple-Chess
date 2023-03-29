#include "Pieces.h"



// If piece is at said location, 
bool Pieces::GetPieceAtCoord(char Coord[3], Piece& outPiece)
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

bool Pieces::KillPieceAtCoord(char Coord[3])
{
	for (auto& piece : piecesArray)
	{
		if (piece->info[1] == Coord[1] && piece->info[2] == Coord[2])
		{
			piece->info[0] = 'x';
			return true;
		}
	}
	return false;
}

bool Pieces::SetPosition(char curCoord[2], char newCoord[2])
{
	for (auto& piece : piecesArray)
	{
		if (piece->info[1] == curCoord[1] && piece->info[2] == curCoord[2])
		{
			piece->info[1] = newCoord[1];
			piece->info[2] = newCoord[2];
			return true;
		}
	}
	return false;
}



Pieces::Pieces()
{
	piece1 = new Pawn('0', '5');
	piece2 = new Pawn('1', '1');
	piece3 = new Pawn('1', '2');
	piece4 = new Pawn('1', '3');
	piece5 = new Pawn('2', '2');
	piece6 = new Pawn('5', '1');
	piece7 = new Pawn('6', '1');
	piece8 = new Pawn('7', '1');
	piece9 = new Rook('0', '0');
	piece10 = new Knight('1', '0');
	piece11 = new Bishop('2', '0');
	piece12 = new Queen('3', '0');
	piece13 = new King('4', '0');
	piece14 = new Bishop('5', '0');
	piece15 = new Knight('6', '0');
	piece16 = new Rook('7', '0');

	piecesArray = std::vector<Piece*> { piece1, piece2, piece3, piece4, piece5, piece6, piece7, piece8,
		piece9, piece10, piece11, piece12, piece13, piece14, piece15, piece16 };

}
