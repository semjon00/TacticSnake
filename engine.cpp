#include "engine.h"

#include <windows.h>
#include <stdio.h>

COORD coord;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Change draw-from cell
void gotoXY(short x, short y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Changing color for drawing
void setColor(int c)
{
    SetConsoleTextAttribute(hConsole, c);
}

void pause(int ms)
{
    // Pauses code executing
    Sleep(ms);
}

void cls()
{
    system("cls");
}

void draw(short x, short y, int color, const std::string& outing)
{
    gotoXY(x, y);
    setColor(color);
    std::cout << outing;
}

void drawFrame(short x, short y, short dx, short dy, int color, char base)
{
    setColor(color);

    for(int i=1; i<dy+1; i++)
    {
        gotoXY(x, i+y);
        std::cout << base;
        gotoXY(x+dx+1, i+y);
        std::cout << base;
    }
    gotoXY(x,y);
    for(int i=0; i<dx+2; i++)
        std::cout << base;
    gotoXY(x,y+dy+1);
    for(int i=0; i<dx+2; i++)
        std::cout << base;
}

void playerBarUpdate(short length, short player_number, bool meIndicator)
{
    // Me indicator
    setColor(DARKGRAY);
    gotoXY(18,3+3*7+2);
    std::cout << (meIndicator ? u8"\u2666" : u8" ");

    // Actual bar
    setColor((player_number+1)*34);
    for (int i=0; i<length; i++)
    {
        std::cout << (i==0 && meIndicator ? static_cast<char>(257) : ' ');
    }

    // Leftovers remove
    setColor(BLACK);
    for (int i=0; i<3-length; i++)
        std::cout << ' ';
}


short choosing(std::vector<short> Y, short x, int color, const std::string& base)
{
    int pointing_to=0;

    while (true)
    {
        draw(x,Y[pointing_to], YELLOW, base);
        char c = normalized_getch();
        draw(x,Y[pointing_to], YELLOW, " ");
        switch (c)
        {
        case 'w':
            pointing_to=(pointing_to-1+Y.size())%Y.size();
            break;
        case 's':
            pointing_to=(pointing_to+1)%Y.size();
            break;
        case 'd':
            return pointing_to;
            break;
        }
    }
}

void toggle(int *variable, int min_val, int max_val)
{
    if ((*variable) == max_val)
    {
        (*variable) = min_val;
    }
    else
    {
        (*variable)++;
    }
}


void _debugCharacterCast()
{
    setColor(GRAY);
    gotoXY(0,0);
    cls();

    // Drawing symbols
    for(int i=176; i<=287; i++)
    {
        if (i==255||i==256||i==263||i==264||i==265||i==266||(i>=224 && i<=241))
            continue;
        std::cout << i << ' ' << static_cast<char>(i) << ' ';
    }
    std::cout << "\n\n";

    // Drawing colors
    for(int i=0; i<16; i++)
    {
        setColor(i);
        std::cout << i << ' ';
    }

    unsigned char c;
    do {
        c = _getch();
        std::cout << (int)c << ' ';
    } while (c != 'q');

}

void disableBlinking()
{
    CONSOLE_CURSOR_INFO CursoInfo;
    CursoInfo.dwSize = 1;
    CursoInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &CursoInfo);
}

void flushGetch()
{
    while (kbhit())
    {
        _getch();
        // result gets discarded
    }
}

char normalized_getch()
{
    unsigned char c = _getch();
    if (c==224)
        c = _getch();

    // Arrow keys
    if (c==72)
        c = 119; // up
    if (c==75)
        c =  97; // left
    if (c==80)
        c = 115; // down
    if (c==77)
        c = 100; // right
    if (c==39)
        c = 'q'; // action

    // Cyrilic
    if (c==230)
        c = 119; // key-up
    if (c==228)
        c =  97; // key-left
    if (c==235)
        c = 115; // key-down
    if (c==162)
        c = 100; // key-right
    if (c == 92)
        c = 'q'; // action

    return c;
}
