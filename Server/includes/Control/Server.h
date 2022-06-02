#ifndef __SERVER_H__
#define __SERVER_H__

#include <stdio.h>
#include <iostream>
#include <string>

class Server {
private:

public:
    Server(const std::string& port);
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&& other) = delete;
    Server& operator=(Server&& other) = delete;

    void run();
    ~Server();
};


#endif  // __SERVER_H__
