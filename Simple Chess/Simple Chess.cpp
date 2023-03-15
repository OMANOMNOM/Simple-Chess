// Simple Chess.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <String>
#include <iostream>
#include "Chessboard.h"
#define CSI "\x1b["

void clearDisplay(HANDLE& hStdOut, const DWORD& originalMode);
void EnableVirtualTerminalSequences(HANDLE& hStdOut, DWORD originalMode);
void getInputArray(std::string& input, char startPos[]);
bool isValidTraversal(char startPos[], char endPos[], player::Color playercolor,
	Chessboard& board);
bool isSquareEmptyOrTakeable(char  endPos[], Chessboard& board, player::Color playercolor);
void takePiece(player::Color playercolor, Chessboard& board, char endPos[]);
bool isPieceTakeable(player::Color playercolor, Chessboard& board,
	char endPos[]);
bool isSquareEmpty(char endPos[], Chessboard& board);

bool isChecked(Chessboard& board, player::Color curPlayer);

bool isCheckMate(Chessboard& board, player::Color curPlayer);

bool isValidSelection(char startPos[], player* curPlayer);

int main() {
	HANDLE hStdOut;
	DWORD originalMode = 0;
	EnableVirtualTerminalSequences(hStdOut, originalMode);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) {
		printf("Couldn't get the console handle. Quitting.\n");
		return -1;
	}
	Chessboard board = Chessboard();
	int curPlayerId = 0;
	player* curPlayer = &board.whitePlayer;

	while (true) {
		board.printChessboard();
		if (curPlayerId + 1 == 2) {
			printf(CSI "30m");
			std::cout << "Player " << curPlayerId + 1;
			printf(CSI "0m");
		}
		else
			std::cout << "Player " << curPlayerId + 1;
		std::cout << " it is now your turn" << std::endl;
		std::string input;
		char endPos[3]{};
		char startPos[3]{};
		bool isValidInput = false;
		// While loop
		while (!isValidInput) {
			std::wcout << "Please enter the piece you'd like to move (piece, x, y);"
				<< std::endl;
			std::cin >> input;
			std::cin.ignore(200, '\n');
			if (input.size() == 5) {
				getInputArray(input, startPos);
				//Check if selection is of a valid piece.
				// get color 
				// get start pos
				/*if (isValidSelection(startPos, curPlayer)) 
				{
					isValidInput = true;
				}*/
					
				// check if player has a piece at that start position
			}
		}

		isValidInput = false;
		while (!isValidInput) {
			std::wcout
				<< "Please enter the position you'd like to move to (piece, x, y):"
				<< std::endl;
			std::cin >> input;
			std::cin.ignore(200, '\n');
			if (input.size() == 5) {
				getInputArray(input, endPos);
				/*if (isValidTraversal(startPos, endPos, curPlayer->playerColor, board)) {
					if (isSquareEmptyOrTakeable(endPos, board, curPlayer->playerColor))
						isValidInput = true;
				}*/
			}
		}
		// don't know if i should uncomment this board.whitePlayer.setPosition(startPos, endPos);
		//curPlayer->setPosition(startPos, endPos);
		if (curPlayerId == 0) {
			curPlayerId = 1;
			curPlayer = &board.blackPlayer;
		}
		else {
			curPlayerId = 0;
			curPlayer = &board.whitePlayer;
		}
		clearDisplay(hStdOut, originalMode);
		/*if (isChecked(board, player::Color::blackPlayer))
			std::cout << "black is checked";
		if (isChecked(board, player::Color::whitePlayer))
			std::cout << "black is checked";
		if (isCheckMate(board, player::Color::blackPlayer))
			std::cout << "black is checkmate ";
		if (isCheckMate(board, player::Color::whitePlayer))
			std::cout << "black is checkmate ";*/
	}
}

void EnableVirtualTerminalSequences(HANDLE& hStdOut, DWORD originalMode) {
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// Fetch existing console mode so we correctly add a flag and not turn off
	// others
	DWORD mode = 0;
	if (!GetConsoleMode(hStdOut, &mode)) {
		// return ::GetLastError();
	}

	// Hold original mode to restore on exit to be cooperative with other
	// command-line apps.
	originalMode = mode;
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	// Try to set the mode.
	if (!SetConsoleMode(hStdOut, mode)) {
		// return ::GetLastError();
	}
}
void clearDisplay(HANDLE& hStdOut, const DWORD& originalMode) {
	// Write the sequence for clearing the display.
	DWORD written = 0;
	PCWSTR sequence = L"\x1b[2J";
	if (!WriteConsoleW(hStdOut, sequence, (DWORD)wcslen(sequence), &written,
		NULL)) {
		// If we fail, try to restore the mode on the way out.
		SetConsoleMode(hStdOut, originalMode);
	}
}

