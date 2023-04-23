#pragma once
#include "player.h"
#include <string>
class Chessboard
{
public:
    Chessboard();
    char board[8][8]{
        {'w', 'b', 'w', 'b', 'w', 'b', 'w', 'b'},
        {'b', 'w', 'b', 'w', 'b', 'w', 'b', 'w'},
        {'w', 'b', 'w', 'b', 'w', 'b', 'w', 'b'},
        {'b', 'w', 'b', 'w', 'b', 'w', 'b', 'w'},
        {'w', 'b', 'w', 'b', 'w', 'b', 'w', 'b'},
        {'b', 'w', 'b', 'w', 'b', 'w', 'b', 'w'},
        {'w', 'b', 'w', 'b', 'w', 'b', 'w', 'b'},
        {'b', 'w', 'b', 'w', 'b', 'w', 'b', 'w'}
    };
    player whitePlayer{player::Color::whitePlayer};
    player blackPlayer{player::Color::blackPlayer};

    // Chessboard has white in right corners.
    // Each sub array is a row. 
    // chessboard[row][column]
    std::string printChessboard();

    std::string PrintRowDivider(bool isEdge);
    std::string PrintVerticalDivider();
    
};


