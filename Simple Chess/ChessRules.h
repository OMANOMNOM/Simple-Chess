#pragma once
#include "player.h"
#include "Chessboard.h"
class ChessRules
{
public:
	static bool isValidTraversal(char startPos[], char endPos[], player::Color playercolor, Chessboard& board);
	static bool isSquareEmptyOrTakeable(char endPos[], Chessboard& board, player::Color playercolor);
	static void takePiece(player::Color playercolor, Chessboard& board, char endPos[]);
	static bool isPieceTakeable(player::Color playercolor, Chessboard& board, char endPos[]);
	static bool isSquareEmpty(char endPos[], Chessboard& board);
	static bool isChecked(Chessboard& board, player::Color curPlayer);
	static bool isCheckMate(Chessboard& board, player::Color curPlayer);
	static bool isValidSelection(char startPos[], player* curPlayer);
};

