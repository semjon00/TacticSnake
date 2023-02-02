#ifndef UI_H
#define UI_H

#include "GameSettings.h"
#include <string>

struct Settings
{
    bool strict_color_mode = true;
};

class UI
{
public:
    static void fancyTitle();
    static int mainScreen();

    static void settingsScreen(GameSettings &changing);
    static void appearanceScreen(GameSettings &changing);

    // Various customization settings
    inline static Settings settings;

};

#endif // UI_H
