#ifndef __SERVER_H__
#define __SERVER_H__

#include <cstdio>
#include <iostream>
#include <string>
// --------------------------------------------------- //
#include "YAMLReader.h"
#include "Accepter.h"

class Server {
private:
    YAMLReader reader;
    Accepter accepter;

public:
    explicit Server(const std::string& config_path);
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&& other) = delete;
    Server& operator=(Server&& other) = delete;

    void run();
    ~Server();
};


#endif  // __SERVER_H__
