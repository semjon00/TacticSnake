#include "ui.h"

#include "engine.h"
#include "version.h"

void UI::fancyTitle()
{
    // Header with easter egg
    if (rand()%50 != 0)
        system("title Tactic Snake!");
    else if (rand()%2 == 0)
        system("title Tactic Sanek!");
    else
        system("title tic tac Snake!");
}

int UI::mainScreen()
{
    setColor(BLACK);
    cls();

    // TODO: Make change colors using thread
    const std::string logoStr = u8"   ===  =   == === =  ==\n"
                                  "    =  === =    =  = =  \n"
                                  "    = =   = ==  =  =  ==\n"
                                  "      ╔╕  ╓┐ ╥ ╔═╗ ╥ ╥ ╓──\n"
                                  "      ╚═╗ ║└┐║ ╟─╢ ║╔╝ ║  \n"
                                  "      ╓ ║ ║ └╢ ║ ║ ╠╩╗ ╟──\n"
                                  "      ╚═╝ ╨  ╨ ╨ ╨ ╨ ╨ ╨──\n";
    draw(0, 1, GREEN, logoStr);

    // Screen options
    draw(10,10,GRAY,"Hot seat");
    draw(10,11,GRAY,"Game rules");
    draw(10,13,GRAY,"Online match");
    draw(10,15,GRAY,"Appearance");
    draw(10,16,GRAY,"Exit");
    draw(0, 29, Version::BUILD % 7 + 1, Version::STRING);

    return choosing({10, 11, 13, 15, 16}, 8, YELLOW, ">");
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


void UI::wrongBuildScreen(const std::string& serverVersion)
{
    cls();

    draw(4, 10, RED, u8"\u2593Builds do not match!\u2593");
    draw(2, 12, YELLOW, "It looks like you are using   an incompatible version...");
    draw(2, 15, GRAY, "Your version is  " + Version::STRING);
    draw(2, 16, GRAY, "But server uses  " + serverVersion);
    draw(2, 18, GREEN, "Please obtain the most");
    draw(2, 19, GREEN, "recent build from GitHub.");

    _getch();
}

std::string UI::getOnlineString(std::string str)
{
    cls();
    draw(1, 2, BLUE, "Please input server address   and room.");
    drawFrame(1, 5, 25, 1, DARKCYAN*16+DARKRED, '.');
    int strcolor = GRAY;

    const std::string SERVER = "SERVER";
    const int SERVERCOLOR = WHITE*16 + DARKRED;

    bool redraw = true;
    while (true)
    {
        if (str == SERVER && strcolor != SERVERCOLOR)
        {
            redraw = true;
            strcolor = SERVERCOLOR;
        }
        if (str != SERVER && strcolor == SERVERCOLOR)
        {
            redraw = true;
            strcolor = GRAY;
        }

        flushGetch();
        if (redraw)
        {
            redraw = !redraw;
            draw(2, 6, strcolor, str);
        }

        char c = waitKey();
        switch (c)
        {
            case '\b': // Backspace
                if (!str.empty())
                {
                    str.pop_back();
                    draw(1+str.size()+1, 6, 0, " ");
                }
                break;
            case '\033': // Esc
                return std::string();
            case '\r': // Enter
                return str;
            default:
                if (c >= 32 && c <= 122 && str.size() < 25)
                {
                    str.push_back(c);
                    draw(1+str.size(), 6, 7, std::string(1,c));
                }
                break;
        }
    }
}
