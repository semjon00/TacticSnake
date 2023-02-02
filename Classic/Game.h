#ifndef TACTICSNAKE_GAME_H
#define TACTICSNAKE_GAME_H

#include "GameSettings.h"
#include "snake.h"
#include <string>

class Game {
    void removeCorpse(Snake &snake);

    int snakes_alive;
    int isGameOn = true;
public:

    GameSettings settings;

    bool movesAvailable(Snake &snake);

    int getBoardAt(int x, int y);
    void setBoardAt(int x, int y, int val);

    bool turn(short deltaX, short deltaY, Snake &snake);

    explicit Game(const GameSettings& _settings);

    const std::pair<int,int> voidCell = {-1,-1};
private:
    std::vector<std::vector<int>> board;

    std::pair<int, int> getRealCoords(int x, int y);
};


#endif //TACTICSNAKE_GAME_H
