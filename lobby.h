#ifndef LOBBY_H
#define LOBBY_H

enum ObstacleMode
{
    FAIR, RANDOM
};

enum ColorSceme
{
    CLASSIC, DISCO, FANCY
};

class Lobby
{
public:
    Lobby();

    void mainScreen();
    void settingsScreen();
    static void wrongBuildScreen(int build_number);

    bool is_in_game = false;
    bool is_running = true;
    bool net_usage = false;

    short field_width = 8;
    short field_height = 7;

    // Various customization settings
    ColorSceme color_sceme = CLASSIC;

    // Various match-releated settings
    int snakes_total = 2;
    int snakes_in_game = 2;
    int obstacles = 0;
    ObstacleMode obstalce_mode = FAIR;
    bool corpseMode = false;
    bool portal_walls = false;

    // Snake start coordinates
    int spawn_coords[8] = {0, 0, 7, 6, 0, 6, 7, 0};
private:

};

#endif // LOBBY_H
