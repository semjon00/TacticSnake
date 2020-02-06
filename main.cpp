#define _WIN32_WINNT 0x0500
#include "engine.h"
#include "ui.h"
#include "Game.h"
#include <windows.h>

int main()
{
    AllocConsole();
    srand(time(nullptr));
    system("MODE 30,30");
    disableBlinking();
    SetConsoleOutputCP(65001);
    UI::fancyTitle();
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    GameSettings settings;

    while(true)
    {
        int picked = UI::mainScreen();
        if (picked == 0) {
            // NEW GAME
            Game a = Game(settings);

        } else if (picked == 1) {
            // ASK NET

            // IF OK START GAME
        } else if (picked == 2) {
            UI::settingsScreen(settings);
        } else if (picked == 3) {
            // Exiting game
            draw(10,18,RED*16+GREEN,"GOODBYE!");
            Sleep(1000);
            setColor(0);
            gotoXY(15,18);
            break;
        }
    }
}
