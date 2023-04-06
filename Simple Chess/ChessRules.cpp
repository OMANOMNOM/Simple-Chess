#include "ChessRules.h" 

// 1. can their chosen piece make that move.
// 2. Is the a piece blocking its movement
// 3. Does this result in taking another piece?
bool ChessRules::isValidTraversal(char startPos[], char endPos[], player::Color playercolor,
	Chessboard& board) {
	// What kind of piece is it
	switch (startPos[0]) {
	case 'P':
		// Does it move in the correct direction
		if ((playercolor == player::Color::whitePlayer &&
			(startPos[2] - endPos[2]) < 0) ||
			(playercolor == player::Color::blackPlayer &&
				(startPos[2] - endPos[2]) > 0)) {
			// Does it move by one in only the column and zero in the row
			if (startPos[1] == endPos[1] &&
				std::abs((startPos[2] - endPos[2])) == 1) {
				if (isSquareEmpty(endPos, board)) {
					return true;
				}
			}
			// Check if the pawn can take a piece
			if (std::abs(startPos[1] - endPos[1]) == 1 &&
				std::abs((startPos[2] - endPos[2])) == 1) {
				if (isPieceTakeable(playercolor, board, endPos)) {
					takePiece(playercolor, board, endPos);
					return true;
				}
			}
		}
		return false;

	case 'K':
		// Does it only move one unit
		if (std::abs(startPos[1] - endPos[1]) == 1 ||
			std::abs(startPos[2] - endPos[2]) == 1)
			return true;
		return false;

	case 'N':
		// Does it move in an 'L' Shape
		// 1, hoizontally, 2 vertically or // 2, horizontally, 1 verticlly
		if ((std::abs(startPos[1] - endPos[1]) == 1 &&
			std::abs(startPos[2] - endPos[2]) == 2) ||
			(std::abs(startPos[1] - endPos[1]) == 2 &&
				std::abs(startPos[2] - endPos[2]) == 1))
			return true;
		return false;

	case 'R':
		// Does it only move in one axis?
		if (std::abs(startPos[1] - endPos[1]) > 0 &&
			std::abs(startPos[2] - endPos[2]) == 0 ||
			std::abs(startPos[2] - endPos[2]) > 0 &&
			std::abs(startPos[1] - endPos[1]) == 0) {

			// Do pieces block its movement
			// If movement occurs horizontally
			if (std::abs(startPos[1] - endPos[1]) > 1) {
				int incrememter = 0;
				if (startPos[1] > endPos[1])
					incrememter = -1;
				else
					incrememter = 1;

				for (int i = startPos[1] + incrememter; i != endPos[1];
					i += incrememter) {
					char temp[] = { 'z', i, startPos[2] };
					if (!isSquareEmpty(temp, board))
						return false;
				}
			}

			// If movement occurs Vertically
			if (std::abs(startPos[2] - endPos[2]) > 1) {
				int incrememter = 0;
				if (startPos[2] > endPos[2])
					incrememter = -1;
				else
					incrememter = 1;

				for (int i = startPos[2] + incrememter; i != endPos[2];
					i += incrememter) {
					char temp[] = { 'z', startPos[1], i };
					if (!isSquareEmpty(temp, board))
						return false;
				}
			}
			return true;
		}
		return false;

	case 'B':
		// Does it only move in diagonals?
		if (std::abs(startPos[1] - endPos[1]) == std::abs(startPos[2] - endPos[2])) {
			// are the squares empty along its path
			if (std::abs(startPos[2] - endPos[2]) > 1) {
				int incrVert = 0;
				if (startPos[2] > endPos[2])
					incrVert = -1;
				else
					incrVert = 1;

				if (std::abs(startPos[1] - endPos[1]) > 1) {
					int incrHor = 0;
					if (startPos[1] > endPos[1])
						incrHor = -1;
					else
						incrHor = 1;
					int j = startPos[1] + incrHor;

					// Increment along path checking for blocking pieces
					for (int i = startPos[2] + incrVert; i != endPos[2];
						i += incrVert) {

						char temp[] = { 'z', j, i };
						if (!isSquareEmpty(temp, board))
							return false;
						j += incrHor;
					}
				}
			}
			return true;
		}
		return false;
	case 'Q':
		// Does it only move in diagonals?
		if (std::abs(startPos[1] - endPos[1]) == std::abs(startPos[2] - endPos[2])) {
			// are the squares empty along its path
			if (std::abs(startPos[2] - endPos[2]) > 1) {
				int incrVert = 0;
				if (startPos[2] > endPos[2])
					incrVert = -1;
				else
					incrVert = 1;

				if (std::abs(startPos[1] - endPos[1]) > 1) {
					int incrHor = 0;
					if (startPos[1] > endPos[1])
						incrHor = -1;
					else
						incrHor = 1;
					int j = startPos[1] + incrHor;

					// Increment along path checking for blocking pieces
					for (int i = startPos[2] + incrVert; i != endPos[2];
						i += incrVert) {

						char temp[] = { 'z', j, i };
						if (!isSquareEmpty(temp, board))
							return false;
						j += incrHor;
					}
				}
			}
			return true;
		}
		// Does it only move in one axis?
		if (std::abs(startPos[1] - endPos[1]) > 0 &&
			std::abs(startPos[2] - endPos[2]) == 0 ||
			std::abs(startPos[2] - endPos[2]) > 0 &&
			std::abs(startPos[1] - endPos[1]) == 0) {

			// Do pieces block its movement
			// If movement occurs horizontally
			if (std::abs(startPos[1] - endPos[1]) > 1) {
				int incrememter = 0;
				if (startPos[1] > endPos[1])
					incrememter = -1;
				else
					incrememter = 1;

				for (int i = startPos[1] + incrememter; i != endPos[1];
					i += incrememter) {
					char temp[] = { 'z', i, startPos[2] };
					if (!isSquareEmpty(temp, board))
						return false;
				}
			}

			// If movement occurs Vertically
			if (std::abs(startPos[2] - endPos[2]) > 1) {
				int incrememter = 0;
				if (startPos[2] > endPos[2])
					incrememter = -1;
				else
					incrememter = 1;

				for (int i = startPos[2] + incrememter; i != endPos[2];
					i += incrememter) {
					char temp[] = { 'z', startPos[1], i };
					if (!isSquareEmpty(temp, board))
						return false;
				}
			}
			return true;
		}
		return false;
	}

}

