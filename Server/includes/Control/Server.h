#ifndef __SERVER_H__
#define __SERVER_H__

#include <cstdio>
#include <iostream>
#include <string>

class Server {
private:
    std::string port;
    int max_clients_queued;
public:
    Server(std::string port, int max_clients_queued);
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&& other) = delete;
    Server& operator=(Server&& other) = delete;

    void run();
    ~Server();
};


#endif  // __SERVER_H__
