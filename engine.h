#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>

enum Color
{
    BLACK, DARKBLUE, DARKGREEN, DARKCYAN, DARKRED, DARKMAGENTA, DARKYELLOW, GRAY,
    DARKGRAY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
};

void initInterface();

void gotoXY(short x, short y);
void setColor(int c);
void pause(int ms);

void title(const std::string& title);
void cls();

bool keypressBuffered();
void discardKeypress();
int popKeypress();

void draw(short x, short y, int color, const std::string& outing);
void drawFrame(short x, short y, short dx, short dy, int color, char base);
void playerBarUpdate(short length, short player_number, bool meIndicator);

short choosing(std::vector<short> Y, short x, int color, const std::string& base);
short choosing(std::vector<short> Y, short x, int color, const std::string& base, int pointing_to);
void toggle(int &variable, int min_val, int max_val);

void debugCharacterCast();

void flushGetch();
char waitKey();

unsigned int hash(unsigned int x);

#endif // ENGINE_H
