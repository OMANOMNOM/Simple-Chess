// Simple Chess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Chessboard.h"
#include <Windows.h>
#include <String>
#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#define CSI "\x1b["

void clearDisplay(HANDLE& hStdOut, const DWORD& originalMode);
void EnableVirtualTerminalSequences(HANDLE& hStdOut, DWORD originalMode);
bool validateInput(std::string);
void getInputArray(std::string& input, char startPos[]);
bool isValid(char startPos[], char endPos[], player::Color playercolor, Chessboard& board);
bool isSquareEmpty(char endPos[], Chessboard& board);

int main()
{
	HANDLE hStdOut;
	DWORD originalMode = 0;
	EnableVirtualTerminalSequences(hStdOut, originalMode);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		printf("Couldn't get the console handle. Quitting.\n");
		return -1;
	}
	Chessboard board = Chessboard();
	int curPlayerId = 0;
	player* curPlayer = &board.whitePlayer;

	while (true) {

		board.printChessboard();
		std::wcout << "Player " << curPlayerId + 1 << " it is now your turn" << std::endl;
		std::string input;
		char endPos[3]{};

		// While loop
		std::wcout << "Please enter the piece you'd like to move (piece, x, y);" << std::endl;
		std::cin >> input;
		char startPos[3]{};
		//validateInput(); // Validate the actual chars
		getInputArray(input, startPos);
		// Is this an actual piece they own?

		while (true)
		{
			std::wcout << "Please enter the position you'd like to move to (piece, x, y):" << std::endl;
			std::cin >> input;
			//validateInput(); // Validate the actual chars
			getInputArray(input, endPos);
			if (isValid(startPos, endPos, curPlayer->playerColor, board))
				break;
		}
		//board.whitePlayer.setPosition(startPos, endPos);
		curPlayer->setPosition(startPos, endPos);
		if (curPlayerId == 0)
		{
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

	// Fetch existing console mode so we correctly add a flag and not turn off others
	DWORD mode = 0;
	if (!GetConsoleMode(hStdOut, &mode))
	{
		//return ::GetLastError();
	}

	// Hold original mode to restore on exit to be cooperative with other command-line apps.
	originalMode = mode;
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	// Try to set the mode.
	if (!SetConsoleMode(hStdOut, mode))
	{
		//return ::GetLastError();
	}
}
void clearDisplay(HANDLE& hStdOut, const DWORD& originalMode) {
	// Write the sequence for clearing the display.
	DWORD written = 0;
	PCWSTR sequence = L"\x1b[2J";
	if (!WriteConsoleW(hStdOut, sequence, (DWORD)wcslen(sequence), &written, NULL))
	{
		// If we fail, try to restore the mode on the way out.
		SetConsoleMode(hStdOut, originalMode);
	}
}

bool validateInput(std::string) {
	// Check if valid chars 
	// Check if its a piece that plater actualy owns and is at said positon

	return true;
}

// Get input and convert to array coordinates starting at zero
void getInputArray(std::string& input, char startPos[]) {
	for (int i = 0; i < 3; i++)
	{
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
bool isValid(char startPos[], char endPos[], player::Color playercolor, Chessboard& board)
{
	// What kind of piece is it
	// Did it do any of the corresponding valid moves
	char piece = startPos[0];
	switch (piece) {
	case 'P':
		//Does it move in the correct direction
		if ((playercolor == player::Color::whitePlayer && (startPos[2] - endPos[2]) < 0) || (playercolor == player::Color::blackPlayer && (startPos[2] - endPos[2]) > 0))
		{
			// Does it move by one in only the column and zero in the row
			if (startPos[1] == endPos[1] && std::abs((startPos[2] - endPos[2])) == 1)
			{
				if (isSquareEmpty(endPos, board))
				{
					return true;
				}
			}
			// Check if the pawn can take a piece
			if (std::abs(startPos[1] - endPos[1]) == 1 && std::abs((startPos[2] - endPos[2])) == 1)
			{
				if (playercolor == player::Color::whitePlayer)
				{
					for (int i = 0; i < 16; i++)
					{
						if (board.blackPlayer.pieces[i][1] == endPos[1] && board.blackPlayer.pieces[i][2] == endPos[2])
						{
							//Then we need to preform takeing said piece
							board.blackPlayer.pieces[i][0] = 'x';
							board.whitePlayer.score.pawns += 1;
							return true;
						}
					}
				}
				else
				{
					for (int i = 0; i < 16; i++)
					{
						if (board.whitePlayer.pieces[i][1] == endPos[1] && board.whitePlayer.pieces[i][2] == endPos[2])
						{
							//Then we need to preform takeing said piece
							board.whitePlayer.pieces[i][0] = 'x';
							board.blackPlayer.score.pawns += 1;
							return true;
						}
					}
				}

			}
		}
		std::cout << "Invalid movement";
		return false;
		break;

	}

}

bool isSquareEmpty(char endPos[], Chessboard& board)
{
	for (int i = 0; i < 16; i++)
	{
		if (board.blackPlayer.pieces[i][1] == endPos[1] && board.blackPlayer.pieces[i][2] == endPos[2])
		{
			return false;
		}
		if (board.whitePlayer.pieces[i][1] == endPos[1] && board.whitePlayer.pieces[i][2] == endPos[2])
		{
			return false;
		}
	}
	return true;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
