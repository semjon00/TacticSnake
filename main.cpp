/// TODO: ///

/// Nessesery
// Destructors
// No-mess observers
// Settings share

// Spectator mode
// Logo
// Surprices
// Bonus indicators

/// Gameplay
// Corpse mode
// N in M out rule (shorten from back)
// No-straight mode (no more 3 straight turns)
// Obstacles

/// Coding
// Merge board and lobby (new game class?)
// Initializators rewrite
// snake_color

/// Box
// Smart congratulations
// Net time out
// I am always green net coloring mode
// Choosed options highlighting
// Recording and replaying match (with net?)
// Bigger display
// Snake skin
// Notifications
// Line of events
// Faster graphics
// Cpu-controll-mode
// 3D field

#include "engine.h"
#include "snake.h"
#include "net.h"
#include "lobby.h"

int main()
{
    //_debugCharacterCast();

    Lobby lobby;
    Net net;

    while (true)
    {
        lobby.mainScreen();
        if (!lobby.isRunning)
        {
            // Handeling exit from the game
            return 0;
        }

        // Drawing field
        system("cls");
        drawFrame(2,2,3*8,3*7,GRAY,'#');
        draw(2,3+3*7+2,GRAY,"Current player: ");

        // Creating field
        std::vector<std::vector<short>> board (8, std::vector<short> (7, -1));

        // Creating snakes
        std::vector<Snake> snakes;

        bool net_local_ocupied = false;
        for(int i = 0; i<lobby.snakes_total; i++)
        {
            if (lobby.net_usage)
            {
                if (net.wasUpdated(i, 0)||net_local_ocupied)
                {
                    snakes.push_back(Snake(i, &board, &lobby, &net, NET));
                }
                else
                {
                    snakes.push_back(Snake(i, &board, &lobby, &net, PLAYER));
                    net_local_ocupied = true;
                }
            }
            else
            {
                snakes.push_back(Snake(i, &board, &lobby, &net, PLAYER));
            }
        }
        lobby.snakes_in_game = lobby.snakes_total;

        // Making snakes move
        while (lobby.isInGame)
        {
            for(unsigned int i=0; i<snakes.size(); ++i)
            {
                // Main loop
                snakes[i].makeMove();

                if (lobby.snakes_in_game<=1)
                {
                    // Game won
                    lobby.isInGame=0;

                    // Finding snake and make it celebrate
                    for(int i=0; i<lobby.snakes_total; i++)
                    {
                        if (snakes[i].isDead == false)
                        {
                            snakes[i].win();
                            break;
                        }
                    }
                    Sleep(2000);

                    // Clearing files
                    if (lobby.net_usage)
                    {
                        for (int i=0; i<lobby.snakes_total; i++)
                        {
                            net.voidState(i);
                        }
                    }
                    break;
                }
            }
        }
        system("cls");
    }
}
