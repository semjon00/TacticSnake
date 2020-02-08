#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>

enum Part
{
    EMPTY, REGULAR, HEAD, CORPSE_HEAD, WATSON_HEAD, WIN_HEAD
};

class Snake
{
public:
    Snake(int _player_number, std::pair<int, int> startPos);

    short getHeadX();
    short getHeadY();

    virtual std::pair<int, int> pickTurn() =0; // Asks the snake to pick relative coords to turn to
    virtual void applyTurn(int x, int y); // Update to be turned to x,y (real)

    void drawPart(short x, short y, int part);
    void lose(bool corpseMode);
    void win();

    bool isDead = false;
    std::vector<std::pair<short,short>> visited_cords;
    int seed;
    int colors[2]; // Base and alternative
    bool bonus_avaible[2] = {true, true}; // Long jump and diagonal
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
