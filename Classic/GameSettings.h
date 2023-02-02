#ifndef TACTICSNAKE_GAMESETTINGS_H
#define TACTICSNAKE_GAMESETTINGS_H

class GameSettings {
public:
    GameSettings();

    short field_width;
    short field_height;
    int snakes_total;
    bool corpseMode;
    bool portal_walls;
};


#endif //TACTICSNAKE_GAMESETTINGS_H
