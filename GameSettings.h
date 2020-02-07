#ifndef TACTICSNAKE_GAMESETTINGS_H
#define TACTICSNAKE_GAMESETTINGS_H

#include <vector>

enum ObstacleMode
{
    NONE, FAIR, RANDOM
};

class GameSettings {
public:
    GameSettings();

    short field_width;
    short field_height;
    int snakes_total;
    ObstacleMode obstalce_mode;
    bool corpseMode;
    bool portal_walls;


};


#endif //TACTICSNAKE_GAMESETTINGS_H
