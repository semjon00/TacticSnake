#include <ctime>

#include "engine.h"
#include "ui.h"
#include "Game.h"

int main()
{
    initInterface();
    UI::fancyTitle();

    srand(time(nullptr));

    GameSettings settings;

    while(true)
    {
        flushGetch();
        int picked = UI::mainScreen();
        if (picked == 0) {
            // NEW GAME
            Game a = Game(settings);
        }  else if (picked == 1) {
            UI::settingsScreen(settings);
        } else if (picked == 2) {
            UI::appearanceScreen(settings);
        } else if (picked == 3) {
            // Exiting game
            draw(10,18,RED*16+GREEN,"GOODBYE!");
            pause(1000);
            setColor(BLACK);
            gotoXY(15,18);
            break;
        }
    }
}
