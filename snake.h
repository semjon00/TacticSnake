#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>

#include "engine.h"
#include "lobby.h"
#include "net.h"

enum ControlModes
{
    PLAYER, NET, CPU
};

enum Parts
{
    EMPTY, REGULAR, HEAD, CORPSE_HEAD, WATSON_HEAD, WIN_HEAD
};


class Snake
{
public:
    Snake(short _player_number,
          std::vector<std::vector<short>>* _board,
          Lobby* _lobby,
          Net* _net, ControlModes _control_mode);

    short getHeadX();
    short getHeadY();
    int safeBoard(short x, short y);

    void makeMove();
    bool moveIfPossible(short deltaX, short deltaY);

    void drawPart(short x, short y, int part);

    bool cellsAvaible();
    void lose();
    void win();

    ControlModes control_mode = PLAYER;
    bool isDead = false;
    short moves_done = 0;
private:
    std::vector<std::pair<short,short>> visited_cords;

    // Long jump and diagonal
    bool bonus_avaible[2] = {true, true};

    short player_number;

    // Link to the board object
    std::vector<std::vector<short>>* board;

    // Link to the lobby object
    Lobby* lobby;

    // Link to the net object
    Net* net;

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
