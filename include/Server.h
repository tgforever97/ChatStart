//
// Created by wang on 2020/3/26.
//

#ifndef CHATSTART_SERVER_H
#define CHATSTART_SERVER_H

#include "Common.h"
#include <map>

using std::vector;
using std::string;
using std::map;

class Server{

public:

    Server();

    void init();

    void close_connect();

    void start_work();

    void start_master();

private:

    int listener;

    struct sockaddr_in server_addr;

    map<string, string> clients_word;

};
#endif //CHATSTART_SERVER_H
