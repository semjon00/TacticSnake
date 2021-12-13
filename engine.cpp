#include "engine.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <ctime>

#ifdef _WIN32
#include <cstdlib>
#include <windows.h>
#include <conio.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
void initInterface()
{
    // Set width and height
    system("MODE 30,30");

    // Disable blinking
    CONSOLE_CURSOR_INFO CursoInfo;
    CursoInfo.dwSize = 1;
    CursoInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &CursoInfo);

    // ???
    SetConsoleOutputCP(65001);
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

// Change draw-from cell
COORD coord;
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

// Pauses code executing
void pause(int ms)
{
    Sleep(ms);
}

void title(const std::string& title)
{
    system(("title " + title).c_str());
}

void cls()
{
    setColor(BLACK);
    system("cls");
}

bool keypressBuffered()
{
    return kbhit();
}

void discardKeypress()
{
    _getch();
}

unsigned char popKeypress()
{
    return _getch();
}
#endif
#ifdef __linux__
#include <unistd.h>
#include <termios.h>

void initInterface() {
    // Enable one-keypress reads
    system("stty raw");

    // Set width and height
    std::cout << '\033' << "[8;50;100t";
}

void gotoXY(short x, short y) {
    std::cout << "\033" << "[" << y << ";" << x << "H";
}

void setColor(int c) {
    int background = c / 16;
    int foreground = c % 16;

    int ans0 = -1;
    int ans1 = -1;

    for (auto& cf : {background, foreground}) {
        int linux_color = -1;
        if (cf == BLACK) linux_color = 30;
        if (cf == DARKRED) linux_color = 31;
        if (cf == DARKGREEN) linux_color = 32;
        if (cf == DARKYELLOW) linux_color = 33;
        if (cf == DARKBLUE) linux_color = 34;
        if (cf == DARKMAGENTA) linux_color = 35;
        if (cf == DARKCYAN) linux_color = 36;
        if (cf == GRAY) linux_color = 37;

        if (cf == DARKGRAY) linux_color = 90;
        if (cf == RED) linux_color = 91;
        if (cf == GREEN) linux_color = 92;
        if (cf == YELLOW) linux_color = 93;
        if (cf == BLUE) linux_color = 94;
        if (cf == MAGENTA) linux_color = 95;
        if (cf == CYAN) linux_color = 96;
        if (cf == WHITE) linux_color = 97;

        if (ans0 == -1) ans0 = linux_color + 10;
        else if (ans1 == -1) ans1 = linux_color;
    }

    std::cout << "\033[" << ans0 << ";" << ans1 << "m";
}

void pause(int ms) {
    struct timespec rem{};
    struct timespec req= {
            (int)(ms / 1000),
            (ms % 1000) * 1000000
    };

    nanosleep(&req , &rem);
}

void title(const std::string& title) {
    std::cout << "\033]30;" << title << "\007";
}

void cls() {
    setColor(BLACK);
    std::cout << "\033[2J\033[1;1H";
}

bool keypressBuffered() {
    return false; // TODO: fix
}

void discardKeypress() {
    // TODO: fix
}

unsigned char popKeypress() {
    setColor(16*BLACK+BLACK);
    gotoXY(30,30);
    return getchar();
}
#endif

void draw(short x, short y, int color, const std::string& outing)
{
    gotoXY(x, y);
    setColor(color);
    std::cout << outing;
    std::flush(std::cout);
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
    return choosing(Y, x, color, base, 0);
}

short choosing(std::vector<short> Y, short x, int color, const std::string& base, int pointing_to)
{
    while (true)
    {
        draw(x,Y[pointing_to], YELLOW, base);
        unsigned char c = waitKey();
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
        case 'q':
            return pointing_to;
            break;
        }
    }
}

void toggle(int &variable, int min_val, int max_val)
{
    variable++;
    if (variable == max_val + 1)
        variable = min_val;
}

void flushGetch()
{
    while (keypressBuffered())
    {
        discardKeypress();
    }
}

// TODO: Make it return enum element
unsigned char waitKey()
{
    unsigned char c = popKeypress();
    if (c==224)
        c = popKeypress();

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

unsigned int hash(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
