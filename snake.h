#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>

enum ControlModes
{
    PLAYER, NET, CPU
};

enum Part
{
    EMPTY, REGULAR, HEAD, CORPSE_HEAD, WATSON_HEAD, WIN_HEAD
};

class Snake
{
public:
    Snake(int _player_number, ControlModes _control_mode, std::pair<int, int> startPos);

    short getHeadX();
    short getHeadY();
    std::pair<int, int> makeMove();
    void drawPart(short x, short y, int part);

    void lose(bool corpseMode);
    void win();

    ControlModes control_mode = PLAYER;
    bool isDead = false;
    std::vector<std::pair<short,short>> visited_cords;

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
};
#endif // SNAKE_H
