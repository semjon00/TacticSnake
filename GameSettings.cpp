#include "GameSettings.h"

GameSettings::GameSettings()
{
    field_width = 8;
    field_height = 7;
    snakes_total = 2;
    obstacle_pos = std::vector<std::pair<int,int>> ();
    obstalce_mode = FAIR;
    corpseMode = false;
    portal_walls = false;
}