bool ChessRules::isSquareEmptyOrTakeable(char  endPos[], Chessboard& board, player::Color playercolor)
{
	// Is the an enemy piece at its end location and can it take it?
	if (isSquareEmpty(endPos, board)) {
		return true;
	}
	else {
		// Is it an enemy piece?
		if (isPieceTakeable(playercolor, board, endPos))
			takePiece(playercolor, board, endPos);
		return true;
	}
	return false;
}

void ChessRules::takePiece(player::Color playercolor, Chessboard& board,
	char endPos[]) {
	// What is the color of the opponents?
	player* curPlayer = nullptr;
	player* enemyPlayer = nullptr;

	if (playercolor == player::Color::whitePlayer)
	{
		curPlayer = &board.whitePlayer;
		enemyPlayer = &board.blackPlayer;
	}
	else
	{
		curPlayer = &board.blackPlayer;
		enemyPlayer = &board.whitePlayer;

	}

	Piece enemyPiece;
	if (enemyPlayer->pieces->GetPieceAtCoord(endPos, enemyPiece))
	{
		// Find out what piece it is
		switch (enemyPiece.info[0])
		{
		case 'P':
			curPlayer->score.pawns += 1;
			break;
		case 'R':
			curPlayer->score.rooks += 1;
			break;
		case 'N':
			curPlayer->score.knights += 1;
			break;
		case 'B':
			curPlayer->score.bishops += 1;
			break;
		case 'Q':
			curPlayer->score.queen += 1;
			break;
		}
		// Set that piece to dead
		enemyPlayer->pieces->KillPieceAtCoord(endPos);
	}

}

