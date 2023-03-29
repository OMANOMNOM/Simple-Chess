#include "Chessboard.h"
#include <iostream>
#include <windows.h>

#define CSI "\x1b["

void Chessboard::PrintRowDivider(bool isEdge)
{
	if (isEdge)
	{
		std::wcout << "+";
		for (int i = 0; i < 7; i++)
			std::wcout << "----";
		std::wcout << "---+";

	}
	else { 

		std::wcout << "+";
		for (int i = 0; i < 8; i++)
			std::wcout << "---+";
	}
	std::wcout << std::endl;

}

void Chessboard::PrintVerticalDivider()
{
	std::wcout << '|';
}

Chessboard::Chessboard() {
	//Setup black pieces
	for (int i = 0; i < 8; i++) {
		blackPlayer.pieces->piecesArray[i]->info[2] = '6';
	}
	for (int i = 8; i < 16; i++) {
		blackPlayer.pieces->piecesArray[i]->info[2] = '7';
	}
}

void Chessboard::printChessboard()
{
	char columns[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	// i are rows
	std::wcout << "  ";
	for (int i = 0; i < 8; i++)
	{
		std::wcout << columns[i];
		std::wcout << "   ";
	}
	std::wcout << std::endl;
	PrintRowDivider(true);
	for (int i = 7; i >= 0; i--)
	{
		PrintVerticalDivider();

		// J are columns
		for (int j = 0; j < 8; j++)
		{
			char square = 'x';
			// Here we preform the check to see if a piece is here.
			for (int k = 0; k < 16; k++) {
				if ((whitePlayer.pieces->piecesArray[k]->info[1] - '0') == j && (whitePlayer.pieces->piecesArray[k]->info[2] - '0') == i && whitePlayer.pieces->piecesArray[k]->info[0] != 'x')
				{
					square = whitePlayer.pieces->piecesArray[k]->info[0];
				}
			}
			// Here we preform the check to see if a piece is here.
			for (int k = 0; k < 16; k++) {
				if ((blackPlayer.pieces->piecesArray[k]->info[1] - '0') == j && (blackPlayer.pieces->piecesArray[k]->info[2] - '0') == i && blackPlayer.pieces->piecesArray[k]->info[0] != 'x')
				{
					square = blackPlayer.pieces->piecesArray[k]->info[0];
					printf(CSI "30m"); // 
				}
			}
			if (square == 'x')
			{
				square = '   ';
				//square = this->board[i][j];
			}

			std::cout << " " << square << " ";
			printf(CSI "0m");
			PrintVerticalDivider();
		}
		std::wcout << "  " << i + 1 << "  ";
		if (i == 6)
		{
			//print out the scores for blacks
			std::cout << "Blacks: " << "P:" << blackPlayer.score.pawns << " R:" << blackPlayer.score.rooks << " N:" << blackPlayer.score.knights << " B:" << blackPlayer.score.bishops << " Q:" << blackPlayer.score.queen;

		}
		
		if (i == 1) {
			//Print out the scores for whites
			std::cout << "Whites: " << "P: " << whitePlayer.score.pawns << " R:" << whitePlayer.score.rooks << " N:" << whitePlayer.score.knights << " B:" << whitePlayer.score.bishops << " Q:" << whitePlayer.score.queen;

		}
		std::cout << std::endl;
		if (i !=1)
			PrintRowDivider(false);
		else
			PrintRowDivider(true);

	}
}