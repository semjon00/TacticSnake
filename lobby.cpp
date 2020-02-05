#include "lobby.h"

#include "engine.h"
#include "version.h"

Lobby::Lobby()
{
    // Initializing random-number generator
    srand(time(nullptr));

    // Making window correct size
    system("MODE 30,30");

    // Header with easter egg
    if (rand()%50 != 0)
        system("title Tactic Snake!");
    else if (rand()%2 == 0)
        system("title Tactic Sanek!");
    else
        system("title tic tac Snake!");

    disableBlinking();
}

void Lobby::mainScreen()
{
    bool to_exit = false;
    while (!to_exit)
    {
        // Screen options
        setColor(BLACK);
        cls();
        draw(10,10,GRAY,"Hot seat");
        draw(10,11,GRAY,"I/O Multiplayer");
        draw(10,14,GRAY,"Settings");
        draw(10,16,GRAY,"Exit");

        // Version of the product
        gotoXY(0, 29);
        setColor(Version::BUILD % 7 + 1);
        std::cout << 'v' << Version::MAJOR << '.'
                  << Version::MINOR << '.'
                  << Version::BUILD;

        // Choose switch
        switch (choosing({10, 11, 14, 16}, 8, YELLOW, ">"))
        {
        case 0:
            to_exit = true;
            is_in_game = true;
            net_usage = false;
            break;
        case 1:
            to_exit = true;
            is_in_game = true;
            net_usage = true;
            break;
        case 2:
            settingsScreen();
            break;
        case 3:
            // Exiting game
            draw(10,18,RED*16+GREEN,"GOODBYE!");
            Sleep(1000);
            setColor(0);
            gotoXY(15,18);
            is_running = false;
            to_exit = true;
            break;
        }
    }
}

void Lobby::settingsScreen()
{
    bool to_exit = false;
    while (!to_exit)
    {
        // Screen
        cls();

        draw(7, 11, GRAY, "Players ");
        draw(20, 11, GREEN, std::to_string(snakes_total));

        draw(7, 13, GRAY, "Corpse mode ");
        draw(20, 13, GREEN, corpseMode ? "[--I]" : "[O--]");

        //draw(7, 15, GRAY, "Portal walls ");
        //draw(20, 15, GREEN, portal_walls ? "[--I]" : "[O--]");

        draw(7, 21, GRAY, "Open dev codes");

        draw(7, 23, GRAY, "Back");

        // Choose
        switch(choosing({11, 13, /*15,*/ 21, 23}, 4, YELLOW, ">"))
        {
        case 0:
            toggle(&snakes_total, 2, 4);
            break;
        case 1:
            corpseMode = !corpseMode;
            break;
        //case 2:
        //    portal_walls = !portal_walls;
        //    break;
        case 2:
            _debugCharacterCast();
            break;
        case 3:
            to_exit = true;
            break;
        }
    }
}

void Lobby::wrongBuildScreen(int build_number)
{
    cls();

    draw(7, 10, RED, "Builds do not match!");

    draw(2, 12, YELLOW, "It looks like you are using an incompatible build...");

    draw(2, 15, GRAY, "Your build is #");
    std::cout << Version::BUILD;

    draw(2, 16, GRAY, "Game is run at build #");
    std::cout << build_number;

    draw(2, 18, GREEN, "Please obtain the most recent");
    draw(2, 19, GREEN, "build from GitHub.");

    _getch();
}
