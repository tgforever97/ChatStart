//
// Created by wang on 2020/3/26.
//
#include "include/Server.h"
#include "include/Utils.h"
#include <thread>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::thread;
using std::mem_fn;

Server::Server(){
    listener = 0;
    clients_word = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
}

void Server::init() {

    cout << "********server init********" << endl;

    if((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("sock init error");
        printf("%s\n", strerror(errno));
        exit(-1);
    }


    if(bind(listener, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("server bind error");
        printf("%s\n", strerror(errno));
        exit(-1);
    }

    if((listen(listener, 5)) < 0){
        perror("server listen error");
        printf("%s\n", strerror(errno));
        exit(-1);
    }

    cout << "********server listening on " << SERVER_IP << ":" << SERVER_PORT << "********" << endl;
}

void Server::close_connect() {
    close(listener);
}

void Server::start_work() {
    while(1){
        int conn = 0;
        char recvBuff[Max_Buffer];
        sockaddr_in client_addr = {};
        socklen_t socket_addr_len = sizeof(sockaddr_in);
        conn = accept(listener, (struct sockaddr*)&client_addr, &socket_addr_len);
        if(conn < 0) {
            perror("server accept error");
            printf("%s\n", strerror(errno));
            break;
        }
        int len = recv(conn, recvBuff, Max_Buffer-1, 0);
        if(len < 0){
            perror("server receive error");
            printf("%s\n", strerror(errno));
            break;
        }else{
            recvBuff[len] = '\0';
//            cout << "recv:" << recvBuff << endl;
            string recv_string = ch_string(recvBuff);
            auto recv_vector = split(recv_string, ';');
            if(recv_vector.size() == 3){
                printf("%s  send  %s   to   %s\n", recv_vector[1].c_str(), recv_vector[2].c_str(), recv_vector[0].c_str());
                auto it = clients_word.find(recv_vector[0]);
                if(it != clients_word.end()){
                    it->second = it->second + "," + recv_vector[2];
                } else{
                    clients_word.insert({recv_vector[0], recv_vector[1] + ":" + recv_vector[2]});
                }
            }
            if(clients_word.empty()){
                send(conn, NOMESSAGE, sizeof(NOMESSAGE), 0);
            }else{
                bool sendMessage = false;
                for(const auto& word : clients_word){
                    if(recv_vector[1].find(word.first) != string::npos){
                        printf("word = %s    %s\n", word.first.c_str(), word.second.c_str());
                        if(send(conn, word.second.c_str(), word.second.size(), 0) < 0){
                            cout << "send error, and chat is over" << endl;
                        }
                        sendMessage = true;
                        break;
                    }
                }
                if(sendMessage){
                    clients_word.erase(recv_vector[1]);
                } else{
                    send(conn, NOMESSAGE, sizeof(NOMESSAGE), 0);
                }
            }
        }
    }
    close_connect();
}

void Server::start_master() {
    thread t_1(mem_fn(&Server::start_work), std::ref(*this));
//    thread t_2(mem_fn(&Server::start_work), std::ref(*this));
    t_1.join();
//    t_2.join();
}

