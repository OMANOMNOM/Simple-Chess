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

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <memory>  // for allocator, __shared_ptr_access
#include <string>  // for char_traits, operator+, string, basic_string
#include <chrono>                  // for operator""s, chrono_literals
#include <thread>  // for sleep_for
#include <functional>
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref
#include "ftxui/dom/node.hpp"      // for Render
#include "ftxui/screen/color.hpp"  // for ftxui

std::chrono::time_point<std::chrono::high_resolution_clock> start;
std::string timerString = "empty";
ftxui::Component* curScreen = nullptr;
ftxui::Component renderLoadingScreen;
ftxui::Component renderMenu;
ftxui::Component renderGame;
Chessboard board;
int curPlayerId;
player* curPlayer = nullptr;
std::string content;
std::string content1;


ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

void clearDisplay(HANDLE& hStdOut, const DWORD& originalMode);
void EnableVirtualTerminalSequences(HANDLE& hStdOut, DWORD originalMode);
void PlayerTurn(int& curPlayerId, player*& curPlayer, Chessboard& board);
void getInputArray(std::string& input, char startPos[]);
int updateTimer();
std::function<void()> startTimer();
std::function<void()> pieceSelection();

int playGame();

int main() {

	using namespace ftxui;
	using namespace std::chrono_literals;
	//Menu stuff
	std::vector<std::string> entries = {
	"New Game",
	"Options",
	"Exit",
	};
	MenuOption option;
	int selected = 0;
	curScreen = nullptr;
	auto menuObject = Menu(&entries, &selected, &option);

	content = "";
	std::string placeholder = "placeholder";
	std::string placeholder1 = "test ";

	InputOption inputoptions;
	inputoptions.on_enter = &pieceSelection;
	Component input = Input(&content, &placeholder, &inputoptions);
	Component inputDestination = Input(&content1, &placeholder1, &inputoptions);

	auto component = Container::Vertical({
	input,
	inputDestination,
	
		});

	renderGame = Renderer(component,  [&] {
		// Input box
		
		// Chessboard componet
		std::vector<std::string> strings;
		std::string b = board.printChessboard();
		int curPos = 0;
		while (curPos < b.length() - 1) {
			int x = b.find("\n", curPos);
			if (x == std::string::npos)
			{
				curPos = b.length();
			}
			else {
				strings.push_back(b.substr(curPos, x - curPos));
				curPos = x + 1;
			}

		}

		//chess logic
		std::string playerPromt = "";
		if (curPlayerId + 1 == 2) {
			playerPromt = "Player " + std::to_string(curPlayerId + 1);
		}
		else {
			playerPromt = "Player " + std::to_string(curPlayerId + 1);
		}
			playerPromt += " it is now your turn";
			return
				gridbox({
					{
					filler(),
					vbox({
						text(strings[0]),
						text(strings[1]),
						text(strings[2]),
						text(strings[3]),
						text(strings[4]),
						text(strings[5]),
						text(strings[6]),
						text(strings[7]),
						text(strings[8]),
						text(strings[9]),
						text(strings[10]),
						text(strings[11]),
						text(strings[12]),
						text(strings[13]),
						text(strings[14]),
						text(strings[15]),
						text(strings[16]),
						text(strings[17]),
						}),
						border(
								vbox({
									text(playerPromt),
									hbox({input->Render()}),
									hbox({inputDestination->Render()}),
								})
						),
				filler(),
				}
				}) |
			border;
		});

	renderLoadingScreen = Renderer(menuObject, [&] {
		// Update the timer.
		int duration = updateTimer();
		if (duration >= 1.0f)
		{
			// Change the screen to show chess
			
			board = Chessboard();
			curPlayerId = 0;
			curPlayer = &board.whitePlayer;
			screen.ExitLoopClosure();

			curScreen = &renderGame;
			screen.Loop(*curScreen);
			playGame();

		}
		return
			gridbox({
				{
				filler(),
				vbox({
					gauge(duration / 10.0),
					text("this is a test"),
					text(timerString),
				}),
				filler(),
				}
				}) |
			border;
		});

	renderMenu = Renderer(menuObject, [&] {
		// Stick everything in here that i want to render
		return
			gridbox({
				{
				filler(),
				vbox({
					text("Chess game"),
					vbox({
						text(R"(                                                       .::.)"),
						text(R"(                                            _()_       _::_)"),
						text(R"(                                  _O      _/____\_   _/____\_)"),
						text(R"(           _  _  _     ^^__      / //\    \      /   \      /)"),
						text(R"(          | || || |   /  - \_   {     }    \____/     \____/)"),
						text(R"(          |_______| <|    __<    \___/     (____)     (____))"),
						text(R"(    _     \__ ___ / <|    \      (___)      |  |       |  |)"),
						text(R"(   (_)     |___|_|  <|     \      |_|       |__|       |__|)"),
						text(R"(  (___)    |_|___|  <|______\    /   \     /    \     /    \)"),
						text(R"(  _|_|_    |___|_|   _|____|_   (_____)   (______)   (______))"),
						text(R"( (_____)  (_______) (________) (_______) (________) (________))"),
						text(R"( /_____\  /_______\ /________\ /_______\ /________\ /________\)"),
						text(R"(                                             __By Alefith 22.02.95__)"),

					}),
					separator(),
					border(
						vbox({
						menuObject->Render(),
						})
					),
				})
				| border,
				filler(),
				}
				});
		});
	curScreen = &renderMenu;
	option.on_enter = &startTimer;
	screen.Loop(*curScreen);


}

