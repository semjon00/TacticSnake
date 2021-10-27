#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>
#include "engine.h"

enum Part
{
    EMPTY, REGULAR, HEAD, CORPSE_HEAD, WIN_HEAD
};

class Snake
{
public:
    Snake(short _player_number, std::pair<int, int> startPos);

    short getHeadX();
    short getHeadY();
    std::pair<int, int> pickTurn();
    void drawPart(short x, short y, int part);
    void makeMove(int x, int y);

    void lose(bool corpseMode);
    void win();

    bool isDead = false;
    std::vector<std::pair<short,short>> visited_cords;
    int seed;

    // Long jump and diagonal
    bool bonus_avaible[2] = {true, true};
    short player_number;

protected:
    const char* debris[8][3] = {
            {"   ", "   ", "   "}, // Empty
            {"   ", "   ", "   "}, // Regular
            {"* *", "   ", "___"}, // Head
            {"x x", "   ", "___"}, // Corpse head
            {"o^o", "   ", "__j"}, // Watson head
            {"^ ^", "   ", "c_j"}, // Win head
            {"T T", "   ", " _ "}, // Cry emoji head
            {"o -", "   ", " -<"}, // Kiss emoji head
    };

    const int snakes_colors[4][2] = {
            {16*DARKGREEN + DARKBLUE, 16*GREEN + BLACK},
            {16*DARKRED + DARKCYAN, 16*RED + BLACK},
            {16*DARKYELLOW + DARKMAGENTA, 16*YELLOW + BLACK},
            {16*DARKGRAY + WHITE, 16*GRAY + BLACK},
    };

};
#endif // SNAKE_H
