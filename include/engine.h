#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>  /* draw */
#include <vector>
#include <windows.h> /* gotoXY */
#include <conio.h>   /* _getch */
#include <cstdlib> /* pseudographics couting */

#include <cstdlib> /* rand */
#include <ctime> /* for rand initializing */

enum Color
{
    BLACK, DARKBLUE, DARKGREEN, DARKCYAN, DARKRED, DARKMAGENTA, DARKYELLOW,
    GRAY, DARKGRAY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
};

void gotoXY(short x, short y);
void setColor(int c);
void pause(int ms);

void draw(short x, short y, int color, std::string outing);
void drawFrame(short x, short y, short dx, short dy, int color, char base);
void playerBarUpdate(short length, short player_number, bool meIndicator);

short choosing(std::vector<short> Y, short x, int color, std::string base);

void _debugCharacterCast();
void disableBlinking();

void flushGetch();
char normalized_getch();

#endif // ENGINE_H
