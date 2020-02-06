#ifndef UI_H
#define UI_H

#include "GameSettings.h"

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
    static void wrongBuildScreen(int build_number);

    // Various customization settings
    static ColorSceme color_sceme;

private:
};

#endif // UI_H
