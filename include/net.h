#ifndef NET_H
#define NET_H

#include <vector>
#include <string>
#include <fstream>
#include <conio.h> /* ??? */

class Net
{
public:
    void writeState(int player_number, std::vector<std::pair<short,short>>* outing);
    void voidState(int player_number);
    bool wasUpdated(int player_number, int previous_n);
    std::pair<short,short> readState(int player_number, short offset);

    std::ifstream input;
    std::ofstream output;
private:
    std::string getFileName(int player_number);
};

#endif // NET_H
