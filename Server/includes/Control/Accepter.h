#ifndef ACCEPTER_H
#define ACCEPTER_H
#include <atomic>
#include <list>
#include "../../../Common/includes/Thread.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "ClientLogin.h"

class Accepter : public Thread {
private:
    /*
     * Socket bind
     */
    Socket socket;
    std::atomic_bool keep_accepting;
    /*
     * Contenedor de todos los hilos cliente.
     */
    std::list<ClientLogin*> client_logins;
    /*
     * Acepta una conexion y lanza el hilo cliente.
     */
    void _acceptClient(Game &game);
    /*
     * Limpia los clientes que se desconectaron.
     */
    void _joinClientLogins();
    /*
     * Limpia todos los clientes, conectados o no.
     */
    void _joinLogins();

public:
    explicit Accepter(std::string port);
    Accepter(const Accepter&) = delete;
    Accepter& operator=(const Accepter&) = delete;
    Accepter(Accepter&& other) = delete;
    Accepter& operator=(Accepter&& other) = delete;
    void run() override;
    void stop();
    ~Accepter() override;
};


#endif  // ACCEPTER_H