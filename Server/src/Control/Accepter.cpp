#include "../../includes/Control/Accepter.h"
#include "../../../Common/includes/Exceptions/LibError.h"

#define MAX_CLIENTS_QUEUED 10

// --------- METODOS PRIVADOS --------- //
void Accepter::_acceptClient(Game &game) {
    Socket peer = socket.accept();
    std::cout << "[ACCEPTER]: Cliente aceptado.\n";
    if (keep_accepting) {
        auto client = new ClientLogin(peer, game);
        client_logins.emplace_back(client);
        client->start();
    }
}

void Accepter::_joinClientLogins() {
    for (auto client = client_logins.begin(); client != client_logins.end();) {
        if (!((*client)->isRunning())) {
            (*client)->join();
            delete (*client);
            client = client_logins.erase(client);
        } else {
            client++;
        }
    }
}

void Accepter::_joinLogins() {
    for (auto client = client_logins.begin(); client != client_logins.end();) {
        (*client)->stop();
        (*client)->join();
        delete (*client);
        client = client_logins.erase(client);
    }
}

// --------- METODOS PUBLICOS --------- //

Accepter::Accepter(std::string port)
        : socket(port, MAX_CLIENTS_QUEUED),
          keep_accepting(true) {}

void Accepter:: run() {
    try {
        Game game;
        while (keep_accepting) {
            _acceptClient(game);
            _joinClientLogins();
        }
    } catch (const LibError& e) {
        //fprintf(stderr, "[ACCEPTER]: %s\n", e.what());
    } catch (const std::exception& e) {
        fprintf(stderr, "[ACCEPTER]: %s\n", e.what());
    } catch (...) {
        fprintf(stderr, "[ACCEPTER]: Error desconocido.\n");
    }
    _joinLogins();
}

void Accepter::stop() {
    keep_accepting = false;
    try {
        socket.shutdown(2);
    } catch (const Exception& e) {
        fprintf(stderr,
                "[ACCEPTER]: Error apagando el socket aceptador.\n");
    }
    socket.close();
}

Accepter::~Accepter() {
    /* No hace falta ya que todos los hilos fueron joineados antes de que el ::run
     * termine su ejecucion, pero por las dudas.
     */
    _joinLogins();
}