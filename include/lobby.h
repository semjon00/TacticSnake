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

    bool isInGame = false;
    bool isRunning = true;

    bool net_usage = false;

    ColorSceme color_sceme = CLASSIC;

    // Various match-releated settings
    int snakes_total = 2;
    int snakes_in_game = 2;
    int obstacles = 0;
    ObstacleMode obstalce_mode = FAIR;
    bool corpseMode = false;

    // Snake start coordinates
    int spawn_coords[8] = {0, 0, 7, 6, 0, 6, 7, 0};
private:

};

#endif // LOBBY_H
