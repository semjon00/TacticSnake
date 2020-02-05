#include "snake.h"

Snake::Snake(short _player_number, std::vector<std::vector<short>>* _board, Lobby* _lobby, Net* _net, ControlModes _control_mode)
{
    player_number = _player_number;
    control_mode = _control_mode;
    board = _board;
    lobby = _lobby;
    net = _net;

    visited_cords.emplace_back(lobby->spawn_coords[player_number*2],lobby->spawn_coords[player_number*2+1]);

    if (lobby->net_usage && control_mode == PLAYER)
    {
        net->writeState(player_number, &visited_cords);
    }

    while (lobby->net_usage && (!net->wasUpdated(player_number, -1)))
    {
        Sleep(net->net_synch_delay);
    }

    drawPart(getHeadX(), getHeadY(), 2);
    (*board)[lobby->spawn_coords[player_number*2]][lobby->spawn_coords[player_number*2+1]] = player_number;
}


short Snake::getHeadX()
{
    return visited_cords.back().first;
}
short Snake::getHeadY()
{
    return visited_cords.back().second;
}

int Snake::safeBoard(short x, short y)
{
    if (!(x<0 || x>=lobby->field_width || y<0 || y>=lobby->field_height))
    {
        return (*board)[x][y];
    }
    else
    {
        if (lobby->portal_walls)
        {
            return (*board)[x+lobby->field_width][y+lobby->field_height];
        }
        else
            return -2;
    }
}


void Snake::makeMove()
{
    if (isDead)
    {
        return;
    }
    if (!cellsAvaible())
    {
        lose();
        return;
    }

    switch (control_mode)
    {
    // Player makes a turn
    case PLAYER:
        short _deltaX, _deltaY;
        do {
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

                playerBarUpdate(steps, player_number, lobby->net_usage);

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
                    playerBarUpdate(steps, player_number, lobby->net_usage);
                }
                if (steps!=0)
                    c = normalized_getch();
            }
        } while (!moveIfPossible(_deltaX, _deltaY));
        break;
    case NET:
        playerBarUpdate(1, player_number, false);

        // Waiting for move
        while (!net->wasUpdated(player_number, visited_cords.size()))
        {
            Sleep(net->net_synch_delay);
        }

        // Making move and catching cheaters on invalid moves
        std::pair<short,short> recieved_mov = net->readState(player_number,0);
        if (!moveIfPossible(recieved_mov.first - getHeadX(), recieved_mov.second - getHeadY()))
        {
            lose();
        }
        break;
    }
}

bool Snake::moveIfPossible(short deltaX, short deltaY)
{
    bool bonuses_to_take[2] = {false, false};

    // Getting boundary safe at first
    if (!lobby->portal_walls)
    {
        if (safeBoard(getHeadX()+deltaX, getHeadY()+deltaY) == -2)
            return false;
    }

    // Checking for allowance
    if ((*board)[deltaX+getHeadX()][deltaY+getHeadY()] != -1)
        return false;

    // Checking for too long jumps
    if ((deltaX+3)%3+(deltaY+3)%3==0)
        return false;

    // Long jump handeling
    if (abs(deltaX)==2||abs(deltaY)==2)
    {
        if (!bonus_avaible[0])
            return false;
        else
            bonuses_to_take[0]=true;
    }

    // Diagonal handeling
    if (abs(deltaX)>=1&&abs(deltaY)>=1)
    {
        if (!bonus_avaible[1])
            return false;
        else
            bonuses_to_take[1]=true;
    }

    ++moves_done;

    // Drawing snake head and last body part
    drawPart(getHeadX(), getHeadY(), 1);
    drawPart(getHeadX()+deltaX, getHeadY()+deltaY, 2);

    // Updating bonuses
    bonus_avaible[0]=bonuses_to_take[0] ? false : bonus_avaible[0];
    bonus_avaible[1]=bonuses_to_take[1] ? false : bonus_avaible[1];

    // Updating cell and visited_cords
    (*board)[deltaX+getHeadX()][deltaY+getHeadY()] = player_number;

    visited_cords.emplace_back(getHeadX()+deltaX, getHeadY()+deltaY);

    // Updating net if nessesery
    if (lobby->net_usage && control_mode == PLAYER)
    {
        net->writeState(player_number, &visited_cords);
    }

    return true;
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


bool Snake::cellsAvaible()
{
    bool is_space_avaible = false;

    for (short k1=-1; k1<2; k1+=2)
    {
        for (short k2=0; k2<2; ++k2)
        {
            // Checking straight moves
            if (safeBoard(getHeadX() + (k2 ? 0 : k1), getHeadY() + (k2 ? k1 : 0)) == -1)
                is_space_avaible = true;
            // Checking long jumps
            if (bonus_avaible[0] && (safeBoard(getHeadX() + (k2 ? 0 : k1*2), getHeadY() + (k2 ? k1*2 : 0)) == -1))
                is_space_avaible = true;
            // Checking both at the same time
            if (bonus_avaible[0] && bonus_avaible[1])
            {
                if (safeBoard(getHeadX() + k1, getHeadY() + k2*4-2) == -1 ||\
                    safeBoard(getHeadX() + k2*4-2, getHeadY()+k1) == -1 )
                        is_space_avaible = true;
            }
        }
        // Checking diagonal
        if (bonus_avaible[1])
        {
            for (short k2=-1; k2<2; k2+=2)
            {
                if (safeBoard(getHeadX() + k1, getHeadY() + k2) == -1)
                    is_space_avaible = true;
            }
        }
    }
    return is_space_avaible;
}

void Snake::lose()
{
    // Actions on death
    isDead = true;
    lobby->snakes_in_game -= 1;

    // Visual effect
    draw(2, 3+3*7+3, player_number*2+2,
            "Game Over for player #" + std::to_string(player_number+1) + "!");

    if (!lobby->corpseMode)
    {
        // No-corpse mode animation and effects
        Sleep(250);
        drawPart(getHeadX(), getHeadY(), CORPSE_HEAD);
        Sleep(250);
        for(auto & visited_cord : visited_cords)
        {
            drawPart(visited_cord.first, visited_cord.second, EMPTY);
            (*board)[visited_cord.first][visited_cord.second] = -1;
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
