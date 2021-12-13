#include "Game.h"
#include "engine.h"

Game::Game(const GameSettings& _settings) {
    settings = _settings;

    // Drawing field
    cls();
    drawFrame(2, 2, 3*settings.field_width, 3*settings.field_height, GRAY, (settings.portal_walls ? '0' :'#'));
    draw(2, 3+3*(settings.field_height)+2, GRAY, "Current player: ");

    // Init
    board = std::vector<std::vector<int>> (settings.field_width, std::vector<int> (settings.field_height, -1));
    std::vector<Snake> snakes;
    static std::pair<int,int> spawn_coords[4] = {
            {0, 0},
            {_settings.field_width - 1, _settings.field_height - 1},
            {0, _settings.field_height - 1},
            {_settings.field_width - 1, 0}
    };
    for(int i = 0; i<settings.snakes_total; i++)
    {
        snakes.emplace_back(i, spawn_coords[i]);
        board[spawn_coords[i].first][spawn_coords[i].second] = i;
    }
    snakes_alive = settings.snakes_total;

    // Main game loop
    while (isGameOn)
    {
        for(auto & snake : snakes)
        {
            // Main loop
            if (snake.isDead)
                continue;

            if (snakes_alive<=1)
            {
                snake.win();
                isGameOn = false;
                break;
            }
            if (movesAvailable(snake)) {
                std::pair<int,int> got;
                do {
                    got = snake.pickTurn();
                } while(!turn(got.first, got.second, snake));
            } else {
                snake.lose(settings.corpseMode);
                if (!settings.corpseMode)
                    removeCorpse(snake);
                snakes_alive--;
            }
        }
    }

    pause(2000);
}

void Game::removeCorpse(Snake &snake) {
    for(auto & visited_cord : snake.visited_cords)
    {
        board[visited_cord.first][visited_cord.second] = -1;
    }
}

// Get value of the cell, resulting from raw coordinates x,y
int Game::getBoardAt(int x, int y)
{
    auto real = getRealCoords(x,y);
    if (real.first == -1)
        return -2;
    else
        return board[real.first][real.second];
}

// Returns {-1,?} if there is no such cell
std::pair<int,int> Game::getRealCoords(int x, int y)
{
    std::pair<int,int> real = {x,y};
    if (settings.portal_walls)
    {
        real.first = (real.first  + settings.field_width ) % settings.field_width;
        real.second= (real.second + settings.field_height) % settings.field_height;
        return real;
    }

    if (x>=0 && x<settings.field_width && y>=0 && y<settings.field_height)
    {
        return real;
    } else
        return voidCell;
}

bool Game::movesAvailable(Snake &snake)
{
    for (short k1=-1; k1<2; k1+=2)
    {
        for (short k2=0; k2<2; ++k2)
        {
            // Checking adjacent-cell moves
            if (getBoardAt(snake.getHeadX() + (k2 ? 0 : k1), snake.getHeadY() + (k2 ? k1 : 0)) == -1)
                return true;

            // Checking jumps
            if (snake.bonus_avaible[0] && (getBoardAt(snake.getHeadX() + (k2 ? 0 : k1 * 2),
                                                      snake.getHeadY() + (k2 ? k1 * 2 : 0)) == -1))
                return true;

            // Checking "knight" moves
            if (snake.bonus_avaible[0] && snake.bonus_avaible[1])
            {
                if (getBoardAt(snake.getHeadX() + k1, snake.getHeadY() + k2 * 4 - 2) == -1 || \
                    getBoardAt(snake.getHeadX() + k2 * 4 - 2, snake.getHeadY() + k1) == -1 )
                    return true;
            }
        }

        // Checking diagonal moves
        if (snake.bonus_avaible[1])
        {
            for (short k2=-1; k2<2; k2+=2)
            {
                if (getBoardAt(snake.getHeadX() + k1, snake.getHeadY() + k2) == -1)
                    return true;
            }
        }
    }
    return false;
}

// Attempt to turn the snake, given relative coords
bool Game::turn(short deltaX, short deltaY, Snake &snake)
{
    bool bonuses_to_take[2] = {false, false};

    std::pair<int,int> newRaw = {snake.getHeadX() + deltaX, snake.getHeadY() + deltaY};

    // Check if cell is available
    if (getBoardAt(newRaw.first, newRaw.second) != -1)
        return false;

    // TODO: Probably should be a new function (determining bonuses)
    // Checking for too long jumps
    if ((deltaX+3)%3+(deltaY+3)%3==0)
        return false;

    // Long jump handeling
    if (abs(deltaX)==2||abs(deltaY)==2)
    {
        if (!snake.bonus_avaible[0])
            return false;
        else
            bonuses_to_take[0]=true;
    }

    // Diagonal handeling
    if (abs(deltaX)>=1&&abs(deltaY)>=1)
    {
        if (!snake.bonus_avaible[1])
            return false;
        else
            bonuses_to_take[1]=true;
    }


    // Updating bonuses
    snake.bonus_avaible[0] &= !bonuses_to_take[0];
    snake.bonus_avaible[1] &= !bonuses_to_take[1];

    std::pair<int,int> newReal = getRealCoords(newRaw.first, newRaw.second);
    snake.makeMove(newReal.first, newReal.second);
    setBoardAt(newReal.first, newReal.second, snake.player_number);
    return true;
}

void Game::setBoardAt(int x, int y, int val) {
    if (settings.portal_walls)
    {
        board[(x+settings.field_width)%settings.field_width][(y+settings.field_height)%settings.field_height] = val;
    }
    else if (x>=0 && x<settings.field_width && y>=0 && y<settings.field_height)
    {
        board[x][y] = val;
    }
}
