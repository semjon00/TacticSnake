#include "net.h"

#include "version.h"

void Net::writeState(int player_number, std::vector<std::pair<short,short>>* outing)
{
    std::string filename = getFileName(player_number);
    output.open(filename);
    output << outing->size() << ' ';
    for(unsigned int i=0; i<outing->size(); i++)
    {
        output << (*outing)[i].first << ' ' << (*outing)[i].second << ' ';
    }
    output.close();
}

void Net::voidState(int player_number)
{
    std::string filename = getFileName(player_number);
    output.open(filename);
    output << -1;
    output.close();
}


bool Net::wasUpdated(int player_number, int previous_n)
{
    std::string filename = getFileName(player_number);
    input.open(filename);
    if (!input.good())
    {
        return false;
    }
    int n;
    input >> n;
    input.close();

    return n > previous_n;
}

std::pair<short,short> Net::readState(int player_number, short offset)
{
    std::string filename = getFileName(player_number);
    input.open(filename);
    unsigned int n;
    input >> n;

    std::pair<short,short> inputing;
    for(unsigned int i=0; i<n-offset; i++)
    {
        input >> inputing.first >> inputing.second;
    }
    input.close();

    return inputing;
}


bool Net::synchSettings(Lobby* obj)
{
    std::string filename = getFileName("conf");
    if (wasUpdated(0, -1))
    {
        input.open(filename);
        // Checking for version compability
        int build_number = 0;
        input >> build_number;
        if (Version::BUILD != build_number)
        {
            input.close();
            obj->wrongBuildScreen(build_number);
            return true;
        }

        // Read settings
        int a, b, c, d, e;
        input >> a >> b >> c >> d >> e;
        obj->snakes_total = a;
        obj->corpseMode = b;
        obj->obstalce_mode = (ObstacleMode)c;
        obj->obstacles = d;
        obj->portal_walls = e;
        input.close();
    }
    else
    {
        // Write settings
        output.open(filename);
        output << Version::BUILD << ' ';
        output << (obj->snakes_total) << ' '\
               << (obj->corpseMode) << ' '\
               << (obj->obstalce_mode) << ' '\
               << (obj->obstacles) << ' '\
               << (obj->portal_walls);
        output.close();
    }
    return false;
}


std::string Net::getFileName(int player_number)
{
    return "ts" + std::to_string(player_number) + ".dat.txt";
}

std::string Net::getFileName(const std::string& str)
{
    return "ts" + str + ".dat.txt";
}
