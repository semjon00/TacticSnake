#include "ui.h"

#include "engine.h"
#include "version.h"

void UI::fancyTitle()
{
    // Header with easter egg
    if (rand() % 50 != 0)
        title("Tactic Snake!");
    else {
        std::string easterEggStrings[] = {
                "Tactic Sanek!",
                "tic tac Snake!",
                "3+ years in the making!"
        };
        std::string &picked = easterEggStrings[rand() % (sizeof(easterEggStrings)/sizeof(*easterEggStrings))];
        title(picked);
    }
}

int UI::mainScreen()
{
    cls();

    // TODO: Make change colors using thread
    const std::string logoStr = u8"   ===  =   == === =  ==  \r\n"
                                  "    =  === =    =  = =    \r\n"
                                  "    = =   = ==  =  =  ==  \r\n"
                                  "      ╔╕  ╓┐ ╥ ╔═╗ ╥ ╥ ╓──\r\n"
                                  "      ╚═╗ ║└┐║ ╟─╢ ║╔╝ ║  \r\n"
                                  "      ╓ ║ ║ └╢ ║ ║ ╠╩╗ ╟──\r\n"
                                  "      ╚═╝ ╨  ╨ ╨ ╨ ╨ ╨ ╨──\r\n";
    draw(0, 1, GREEN, logoStr);

    // Screen options
    draw(10,10,GRAY,"Hot seat");
    draw(10,11,GRAY,"Game rules");
    draw(10,13,GRAY,"Appearance");
    draw(10,16,GRAY,"Exit");
    draw(0, 29, Version::getVersionColor(), Version::getVersion());

    return choosing({10, 11, 13, 16}, 8, YELLOW, ">");
}

void UI::settingsScreen(GameSettings &changing)
{
    bool to_exit = false;
    int picked = 0;
    while (!to_exit)
    {
        // Screen
        cls();

        draw(7, 11, GRAY, "Players ");
        draw(20, 11, GREEN, std::to_string(changing.snakes_total));

        draw(7, 13, GRAY, "Corpse mode ");
        draw(20, 13, GREEN, changing.corpseMode ? "[--I]" : "[O--]");

        draw(7, 15, GRAY, "Portal walls ");
        draw(20, 15, GREEN, changing.portal_walls ? "[--I]" : "[O--]");

        draw(7, 23, GRAY, "Back");

        // Choose
        picked = choosing({11, 13, 15, 23}, 4, YELLOW, ">", picked);
        switch (picked)
        {
        case 0:
            toggle(changing.snakes_total, 2, 4);
            break;
        case 1:
            changing.corpseMode = !changing.corpseMode;
            break;
        case 2:
            changing.portal_walls = !changing.portal_walls;
            break;
        case 3:
            to_exit = true;
            break;
        }
    }
}

void UI::appearanceScreen(GameSettings &changing)
{
    bool to_exit = false;
    int picked = 0;
    while (!to_exit)
    {
        // Screen
        cls();

        draw(7, 11, GRAY, "Strict color mode ");
        draw(20, 11, GREEN, settings.strict_color_mode ? "[--I]" : "[O--]");

        draw(7, 23, GRAY, "Back");

        // Choose
        picked = choosing({11, 23}, 4, YELLOW, ">", picked);
        switch (picked)
        {
            case 0:
                settings.strict_color_mode = !settings.strict_color_mode;
                break;
            case 1:
                to_exit = true;
                break;
        }
    }
}