//void PlayerTurn(int& curPlayerId, player*& curPlayer, Chessboard& board)
//{
//	if (curPlayerId + 1 == 2) {
//		printf(CSI "30m");
//		std::cout << "Player " << curPlayerId + 1;
//		printf(CSI "0m");
//	}
//	else
//		std::cout << "Player " << curPlayerId + 1;
//	std::cout << " it is now your turn" << std::endl;
//	std::string input;
//	char endPos[3]{};
//	char startPos[3]{};
//	bool isValidInput = false;
//	// While loop
//	while (!isValidInput) {
//		std::wcout << "Please enter the piece you'd like to move (piece, x, y);"
//			<< std::endl;
//		std::cin >> input;
//		std::cin.ignore(200, '\n');
//		if (input.size() == 5) {
//			getInputArray(input, startPos);
//			if (ChessRules::isValidSelection(startPos, curPlayer))
//			{
//				isValidInput = true;
//			}
//		}
//	}
//
//	isValidInput = false;
//	while (!isValidInput) {
//		std::wcout
//			<< "Please enter the position you'd like to move to (piece, x, y):"
//			<< std::endl;
//		std::cin >> input;
//		std::cin.ignore(200, '\n');
//		if (input.size() == 5) {
//			getInputArray(input, endPos);
//			if (ChessRules::isValidTraversal(startPos, endPos, curPlayer->playerColor, board)) {
//				if (ChessRules::isSquareEmptyOrTakeable(endPos, board, curPlayer->playerColor))
//					isValidInput = true;
//			}
//		}
//	}
//	curPlayer->pieces->SetPosition(startPos, endPos);
//	if (curPlayerId == 0) {
//		curPlayerId = 1;
//		curPlayer = &board.blackPlayer;
//	}
//	else {
//		curPlayerId = 0;
//		curPlayer = &board.whitePlayer;
//	}
//}

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

int updateTimer() {
	auto temp = std::chrono::high_resolution_clock::now() - start;
	auto timeDuration = std::chrono::duration_cast<std::chrono::seconds>(temp);
	return timeDuration.count();
}
std::function<void()> pieceSelection()
{
	char inputArray[3];
	getInputArray(content, inputArray);
	bool isValidInput = false;
	while (!isValidInput) {
		//std::wcout << "Please enter the piece you'd like to move (piece, x, y);"
			//<< std::endl;
		if (content.size() == 5) {
			getInputArray(content, inputArray);
			if (ChessRules::isValidSelection(inputArray, curPlayer))
			{
				isValidInput = true;
			}
		}
	}
	return nullptr;
}

std::function<void()> startTimer()
{
	start = std::chrono::high_resolution_clock::now();
	screen.ExitLoopClosure();
	curScreen = &renderLoadingScreen;
	screen.Loop(*curScreen);

	return nullptr;
}

int playGame() {
	//HANDLE hStdOut;
	//DWORD originalMode = 0;
	//EnableVirtualTerminalSequences(hStdOut, originalMode);
	//HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//if (hOut == INVALID_HANDLE_VALUE) {
	//	printf("Couldn't get the console handle. Quitting.\n");
	//	return -1;
	//}
	//Chessboard board = Chessboard();
	//int curPlayerId = 0;
	//player* curPlayer = &board.whitePlayer;

	while (true) {
		//board.printChessboard();
		//PlayerTurn(curPlayerId, curPlayer, board);
		//clearDisplay(hStdOut, originalMode);
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