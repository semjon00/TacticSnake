#include "engine.h"
#include "snake.h"
#include "net.h"
#include "lobby.h"

int main()
{
    Lobby lobby;
    Net net;

    while (true)
    {
        lobby.mainScreen();
        if (!lobby.is_running)
        {
            // Handeling exit from the game
            return 0;
        }

        // Syncing settings
        if (lobby.net_usage)
        {
            if (net.synchSettings(&lobby))
            {
                // Gatting out from game
                continue;
            }
        }


        // Drawing field
        cls();
        drawFrame(2, 2, 3*(lobby.field_width), 3*(lobby.field_height), GRAY, '#');
        draw(2, 3+3*(lobby.field_height)+2, GRAY, "Current player: ");

        // Creating field
        std::vector<std::vector<short>> board
            (lobby.field_width, std::vector<short> (lobby.field_height, -1));

        // Creating snakes
        std::vector<Snake> snakes;

        if (lobby.net_usage)
        {
            bool net_local_ocupied = false;
            for(int i = 0; i<lobby.snakes_total; i++)
            {
                if (net.wasUpdated(i, 0) || net_local_ocupied)
                {
                    snakes.push_back(Snake(i, &board, &lobby, &net, NET));
                }
                else
                {
                    snakes.push_back(Snake(i, &board, &lobby, &net, PLAYER));
                    net_local_ocupied = true;
                }
            }
            if (!net_local_ocupied)
            {
                // I am observer
            }
        }
        else
        {
            for(int i = 0; i<lobby.snakes_total; i++)
            {
                snakes.push_back(Snake(i, &board, &lobby, &net, PLAYER));
            }
        }

        lobby.snakes_in_game = lobby.snakes_total;

        // Making snakes move
        while (lobby.is_in_game)
        {
            for(unsigned int i=0; i<snakes.size(); ++i)
            {
                // Main loop
                snakes[i].makeMove();

                if (lobby.snakes_in_game<=1)
                {
                    // Game won
                    lobby.is_in_game=false;

                    // Finding snake and make it celebrate
                    for(int u=0; u<lobby.snakes_total; u++)
                    {
                        if (!snakes[u].isDead)
                        {
                            snakes[u].win();
                            break;
                        }
                    }
                    Sleep(2000);

                    // Clearing files
                    if (lobby.net_usage)
                    {
                        for (int u=0; u<lobby.snakes_total; u++)
                        {
                            net.voidState(u);
                        }
                    }
                    break;
                }
            }
        }
        cls();
    }
}
