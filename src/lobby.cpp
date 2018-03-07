#include "lobby.h"

#include "engine.h"
#include "../version.h"

Lobby::Lobby()
{
    // Initializing random-number generator

    // Making window correct size
    system("MODE 30,30");

    // Header
    system("title Tactic Snake!");

    disableBlinking();
}

void Lobby::mainScreen()
{
    bool to_exit = false;
    while (!to_exit)
    {
        // Screen options
        setColor(BLACK);
        system("cls");
        draw(10,10,GRAY,"Hot seat");
        draw(10,11,GRAY,"I/O Multiplayer");
        draw(10,14,GRAY,"Settings");
        draw(10,16,GRAY,"Exit");

        // Version of the product
        gotoXY(0, 29);
        setColor(AutoVersion::BUILD % 7 + 1);
        std::cout << 'v' << AutoVersion::MAJOR << '.'
                         << AutoVersion::MINOR << '.'
                         << AutoVersion::BUILD;

        // Choose switch
        switch (choosing({10, 11, 14, 16}, 8, YELLOW, ">"))
        {
        case 0:
            to_exit = true;
            isInGame = true;
            net_usage = false;
            break;
        case 1:
            to_exit = true;
            isInGame = true;
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
            isRunning = false;
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
        system("cls");
        draw(10, 12, GRAY, "Corpse mode");
        draw(10, 13, GRAY, " Enable");
        draw(10, 14, GRAY, " Disable");
        draw(10, 17, GRAY, "Open dev codes");
        draw(10, 19, GRAY, "Players");
        draw(10, 20, GRAY, " 2");
        draw(10, 21, GRAY, " 4");

        draw(10, 23, GRAY, "Back");

        // Choose
        switch(choosing({13, 14, 17, 20, 21, 23}, 8, YELLOW, ">"))
        {
        case 0:
            corpseMode = true;
            break;
        case 1:
            corpseMode = false;
            break;
        case 2:
            _debugCharacterCast();
            break;
        case 3:
            snakes_total = 2;
            break;
        case 4:
            snakes_total = 4;
            break;
        case 5:
            to_exit = true;
            break;
        }
    }
}
