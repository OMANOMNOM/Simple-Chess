#pragma once
#include "Score.h"
class player
{
public:
	char pieces[16][3]{
		{'P', '0','1'},
		{'P', '1','4'},
		{'P', '2','1'},
		{'P', '3','1'},
		{'P', '4','1'},
		{'P', '5','1'},
		{'P', '6','1'},
		{'P', '7','1'},

		{'R', '0','0'},
		{'N', '1','0'},
		{'B', '2','0'},
		{'K', '3','0'},
		{'Q', '4','0'},
		{'B', '5','0'},
		{'N', '6','0'},
		{'R', '7','0'}
	};

	enum Color
	{
		whitePlayer,
		blackPlayer,
	};
	Color playerColor; 
	Score score;
	player(player::Color color) 
		: playerColor{ color}
	{
	
	}

public:

	void setPosition(char[], char[]);
};