// Get input and convert to array coordinates starting at zero
void getInputArray(std::string& input, char startPos[]) {
	for (int i = 0; i < 3; i++) {
		char buffer[3];
		input.copy(buffer, 1, (i * 2));
		startPos[i] = buffer[0];
	}
	startPos[1] -= 1;
	startPos[2] -= 1;
}

// can their chosen piece make that move.
// Is the piece blocking its movement
// Does this result in taking another piece?
//bool isValidTraversal(char startPos[], char endPos[], player::Color playercolor,
//	Chessboard& board) {
//	// What kind of piece is it
//	switch (startPos[0]) {
//	case 'P':
//		// Does it move in the correct direction
//		if ((playercolor == player::Color::whitePlayer &&
//			(startPos[2] - endPos[2]) < 0) ||
//			(playercolor == player::Color::blackPlayer &&
//				(startPos[2] - endPos[2]) > 0)) {
//			// Does it move by one in only the column and zero in the row
//			if (startPos[1] == endPos[1] &&
//				std::abs((startPos[2] - endPos[2])) == 1) {
//				if (isSquareEmpty(endPos, board)) {
//					return true;
//				}
//			}
//			// Check if the pawn can take a piece
//			if (std::abs(startPos[1] - endPos[1]) == 1 &&
//				std::abs((startPos[2] - endPos[2])) == 1) {
//				if (isPieceTakeable(playercolor, board, endPos)) {
//					takePiece(playercolor, board, endPos);
//					return true;
//
//				}
//			}
//		}
//		return false;
//
//	case 'K':
//		// Does it only move one unit
//		if (std::abs(startPos[1] - endPos[1]) == 1 ||
//			std::abs(startPos[2] - endPos[2]) == 1) 
//			return true;
//		return false;
//
//	case 'N':
//		// Does it move in an 'L' Shape
//		// 1, hoizontally, 2 vertically or // 2, horizontally, 1 verticlly
//		if ((std::abs(startPos[1] - endPos[1]) == 1 &&
//			std::abs(startPos[2] - endPos[2]) == 2) ||
//			(std::abs(startPos[1] - endPos[1]) == 2 &&
//				std::abs(startPos[2] - endPos[2]) == 1)) 
//			return true;
//		return false;
//
//	case 'R':
//		// Does it only move in one axis?
//		if (std::abs(startPos[1] - endPos[1]) > 0 &&
//			std::abs(startPos[2] - endPos[2]) == 0 ||
//			std::abs(startPos[2] - endPos[2]) > 0 &&
//			std::abs(startPos[1] - endPos[1]) == 0) {
//
//			// Do pieces block its movement
//			// If movement occurs horizontally
//			if (std::abs(startPos[1] - endPos[1]) > 1) {
//				int incrememter = 0;
//				if (startPos[1] > endPos[1])
//					incrememter = -1;
//				else
//					incrememter = 1;
//
//				for (int i = startPos[1] + incrememter; i != endPos[1];
//					i += incrememter) {
//					char temp[] = { 'z', i, startPos[2] };
//					if (!isSquareEmpty(temp, board))
//						return false;
//				}
//			}
//
//			// If movement occurs Vertically
//			if (std::abs(startPos[2] - endPos[2]) > 1) {
//				int incrememter = 0;
//				if (startPos[2] > endPos[2])
//					incrememter = -1;
//				else
//					incrememter = 1;
//
//				for (int i = startPos[2] + incrememter; i != endPos[2];
//					i += incrememter) {
//					char temp[] = { 'z', startPos[1], i };
//					if (!isSquareEmpty(temp, board))
//						return false;
//				}
//			}
//			return true;
//		}
//		return false;
//
//	case 'B':
//		// Does it only move in diagonals?
//		if (std::abs(startPos[1] - endPos[1]) == std::abs(startPos[2] - endPos[2])) {
//			// are the squares empty along its path
//			if (std::abs(startPos[2] - endPos[2]) > 1) {
//				int incrVert = 0;
//				if (startPos[2] > endPos[2])
//					incrVert = -1;
//				else
//					incrVert = 1;
//
//				if (std::abs(startPos[1] - endPos[1]) > 1) {
//					int incrHor = 0;
//					if (startPos[1] > endPos[1])
//						incrHor = -1;
//					else
//						incrHor = 1;
//					int j = startPos[1] + incrHor;
//
//					// Increment along path checking for blocking pieces
//					for (int i = startPos[2] + incrVert; i != endPos[2];
//						i += incrVert) {
//
//						char temp[] = { 'z', j, i };
//						if (!isSquareEmpty(temp, board))
//							return false;
//						j += incrHor;
//					}
//				}
//			}
//			return true;
//		}
//		return false;
//	case 'Q':
//		// Does it only move in diagonals?
//		if (std::abs(startPos[1] - endPos[1]) == std::abs(startPos[2] - endPos[2])) {
//			// are the squares empty along its path
//			if (std::abs(startPos[2] - endPos[2]) > 1) {
//				int incrVert = 0;
//				if (startPos[2] > endPos[2])
//					incrVert = -1;
//				else
//					incrVert = 1;
//
//				if (std::abs(startPos[1] - endPos[1]) > 1) {
//					int incrHor = 0;
//					if (startPos[1] > endPos[1])
//						incrHor = -1;
//					else
//						incrHor = 1;
//					int j = startPos[1] + incrHor;
//
//					// Increment along path checking for blocking pieces
//					for (int i = startPos[2] + incrVert; i != endPos[2];
//						i += incrVert) {
//
//						char temp[] = { 'z', j, i };
//						if (!isSquareEmpty(temp, board))
//							return false;
//						j += incrHor;
//					}
//				}
//			}
//			return true;
//		}
//		// Does it only move in one axis?
//		if (std::abs(startPos[1] - endPos[1]) > 0 &&
//			std::abs(startPos[2] - endPos[2]) == 0 ||
//			std::abs(startPos[2] - endPos[2]) > 0 &&
//			std::abs(startPos[1] - endPos[1]) == 0) {
//
//			// Do pieces block its movement
//			// If movement occurs horizontally
//			if (std::abs(startPos[1] - endPos[1]) > 1) {
//				int incrememter = 0;
//				if (startPos[1] > endPos[1])
//					incrememter = -1;
//				else
//					incrememter = 1;
//
//				for (int i = startPos[1] + incrememter; i != endPos[1];
//					i += incrememter) {
//					char temp[] = { 'z', i, startPos[2] };
//					if (!isSquareEmpty(temp, board))
//						return false;
//				}
//			}
//
//			// If movement occurs Vertically
//			if (std::abs(startPos[2] - endPos[2]) > 1) {
//				int incrememter = 0;
//				if (startPos[2] > endPos[2])
//					incrememter = -1;
//				else
//					incrememter = 1;
//
//				for (int i = startPos[2] + incrememter; i != endPos[2];
//					i += incrememter) {
//					char temp[] = { 'z', startPos[1], i };
//					if (!isSquareEmpty(temp, board))
//						return false;
//				}
//			}
//			return true;
//		}
//		return false;
//		break;
//	}
//
//}
//
//bool isSquareEmptyOrTakeable(char  endPos[], Chessboard& board, player::Color playercolor)
//{
//	// Is the an enemy piece at its end location and can it take it?
//	if (isSquareEmpty(endPos, board)) {
//		return true;
//	}
//	else {
//		// Is it an enemy piece?
//		if (isPieceTakeable(playercolor, board, endPos))
//			takePiece(playercolor, board, endPos);
//			return true;
//	}
//	return false;
//}
//
//
//void takePiece(player::Color playercolor, Chessboard& board,
//	char endPos[]) {
//	// What is the color of the opponents?
//	player* curPlayer = nullptr;
//	player* enemyPlayer = nullptr;
//
//	if (playercolor == player::Color::whitePlayer)
//	{
//		curPlayer = &board.whitePlayer;
//		enemyPlayer = &board.blackPlayer;
//	}
//	else
//	{
//		curPlayer = &board.blackPlayer;
//		enemyPlayer = &board.whitePlayer;
//
//	}
//
//	// Search through said opponents pieces to see if their peice is there
//	for (int i = 0; i < 16; i++) {
//		// If it is one of their pieces at that location
//		if (*enemyPlayer->pieces->piecesArray[i][1]->info == endPos[1] &&
//			*enemyPlayer->pieces->piecesArray[i][2]->info == endPos[2]) {
//			// Find out what piece it is
//			switch (enemyPlayer->pieces[i][0])
//			{
//			case 'P':
//				curPlayer->score.pawns += 1;
//				break;
//			case 'R':
//				curPlayer->score.rooks += 1;
//				break;
//			case 'N':
//				curPlayer->score.knights += 1;
//				break;
//			case 'B':
//				curPlayer->score.bishops += 1;
//				break;
//			case 'Q':
//				curPlayer->score.queen += 1;
//				break;
//			}
//			// Set that piece to dead
//			enemyPlayer->pieces[i][0] = 'x';
//		}
//	}
//}
//
//bool isPieceTakeable(player::Color playercolor, Chessboard& board,
//	char endPos[]) {
//	// What is the color of the opponents?
//	player* curPlayer = nullptr;
//	player* enemyPlayer = nullptr;
//
//	if (playercolor == player::Color::whitePlayer)
//	{
//		curPlayer = &board.whitePlayer;
//		enemyPlayer = &board.blackPlayer;
//	}
//	else
//	{
//		curPlayer = &board.blackPlayer;
//		enemyPlayer = &board.whitePlayer;
//
//	}
//
//	// Search through said opponents pieces to see if their peice is there
//	for (int i = 0; i < 16; i++) {
//		// If it is one of their pieces at that location
//		if (enemyPlayer->pieces[i][1] == endPos[1] &&
//			enemyPlayer->pieces[i][2] == endPos[2]) {
//			return true;
//		}
//	}
//	return false;
//}
//
//bool isSquareEmpty(char endPos[], Chessboard& board) {
//	for (int i = 0; i < 16; i++) {
//		if (board.blackPlayer.pieces[i][1] == endPos[1] &&
//			board.blackPlayer.pieces[i][2] == endPos[2]) {
//			return false;
//		}
//		if (board.whitePlayer.pieces[i][1] == endPos[1] &&
//			board.whitePlayer.pieces[i][2] == endPos[2]) {
//			return false;
//		}
//	}
//	return true;
//}
//
////is Checked
//bool isChecked(Chessboard& board, player::Color curPlayer)
//{
//	player* enemy = nullptr;
//	player* currentPlayer = nullptr;
//
//	if (curPlayer == player::Color::blackPlayer)
//	{
//		enemy = &board.whitePlayer;
//		currentPlayer = &board.blackPlayer;
//	}
//	else
//	{
//		enemy = &board.blackPlayer;
//		currentPlayer = &board.whitePlayer;
//
//	}
//
//	char king[3] = { currentPlayer->pieces[11][0], currentPlayer->pieces[11][1], currentPlayer->pieces[11][2] };
//	// Loop through all enemy pieces
//	for (int i = 0; i < 16; i++)
//	{
//		// Can any of the pieces take the king in the next move? <----- same function
//		char start[3] = { enemy->pieces[i][0], enemy->pieces[i][1], enemy->pieces[i][2] };
//		if (isValidTraversal(start,king,  currentPlayer->playerColor, board))
//		{
//			return true;
//		}
//		// TODO change isvalid to only check and not acutally preform the tak
//		// iF yes check
//			// Check all kings neighbouring squares to see if the king could move into those spaces
//				// Check those spaces are valid to move into
//					// Can any of squares be taken in the next turn too? <------ Same function
//	}
//	return false;
//}
//
//// Check all kings neighbouring squares to see if the king could move into those spaces
//bool isCheckMate(Chessboard& board, player::Color curPlayer) {
//	player* enemy = nullptr;
//	player* currentPlayer = nullptr;
//
//	if (curPlayer == player::Color::blackPlayer)
//	{
//		enemy = &board.whitePlayer;
//		currentPlayer = &board.blackPlayer;
//	}
//	else
//	{
//		enemy = &board.blackPlayer;
//		currentPlayer = &board.whitePlayer;
//
//	}
//
//	char king[3] = { currentPlayer->pieces[11][0], currentPlayer->pieces[11][1], currentPlayer->pieces[11][2] };
//	for (int i = -1; i < 2; i++)
//	{
//		for (int j = -1; j < 2; j++)
//		{
//			int x = (king[1] + i) - 48;
//			int y = (king[2] + j) - 48;
//			char start[] = { 'K', x, y };
//			if (x <= 7 && x >= 0 && y <= 7 && y >= 0)
//			{
//				for (int i = 0; i < 16; i++)
//				{
//					// Can any of the pieces take the king in the next move? <----- same function
//					char start[3] = { enemy->pieces[i][0], enemy->pieces[i][1], enemy->pieces[i][2] };
//					if (isValidTraversal(start, king, currentPlayer->playerColor, board))
//					{
//						return true;
//					}
//				}
//			}
//		}
//	}
//	return false;
//
//	
//}
//
//bool isValidSelection(char startPos[], player* curPlayer) {
//	for (int i = 0; i < 16; i++)
//	{
//		if (curPlayer->pieces[i][0] != 'x')
//		{
//			if (curPlayer->pieces[i][1] == startPos[1] && curPlayer->pieces[i][2] == startPos[2])
//			{
//				return true;
//			}
//		}
//	}
//	std::cout << "You haven't selected a valid piece" << std::endl;
//	return false;
//}
//
//
