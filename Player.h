#ifndef TACTICSNAKE_PLAYER_H
#define TACTICSNAKE_PLAYER_H

#include "snake.h"

class Player : public Snake {
public:
    Player(int _player_number, std::pair<int, int> startPos) : Snake(_player_number, startPos) {};

    std::pair<int, int> pickTurn() override;
    void applyTurn(int x, int y) override;
};


#endif //TACTICSNAKE_PLAYER_H
