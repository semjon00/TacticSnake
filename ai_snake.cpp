#include "ai_snake.h"
#include "snake.h"

using namespace std; // who cares?

AISnake::AISnake(short playerNumber, std::pair<int, int> startPos, Game *_game)
        : Snake(playerNumber, startPos) {
    game = _game;
}

int AISnake::getMyHeadIndex() {
    return WATSON_HEAD;
}

std::pair<int, int> AISnake::pickTurn() {
    if (bonus_avaible[0]) return make_pair(-2, 0);
    if (bonus_avaible[1]) return make_pair(-1, -1);
    int r = rand() % 4;
    if (r == 0) return make_pair(-1, 0);
    if (r == 1) return make_pair(+1, 0);
    if (r == 2) return make_pair(0, -1);
    return make_pair(0, 1);
}
