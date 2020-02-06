#include "snake.h"

#include "engine.h"
#include "ui.h"

Snake::Snake(int _player_number, ControlModes _control_mode, std::pair<int, int> startPos)
{
    player_number = _player_number;
    control_mode = _control_mode;

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
    switch (control_mode)
    {
    // Player makes a turn
    case PLAYER:
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

            if (steps == 0)
                break;
            else
                c = waitKey();
        };

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
    int color;
    switch (part)
    {
    case REGULAR:
        color = (2*player_number+2)*(16+1);
        break;
    case HEAD:
        color = (2*player_number+2)*(16+1)-1;
        break;
    case CORPSE_HEAD:
        color = (2*player_number+2)*(16+1)-1;
        break;
    case WATSON_HEAD:
        color = (2*player_number+2)*(16+1)-1;
        break;
    case WIN_HEAD:
        color = (2*player_number+2)*(16+1)-1;
        break;
    default:
        color = BLACK;
        break;
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
        Sleep(250);
        drawPart(getHeadX(), getHeadY(), CORPSE_HEAD);
        Sleep(250);
        for(auto & visited_cord : visited_cords)
        {
            drawPart(visited_cord.first, visited_cord.second, EMPTY);
            Sleep(100);
        }
    }
    else
    {
        // Corpse mode animation
        Sleep(250);
        drawPart(getHeadX(), getHeadY(), CORPSE_HEAD);
    }
}

void Snake::win()
{
    draw(2, 3+3*7+3, player_number*2+2, "Congratulations!         ");
    drawPart(getHeadX(), getHeadY(), WIN_HEAD);
}
