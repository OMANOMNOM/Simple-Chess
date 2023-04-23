#include "Chessboard.h"
#include <iostream>
#include <windows.h>
#include <string>
#define CSI "\x1b["

std::string Chessboard::PrintRowDivider(bool isEdge)
{
	std::string printout = "";
	if (isEdge)
	{
		printout += "+";
		for (int i = 0; i < 7; i++)
			printout += "----";
		printout += "---+";

	}
	else { 

		printout += "+";
		for (int i = 0; i < 8; i++)
			printout += "---+";
	}
	printout += "\n";
	return printout;
}

std::string Chessboard::PrintVerticalDivider()
{
	return "|";
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

std::string Chessboard::printChessboard()
{
	char columns[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	std::string printout = "";
	// i are rows
	printout += "  ";
	for (int i = 0; i < 8; i++)
	{
		printout += columns[i];
		printout += "   ";
	}
	printout += "\n";
	printout += PrintRowDivider(true);
	for (int i = 7; i >= 0; i--)
	{
		printout += PrintVerticalDivider();

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
					//printf(CSI "30m"); // 
				}
			}
			if (square == 'x')
			{
				square = '  ';
				//square = this->board[i][j];
			}

			printout += " ";
			printout += square;
			printout += " ";
			//printf(CSI "0m");
			printout += PrintVerticalDivider();
		}
		//printout += "  ";
		printout += std::to_string(i+ 1);
		printout +=	+ "  ";
		if (i == 6)
		{
			//print out the scores for blacks
			//std::cout << "Blacks: " << "P:" << blackPlayer.score.pawns << " R:" << blackPlayer.score.rooks << " N:" << blackPlayer.score.knights << " B:" << blackPlayer.score.bishops << " Q:" << blackPlayer.score.queen;

		}
		//	
		//	if (i == 1) {
		//		//Print out the scores for whites
		//		//std::cout << "Whites: " << "P: " << whitePlayer.score.pawns << " R:" << whitePlayer.score.rooks << " N:" << whitePlayer.score.knights << " B:" << whitePlayer.score.bishops << " Q:" << whitePlayer.score.queen;

		//	}
		printout += "\n";
				if (i !=1)
					printout += PrintRowDivider(false);
				else
					printout += PrintRowDivider(true);

	}
	return printout;
}