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
bool isValid(char startPos[], char endPos[], player::Color playercolor,
	Chessboard& board);
bool isSquareEmptyOrTakeable(char  endPos[], Chessboard& board, player::Color playercolor);
bool isPieceTakeable(player::Color playercolor, Chessboard& board,
	char endPos[]);
bool isSquareEmpty(char endPos[], Chessboard& board);

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
			printf(CSI "30m"); //
			std::cout << "Player " << curPlayerId + 1;
			printf(CSI "0m"); //

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
				isValidInput = true;
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
				if (isValid(startPos, endPos, curPlayer->playerColor, board)) {
					isValidInput = true;
				}
			}
		}
		// board.whitePlayer.setPosition(startPos, endPos);
		curPlayer->setPosition(startPos, endPos);
		if (curPlayerId == 0) {
			curPlayerId = 1;
			curPlayer = &board.blackPlayer;
		}
		else {
			curPlayerId = 0;
			curPlayer = &board.whitePlayer;
		}
		clearDisplay(hStdOut, originalMode);
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
bool isValid(char startPos[], char endPos[], player::Color playercolor,
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
				if (isPieceTakeable(playercolor, board, endPos))
					return true;
			}
		}
		return false;

	case 'K':
		// Does it only move one unit
		if (std::abs(startPos[1] - endPos[1]) == 1 ||
			std::abs(startPos[2] - endPos[2]) == 1) {
			if (isSquareEmptyOrTakeable(endPos, board, playercolor))
				return true;
		}
		return false;

	case 'N':
		// Does it move in an 'L' Shape
		// 1, hoizontally, 2 vertically or // 2, horizontally, 1 verticlly
		if ((std::abs(startPos[1] - endPos[1]) == 1 &&
			std::abs(startPos[2] - endPos[2]) == 2) ||
			(std::abs(startPos[1] - endPos[1]) == 2 &&
				std::abs(startPos[2] - endPos[2]) == 1)) {
			if (isSquareEmptyOrTakeable(endPos, board, playercolor))
				return true;
		}
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
			if (isSquareEmptyOrTakeable(endPos, board, playercolor))
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
			if (isSquareEmptyOrTakeable(endPos, board, playercolor))
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
			if (isSquareEmptyOrTakeable(endPos, board, playercolor))
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
			if (isSquareEmptyOrTakeable(endPos, board, playercolor))
				return true;
		}
		
		return false;
		break;
	}
	
}

bool isSquareEmptyOrTakeable(char  endPos[], Chessboard& board, player::Color playercolor)
{
	// Is the an enemy piece at its end location and can it take it?
	if (isSquareEmpty(endPos, board)) {
		return true;
	}
	else {
		// Is it an enemy piece?
		if (isPieceTakeable(playercolor, board, endPos))
			return true;
	}
	return false;
}

bool isPieceTakeable(player::Color playercolor, Chessboard& board,
	char endPos[]) {
	// What is the color of the opponents?
	if (playercolor == player::Color::whitePlayer) {
		// Search through said opponents pieces to see if their peice is there
		for (int i = 0; i < 16; i++) {
			// If it is one of their pieces at that location
			if (board.blackPlayer.pieces[i][1] == endPos[1] &&
				board.blackPlayer.pieces[i][2] == endPos[2]) {
				// We then destroy said piece
				board.blackPlayer.pieces[i][0] = 'x';
				board.whitePlayer.score.pawns += 1;
				return true;
			}
		}
	}
	else {
		for (int i = 0; i < 16; i++) {
			if (board.whitePlayer.pieces[i][1] == endPos[1] &&
				board.whitePlayer.pieces[i][2] == endPos[2]) {
				// Then we need to preform takeing said piece
				board.whitePlayer.pieces[i][0] = 'x';
				board.blackPlayer.score.pawns += 1;
				return true;
			}
		}
	}
	return false;
}

bool isSquareEmpty(char endPos[], Chessboard& board) {
	for (int i = 0; i < 16; i++) {
		if (board.blackPlayer.pieces[i][1] == endPos[1] &&
			board.blackPlayer.pieces[i][2] == endPos[2]) {
			return false;
		}
		if (board.whitePlayer.pieces[i][1] == endPos[1] &&
			board.whitePlayer.pieces[i][2] == endPos[2]) {
			return false;
		}
	}
	return true;
}

