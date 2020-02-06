#ifndef UI_H
#define UI_H

#include "GameSettings.h"
#include <string>

enum ColorSceme
{
    CLASSIC, DISCO, FANCY
};

class UI
{
public:
    static void fancyTitle();
    static int mainScreen();
    static void settingsScreen(GameSettings &changing);
    static void wrongBuildScreen(const std::string& serverVersion);

    // Various customization settings
    static ColorSceme color_sceme;

private:

};

#endif // UI_H
