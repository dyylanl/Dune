#include "../../includes/Control/ClientLogin.h"

//-----------------------------------------------------------------------------
// API Pública

ClientLogin::ClientLogin(Socket& peer, YAMLReader& reader1,
                         NonBlockingQueue<NewConnection*>& new_connections)
        : is_running(false),
          peer(std::move(peer)),
          reader(reader1),
          new_connections(new_connections) {}

void ClientLogin::run() {
    is_running = true;
    try {
        // Comienza la ejecución del clientlogin
        fprintf(stderr, "Inicia la ejecución del clientlogin.\n");
        // Si llegamos acá, el cliente ya se loggeo y podemos transferir
        // el socket con seguridad.
        new_connections.push(new NewConnection(peer));
        // Finaliza la ejecución
        fprintf(stderr, "Finaliza la ejecución del clientlogin.\n");
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
