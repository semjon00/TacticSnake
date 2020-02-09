#ifndef TACTICSNAKE_CLIENT_H
#define TACTICSNAKE_CLIENT_H

#include <string>
#include <thread>
#include "Server.h"
#include "GameSettings.h"

class Client {
    bool is_running = true;
    GameSettings settings;

public:
    Client(std::string str);
    void sendRoomConnect();
    void sendMadeTurn(int deltax, int deltay);
    void sendMessage(int str);

    void pingThread();
    void sendPing();

    void listenerThread();
    void processNotifyTurn(int snakei, int absx, int absy, int nextsnakei);
    void processNotifyMessage(int id, int msg);
    void processNotifyLose(int snakei);
    void processNotifyWin(int snakei);
    void processRequestTurn(int snakei);
    void processPing();
};


#endif //TACTICSNAKE_CLIENT_H
