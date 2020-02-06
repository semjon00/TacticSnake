#ifndef TACTICSNAKE_GAME_H
#define TACTICSNAKE_GAME_H

#include "GameSettings.h"
#include "snake.h"
#include <string>

class Game {
    Game(std::string ip);
    void removeCorpse(Snake &snake);

    int snakes_alive;
    int isGameOn = true;

    constexpr static std::pair<int,int> spawn_coords[4] = {{0, 0}, {7, 6}, {0, 6}, {7, 0}}; // Snake start coordinates
public:

    GameSettings settings;

    bool cellsAvaible(Snake &snake);

    int getBoardAt(int x, int y);
    void setBoardAt(int x, int y, int val);

    bool turn(short x, short y, Snake &snake);

    Game(const GameSettings& _settings);

private:
    std::vector<std::vector<int>> board;
};


#endif //TACTICSNAKE_GAME_H
