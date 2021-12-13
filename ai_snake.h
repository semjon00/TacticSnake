#ifndef AI_SNAKE_H
#define AI_SNAKE_H

#include "snake.h"
#include "Game.h"

class AISnake : public Snake {
public:
    AISnake(short playerNumber, std::pair<int, int> startPos, Game *_game);
    int getMyHeadIndex() override;
    std::pair<int, int> pickTurn() override;

private:
    Game* game;
};

#endif // AI_SNAKE_H
