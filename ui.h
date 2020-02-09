#ifndef UI_H
#define UI_H

#include "GameSettings.h"
#include <string>

enum ColorSceme
{
    CLASSIC, DISCO, FANCY
};

struct Settings
{
    bool strict_color_mode = true;
    ColorSceme color_sceme = CLASSIC;
};

class UI
{
public:
    static void fancyTitle();
    static int mainScreen();
    static void settingsScreen(GameSettings &changing);

    static std::string getOnlineString(std::string str);
    static void wrongBuildScreen(const std::string& serverVersion);

    static void appearanceScreen(GameSettings &changing);

    // Various customization settings
    inline static Settings settings;

};

#endif // UI_H
