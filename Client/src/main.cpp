#include <iostream>
#include <exception>
#include "../includes/Client.h"
#define EXPECTED_ARGC 3
#define ERROR 1
#define SUCCESS 0

int main(int argc, char** argv){
    if (argc != EXPECTED_ARGC) {
        fprintf(stderr, "Usage: <ip> <port>\n");
        return ERROR;
    }
    std::string ip = argv[1];
    std::string port = argv[2];
    try {
        Client client(ip, port);
        client.launch();
    } catch (const std::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        return ERROR;
    } catch (...) {
        fprintf(stderr, "Unknown error.\n");
        return ERROR;
    }

    return SUCCESS;
}