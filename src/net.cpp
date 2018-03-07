#include "net.h"

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
    output << 0;
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

std::string Net::getFileName(int player_number)
{
    return "ts" + std::to_string(player_number) + ".dat.txt";
}
