#include <iostream>
#include "../../includes/Control/ClientLogin.h"


//-----------------------------------------------------------------------------
// API Pública

ClientLogin::ClientLogin(SocketWrapper& peer)
        : is_running(false),
          peer(std::move(peer)) {}

void ClientLogin::run() {
    is_running = true;

    try {
        std::cout << "Comenzando ejecucion del cliente..." << std::endl;
    } catch (const std::exception& e) {
        // Error grave
        try {
            peer.shutdown();
        } catch (const Exception& e) {
            fprintf(stderr, "Warning: error while shutting-down client_login.");
        }
        peer.close();
        fprintf(stderr, "%s\n", e.what());
    } catch (...) {
        // Error desconocido
        try {
            peer.shutdown();
        } catch (const Exception& e) {
            fprintf(stderr, "Warning: error while shutting-down client_login.");
        }
        peer.close();
        fprintf(stderr, "Unknown error.\n");
    }

    is_running = false;
}

bool ClientLogin::isRunning() const {
    return is_running;
}

void ClientLogin::stop() {
    if (is_running) {
        // Soy consciente de que en este punto puede existir una RC muuy
        // oportuna, en el caso en que se cierre el server justo en el mismo
        // instante en que un cliente abandone la instancia de login. En este
        // caso, no habrá problema ya que el socket está preparado para hacer el
        // shutdown/close sólo si es necesario. -Mau.
        try {
            peer.shutdown();
        } catch (const Exception& e) {
            fprintf(stderr, "Warning: error while shutting-down client_login.");
        }
        peer.close();
    }
}

ClientLogin::~ClientLogin() {}

//-----------------------------------------------------------------------------
