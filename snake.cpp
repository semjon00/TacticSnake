#include "snake.h"

#include "engine.h"
#include "ui.h"

Snake::Snake(int _player_number, std::pair<int, int> startPos)
{
    player_number = _player_number;
    seed = rand();

    colors[0] = snakes_colors[player_number][0];
    colors[1] = snakes_colors[player_number][1];

    visited_cords.emplace_back(startPos);
    drawPart(getHeadX(), getHeadY(), HEAD);
}

short Snake::getHeadX()
{
    return visited_cords.back().first;
}
short Snake::getHeadY()
{
    return visited_cords.back().second;
}

// Asks the snake to pick relative coords to turn to
std::pair<int, int> Snake::pickTurn()
{
    {
    // Player makes a turn
        short deltaX=0, deltaY=0;
        flushGetch();
        char c = 'n';
        int steps=1;
        do
        {
            // Extender
            if (c=='q')
            {
                int maxExtender = 1 + bonus_avaible[0] + bonus_avaible[1];
                toggle(steps, 1,maxExtender);
            }
            playerBarUpdate(steps, player_number, false);

            c = waitKey();
        } while (c!='w' && c!='a' && c!='s' && c!='d');

        // Directional
        while (true) {
            switch (c)
            {
                case 'w':
                    deltaY+=-1;
                    break;
                case 'a':
                    deltaX+=-1;
                    break;
                case 's':
                    deltaY+= 1;
                    break;
                case 'd':
                    deltaX+= 1;
                    break;
                default:
                    // Something made player rethink extender length, it is ok
                    break;
            }
            steps--;
            playerBarUpdate(steps, player_number, false);
            draw(1,1,((rand() % 14) + 1)*17, " ");

            if (steps == 0)
                break;
            else
                c = waitKey();
        };

        // draw(1,1,(player_number+3)*17, "X");
        return std::make_pair(deltaX, deltaY);
    }
}

// Update to be turned to x,y (real)
void Snake::makeMove(int x, int y) {
    drawPart(getHeadX(), getHeadY(), REGULAR);
    visited_cords.emplace_back(x, y);
    drawPart(getHeadX(), getHeadY(), HEAD);
}

void Snake::drawPart(short x, short y, int part)
{
    int color = colors[0];

    if (part == EMPTY)
        color = 0;
    else if (part==REGULAR && !UI::settings.strict_color_mode)
    {
        if (hash(seed*10000 + x * 100 + y)%3 == 0)
            color = colors[1];
    }

    for(short i=0; i<3; i++)
        draw(x*3+3, y*3+3+i, color, debris[part][i]);
}

void Snake::lose(bool corpseMode)
{
    // Actions on death
    isDead = true;

    // Visual effect
    draw(2, 3+3*7+3, player_number*2+2,
            "Game Over for player #" + std::to_string(player_number+1) + "!");

    if (!corpseMode)
    {
        // No-corpse mode animation and effects
        pause(250);
        drawPart(getHeadX(), getHeadY(), CORPSE_HEAD);
        pause(250);
        for(auto & visited_cord : visited_cords)
        {
            drawPart(visited_cord.first, visited_cord.second, EMPTY);
            pause(100);
        }
    }
    else
    {
        // Corpse mode animation
        pause(250);
        drawPart(getHeadX(), getHeadY(), CORPSE_HEAD);
    }
}

void Snake::win()
{
    draw(2, 3+3*7+3, player_number*2+2, "Congratulations!         ");
    drawPart(getHeadX(), getHeadY(), WIN_HEAD);
}
