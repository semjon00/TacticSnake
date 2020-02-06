#include "Game.h"
#include "engine.h"

Game::Game(const GameSettings& _settings) {
    settings = _settings;

    // Drawing field
    cls();
    drawFrame(2, 2, 3*settings.field_width, 3*settings.field_height, GRAY, (settings.portal_walls ? '0' :'#'));
    draw(2, 3+3*(settings.field_height)+2, GRAY, "Current player: ");

    // Init board
    board = std::vector<std::vector<int>> (settings.field_width, std::vector<int> (settings.field_height, -1));

    std::vector<Snake> snakes;
    for(int i = 0; i<settings.snakes_total; i++)
    {
        snakes.push_back(Snake(i, PLAYER, spawn_coords[i]));
        board[spawn_coords[i].first][spawn_coords[i].second] = i;
    }
//    }

    snakes_alive = settings.snakes_total;

    // Making snakes move
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
            }
            else if (cellsAvaible(snake)) {
                std::pair<int,int> got;
                do {
                    got = snake.makeMove();
                } while(!turn(got.first, got.second, snake));
            } else {
                snake.lose(settings.corpseMode);
                if (settings.corpseMode)
                    removeCorpse(snake);
                snakes_alive--;
            }

            // Net things?
        }
    }

    Sleep(2000);
    cls();
}

Game::Game(std::string ip) {
    // For Net
}

void Game::removeCorpse(Snake &snake) {
    for(auto & visited_cord : snake.visited_cords)
    {
        board[visited_cord.first][visited_cord.second] = -1;
    }
}

int Game::getBoardAt(int x, int y)
{
    if (settings.portal_walls)
    {
        return board[(x+settings.field_width)%settings.field_width][(y+settings.field_height)%settings.field_height];
    }
    else if (x>=0 && x<settings.field_width && y>=0 && y<settings.field_height)
    {
        return board[x][y];
    }
    return -2;
}

bool Game::cellsAvaible(Snake &snake)
{
    bool is_space_avaible = false;

    for (short k1=-1; k1<2; k1+=2)
    {
        for (short k2=0; k2<2; ++k2)
        {
            // Checking straight moves
            if (getBoardAt(snake.getHeadX() + (k2 ? 0 : k1), snake.getHeadY() + (k2 ? k1 : 0)) == -1)
                is_space_avaible = true;
            // Checking long jumps
            if (snake.bonus_avaible[0] && (getBoardAt(snake.getHeadX() + (k2 ? 0 : k1 * 2),
                                                      snake.getHeadY() + (k2 ? k1 * 2 : 0)) == -1))
                is_space_avaible = true;
            // Checking both at the same time
            if (snake.bonus_avaible[0] && snake.bonus_avaible[1])
            {
                if (getBoardAt(snake.getHeadX() + k1, snake.getHeadY() + k2 * 4 - 2) == -1 || \
                    getBoardAt(snake.getHeadX() + k2 * 4 - 2, snake.getHeadY() + k1) == -1 )
                    is_space_avaible = true;
            }
        }
        // Checking diagonal
        if (snake.bonus_avaible[1])
        {
            for (short k2=-1; k2<2; k2+=2)
            {
                if (getBoardAt(snake.getHeadX() + k1, snake.getHeadY() + k2) == -1)
                    is_space_avaible = true;
            }
        }
    }
    return is_space_avaible;
}

bool Game::turn(short x, short y, Snake &snake)
{
    bool bonuses_to_take[2] = {false, false};
    int deltaX = x - snake.getHeadX();
    int deltaY = y - snake.getHeadY();

    // Getting boundary safe at first
    if (!settings.portal_walls)
    {
        if (getBoardAt(x, y) == -2)
            return false;
    }

    // Checking for allowance
    if (getBoardAt(x,y) != -1)
        return false;

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

    snake.drawPart(snake.getHeadX(), snake.getHeadY(), REGULAR);
    snake.visited_cords.emplace_back(x, y);
    snake.drawPart(snake.getHeadX(), snake.getHeadY(), HEAD);

    // Updating bonuses
    snake.bonus_avaible[0] = bonuses_to_take[0] ? false : snake.bonus_avaible[0];
    snake.bonus_avaible[1] = bonuses_to_take[1] ? false : snake.bonus_avaible[1];

    // Updating cell and visited_cords
    setBoardAt(x,y,snake.player_number);

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
