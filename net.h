#ifndef NET_H
#define NET_H

#include <vector>
#include <string>
#include <fstream>

#include "lobby.h"
#include "engine.h"

class Net
{
public:
    void writeState(int player_number, std::vector<std::pair<short,short>>* outing);
    void voidState(int player_number);

    bool wasUpdated(int player_number, int previous_n);
    std::pair<short,short> readState(int player_number, short offset);

    bool synchSettings(Lobby* obj);

    short net_synch_delay = 500;
    int player_snake_number = -1;
private:
    std::ifstream input;
    std::ofstream output;

    static std::string getFileName(int player_number);
    static std::string getFileName(const std::string& str);
};

#endif // NET_H
