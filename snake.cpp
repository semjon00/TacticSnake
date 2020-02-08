#include "snake.h"

#include "engine.h"
#include "ui.h"

Snake::Snake(int _player_number, std::pair<int, int> startPos)
{
    player_number = _player_number;
    seed = rand();

    // TODO: Make colors being picked from const
    colors[0] = (2*player_number+2)*(16+1)  - 1;
    colors[1] = (8+2*player_number+2)*(16+1) - 1;
    if (colors[1] == 271)
        colors[1] = 113;

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

void Snake::applyTurn(int x, int y) {
    visited_cords.emplace_back(x, y);
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
