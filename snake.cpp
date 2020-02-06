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

std::pair<int, int> Snake::makeMove()
{
    switch (control_mode)
    {
    // Player makes a turn
    case PLAYER:
        short _deltaX, _deltaY;
        flushGetch();
        _deltaX=0, _deltaY=0;
        char c = 'n';
        short steps=1;
        do
        {
            if (c=='q')
            {
                short mod=1;
                for (bool i : bonus_avaible)
                {
                    if (i)
                        mod++;
                }
                steps%=mod;
                steps++;
            }

            playerBarUpdate(steps, player_number, false);

            // Input intake and preprocessing
            c = normalized_getch();

        } while (c!='w' && c!='a' && c!='s' && c!='d');

        while (steps)
        {
            switch (c)
            {
            case 'w':
                _deltaY+=-1;
                break;
            case 'a':
                _deltaX+=-1;
                break;
            case 's':
                _deltaY+= 1;
                break;
            case 'd':
                _deltaX+= 1;
                break;
            }
            if (c=='w'||c=='a'||c=='s'||c=='d');
            {
                steps--;
                playerBarUpdate(steps, player_number, false);
            }
            if (steps!=0)
                c = normalized_getch();
        }
        return std::make_pair(getHeadX()+_deltaX, getHeadY()+_deltaY);
        break;
    }
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
