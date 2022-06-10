#ifndef CLIENTLOGIN_H
#define CLIENTLOGIN_H
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <atomic>
#include "../../../Common/includes/Thread.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "../../../Common/includes/Protocol.h"
#include "../Model/Game.h"


class ClientLogin : public Thread {
private:
    std::atomic_bool is_running;
    Socket peer;
    Protocol protocol;
    Game& game;
    /*
     * Ejecuta el comando que envio el Cliente.
     */
    void execute(int command);
    /*
     *  Une el cliente a la partida.
     */
    void executeJoin();
    /*
     * Crea una partida.
     */
    void executeCreate();
    /*
     * Envia la lista de partidas actuales.
     */
    void executeList();

public:
    explicit ClientLogin(Socket& peer, Game &game_r);
    ClientLogin(const ClientLogin&) = delete;
    ClientLogin& operator=(const ClientLogin&) = delete;
    ClientLogin(ClientLogin&& other) = delete;
    ClientLogin& operator=(ClientLogin&& other) = delete;
    void run() override;
    bool isRunning() const;
    /*
     * Stop violento, no importa si el cliente sigue corriendo.
     */
    void stop();
    ~ClientLogin() override;
};


#endif  // CLIENTLOGIN_H