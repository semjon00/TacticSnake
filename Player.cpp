#include "Player.h"

#include "engine.h"
#include "ui.h"

std::pair<int, int> Player::pickTurn()
{
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

void Player::applyTurn(int x, int y) {
    drawPart(getHeadX(), getHeadY(), REGULAR);
    drawPart(x, y, HEAD);

    Snake::applyTurn(x, y);
}
