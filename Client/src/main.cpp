#include <iostream>
#include <exception>
#include "../includes/Client.h"
#include "loby/mainwindow.h"
#include <QApplication>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char** argv){

   std::cout << "empieza" << std::endl;
    QApplication a(argc,argv);
    std::cout << "bug 1" << std::endl;
    MainWindow w(nullptr);
    std::cout << "bug 2" << std::endl;
    w.show();
    std::cout << "bug 3" << std::endl;
    int exit_code = a.exec();
    if(exit_code == 0){
        return ERROR;
    }
    std::cout << "bug 4" << std::endl;    
    Client* cliente = w.get_cliente();
    cliente->iniciar();
    /*
    try {
        Client client;
        client.launch();
    } catch (const std::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        return ERROR;
    } catch (...) {
        fprintf(stderr, "Unknown error.\n");
        return ERROR;
    }*/

    return SUCCESS;
}
