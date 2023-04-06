// Simple Chess.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <Windows.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <String>
#include <iostream>
#include "Chessboard.h"
#include "Pieces.h"
#include "ChessRules.h"

#include <functional>  // for function
#include <string>    // for string, basic_string, allocator

#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/component.hpp"           // for Menu
#include "ftxui/component/component_options.hpp"   // for MenuOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#define CSI "\x1b["

void clearDisplay(HANDLE& hStdOut, const DWORD& originalMode);
void EnableVirtualTerminalSequences(HANDLE& hStdOut, DWORD originalMode);
void PlayerTurn(int& curPlayerId, player*& curPlayer, Chessboard& board);
void getInputArray(std::string& input, char startPos[]);

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
		PlayerTurn(curPlayerId, curPlayer, board);
		clearDisplay(hStdOut, originalMode);
		if (ChessRules::isChecked(board, player::Color::blackPlayer))
			std::cout << "black is checked";
		if (ChessRules::isChecked(board, player::Color::whitePlayer))
			std::cout << "White is checked";
		if (ChessRules::isCheckMate(board, player::Color::blackPlayer))
			std::cout << "black is checkmate ";
		if (ChessRules::isCheckMate(board, player::Color::whitePlayer))
			std::cout << "black is checkmate ";
	}
}

void PlayerTurn(int& curPlayerId, player*& curPlayer, Chessboard& board)
{
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
			if (ChessRules::isValidSelection(startPos, curPlayer))
			{
				isValidInput = true;
			}
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
			if (ChessRules::isValidTraversal(startPos, endPos, curPlayer->playerColor, board)) {
				if (ChessRules::isSquareEmptyOrTakeable(endPos, board, curPlayer->playerColor))
					isValidInput = true;
			}
		}
	}
	curPlayer->pieces->SetPosition(startPos, endPos);
	if (curPlayerId == 0) {
		curPlayerId = 1;
		curPlayer = &board.blackPlayer;
	}
	else {
		curPlayerId = 0;
		curPlayer = &board.whitePlayer;
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

