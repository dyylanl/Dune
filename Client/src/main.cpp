#include <iostream>
#include <exception>
#include "../includes/Client.h"

#define ERROR 1
#define SUCCESS 0

int main(int argc, char** argv){
    try {
        Client client;
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
