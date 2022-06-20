#include <iostream>
#include <exception>
#include "../includes/Client.h"
#include "loby/mainwindow.h"
#include <QApplication>
#define EXPECTED_ARGC 3
#define ERROR 1
#define SUCCESS 0

int main(int argc, char** argv){

//codigo para lanzar qt

    QApplication a(argc, argv);
    MainWindow w(nullptr);
    //w.set_parser(parser_texto);
    w.show();
    a.exec();
    Client* cliente = w.get_cliente();
    cliente->launch();


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