// Basicly is the piece at the final position belonging to the enemy (therfore takeable)
bool ChessRules::isPieceTakeable(player::Color playercolor, Chessboard& board,
	char endPos[]) {
	// What is the color of the opponents?
	player* curPlayer = nullptr;
	player* enemyPlayer = nullptr;
	if (playercolor == player::Color::whitePlayer)
	{
		curPlayer = &board.whitePlayer;
		enemyPlayer = &board.blackPlayer;
	}
	else
	{
		curPlayer = &board.blackPlayer;
		enemyPlayer = &board.whitePlayer;

	}
	Piece empty;
	char pos[3] = { endPos[0], endPos[1], endPos[2] };
	if (enemyPlayer->pieces->GetPieceAtCoord(pos, empty) == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool ChessRules::isSquareEmpty(char endPos[], Chessboard& board) {
	Piece empty;
	if (board.blackPlayer.pieces->GetPieceAtCoord(endPos, empty) == false)
	{
		return true;
	}
	else {
		return false;
	}
	if (board.whitePlayer.pieces->GetPieceAtCoord(endPos, empty) == false)
	{
		return true;
	}
	else {
		return false;
	}
}

//is Checked
bool ChessRules::isChecked(Chessboard& board, player::Color curPlayer)
{
	player* enemy = nullptr;
	player* currentPlayer = nullptr;

	if (curPlayer == player::Color::blackPlayer)
	{
		enemy = &board.whitePlayer;
		currentPlayer = &board.blackPlayer;
	}
	else
	{
		enemy = &board.blackPlayer;
		currentPlayer = &board.whitePlayer;

	}
	char king[3] = { currentPlayer->pieces->piece13->info[0], currentPlayer->pieces->piece13->info[1], currentPlayer->pieces->piece13->info[2] };

	// Loop through all enemy pieces
	for (int i = 0; i < 16; i++)
	{
		// Can any of the pieces take the king in the next move? <----- same function
		char start[3] = { enemy->pieces->piecesArray[i]->info[0], enemy->pieces->piecesArray[i]->info[1], enemy->pieces->piecesArray[i]->info[2] };
		if (isValidTraversal(start, king, currentPlayer->playerColor, board))
		{
			return true;
		}
		// TODO change isvalid to only check and not acutally preform the tak
		// iF yes check
			// Check all kings neighbouring squares to see if the king could move into those spaces
				// Check those spaces are valid to move into
					// Can any of squares be taken in the next turn too? <------ Same function
	}

	return false;
}

// TODO doesn't quite work
// Check all kings neighbouring squares to see if the king could move into those spaces
bool ChessRules::isCheckMate(Chessboard& board, player::Color curPlayer) {
	player* enemy = nullptr;
	player* currentPlayer = nullptr;

	if (curPlayer == player::Color::blackPlayer)
	{
		enemy = &board.whitePlayer;
		currentPlayer = &board.blackPlayer;
	}
	else
	{
		enemy = &board.blackPlayer;
		currentPlayer = &board.whitePlayer;
	}

	char king[3] = { currentPlayer->pieces->piece13->info[0], currentPlayer->pieces->piece13->info[1], currentPlayer->pieces->piece13->info[2] };
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int x = (king[1] + i) - 48;
			int y = (king[2] + j) - 48;
			char start[] = { 'K', x, y };
			if (x <= 7 && x >= 0 && y <= 7 && y >= 0)
			{
				for (int i = 0; i < 16; i++)
				{
					// Can any of the pieces take the king in the next move? <----- same function
					char start[3] = { enemy->pieces->piecesArray[i]->info[0], enemy->pieces->piecesArray[i]->info[1], enemy->pieces->piecesArray[i]->info[2] };
					if (isValidTraversal(start, king, currentPlayer->playerColor, board))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool ChessRules::isValidSelection(char startPos[], player* curPlayer) {
	Piece piece;
	if (!curPlayer->pieces->GetPieceAtCoord(startPos, piece))
	{
		return false;
	}
	else
	{
		return true;
	}

}