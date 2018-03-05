/* TacticSnake v0.1.0 */

#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

int gamemode;
class GlobalDestructor
{
public:
    ~GlobalDestructor()
    {
        if (gamemode==1)
        {
            ofstream val;
            val.open("savefile.txt");
            val << "0 0 0";
        }
    };
};
GlobalDestructor globalDestructor;

// Change draw-from cell
COORD coord;
void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Changing color for drawing
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void set_color(int c)
{
    SetConsoleTextAttribute(hConsole, c);
}

void pause(int ms)
{
    // Pauses code executing
    Sleep(ms);
}

void draw(int x, int y, int pl, bool is_head)
{
    set_color(pl*34-is_head);
    gotoxy(x*2, y*2);
    cout << "''";
    gotoxy(x*2, y*2+1);
    cout << "__";
}

int main()
{
    // Connecting to "net"
    ifstream sis;
    ofstream val;

    // Choosing gamemode
    cout << "How many screens do you want to have? (1 or 2)\n";
    int c;
    do {
        c = _getch();
    } while (c!=49&&c!=50);
    gamemode = c-49;
    system("cls");

    // LEFT->RIGTH, TOP->DOWN
    // 1=reds, 2=greens
    int board[8][7];

    for (int i=0; i<7; i++)
    {
        for (int u=0; u<8; u++)
            board[u][i] = 0;
    }
    int heads[3][2] = {{},{0,0},{7,6}}; // [NULL/green/red][coords]
    int prev_heads[3][2] = {{0,0},{-1,-1},{-1,-1}};
    board[0][0] = 1;
    board[7][6] = 2;
    for (int i=0; i<8; i++)
    {
        for (int u=0; u<7; u++)
        {
            draw(i, u, board[i][u], 0);
        }
    }
    bool ups[3][2] = {{},{1,1},{1,1}}; //[NULL/green/red][jump/diagonal]

    int gen=0;
    int genc=0;

    int pl = 0;
    if (gamemode==1)
    {
        sis.open("savefile.txt");
        if (sis.is_open())
        {
            sis >> genc;
            if (genc > 0)
                pl = 1;
        }
    }
    while (1)
    {
        pl = pl%2+1;
        set_color(7);
        gotoxy(0,16);
        cout << "Current player:";
        set_color(pl*34);
        cout << "C";
        int c;
        bool done = 0;
        int step = 1;
        int dstep = 0;

        while (!done)
        {
            if (gamemode==1&&(pl==2))
            {
                sis.open("savefile.txt");
                int genc=gen;
                if (sis.is_open())
                    sis >> genc;
                // Waiting for new turn...
                while (genc==gen)
                {
                    Sleep(1000);
                    if (sis.is_open())
                    {
                        sis.clear();
                        sis.seekg(0, ios::beg);
                        sis >> genc;
                    }
                    else
                    {
                        sis.open("savefile.txt");
                    }
                }
                // New turn has been made!
                gen = genc;
                sis >> heads[2][0] >> heads[2][1];

                c = -1;
                done = 1;
            }
            else
            {
                c = _getch();
            }

            // Controls
            if ((c==97)&&(heads[pl][0]-step>=0)&&(heads[pl][1]+dstep<7)&&(board[heads[pl][0]-step][heads[pl][1]+dstep] == 0))
            {
                heads[pl][0] -= step;
                heads[pl][1] += dstep;
                done = 1;
            }
            if ((c==115)&&(heads[pl][1]+step<7)&&(heads[pl][0]+dstep<8)&&(board[heads[pl][0]+dstep][heads[pl][1]+step] == 0))
            {
                heads[pl][1] += step;
                heads[pl][0] += dstep;
                done = 1;
            }
            if ((c==100)&&(heads[pl][0]+step<8)&&(heads[pl][1]-dstep>=0)&&(board[heads[pl][0]+step][heads[pl][1]-dstep] == 0))
            {
                heads[pl][0] += step;
                heads[pl][1] -= dstep;
                done = 1;
            }
            if ((c==119)&&(heads[pl][1]-step>=0)&&(heads[pl][0]-dstep>=0)&&(board[heads[pl][0]-dstep][heads[pl][1]-step] == 0))
            {
                heads[pl][1] -= step;
                heads[pl][0] -= dstep;
                done = 1;
            }

            // Powerups
            if (c==101)
            {
                if ((step==1)&&(ups[pl][0]))
                {
                    step++;
                    ups[pl][0] = 0;
                }
                else if ((step==2)&&(!ups[pl][0]))
                {
                    step--;
                    ups[pl][0] = 1;
                }
                gotoxy(0,17);
                set_color(7*step-7);
                cout << "JUMP";
            }
            if (c==113)
            {
                if ((dstep==0)&&(ups[pl][1]))
                {
                    dstep++;
                    ups[pl][1] = 0;
                }
                else if ((dstep==1)&&(!ups[pl][1]))
                {
                    dstep--;
                    ups[pl][1] = 1;
                }
                gotoxy(5,17);
                set_color(7*dstep);
                cout << "DIAGONAL";
            }
            if (done)
            {
                gotoxy(0,17);
                set_color(0);
                cout << "JUMP DIAGONAL";
                board[heads[pl][0]][heads[pl][1]] = pl;
                if (prev_heads[pl][0]!=-1)
                    draw(prev_heads[pl][0], prev_heads[pl][1], pl, 0);
                prev_heads[pl][0] = heads[pl][0];
                prev_heads[pl][1] = heads[pl][1];
                draw(heads[pl][0], heads[pl][1], pl, 1);

                if ((gamemode==1)&&(pl==1))
                {
                    gen++;
                    val.open("savefile.txt");
                    val << gen << " " << 7-heads[1][0] << " " << 6-heads[1][1];
                    val.close();
                }
            }
        }
    }
}
