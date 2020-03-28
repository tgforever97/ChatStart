#include "include/Server.h"

int main() {
    Server server;
    server.init();
//    for(int i = 0; i < Max_Thread; i++){
//        std::thread ts(server.start_work());
//        ts.join();
//    }
    server.start_master();
    return 0;
}
