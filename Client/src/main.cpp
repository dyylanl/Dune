#include <iostream>
#include <exception>
#include "../includes/Client.h"
#include "loby/mainwindow.h"
#include <QApplication>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char** argv){

    /*QApplication a(argc,argv);
    MainWindow w(nullptr);
    w.show();
    int exit_code = a.exec();
    if(exit_code == 0){
        return ERROR;
    }   
    Client* cliente = w.get_cliente();
    cliente->iniciar();*/

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
    //delete cliente;

    return SUCCESS;
}
