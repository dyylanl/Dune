#include "../../includes/Control/ClientLogin.h"
#include "../../includes/defs.h"

ClientLogin::ClientLogin(Socket& peer, YAMLReader& reader1,
                         NonBlockingQueue<NewConnection*>& new_connections)
        : is_running(false),
          peer(std::move(peer)),
          protocol(),
          reader(reader1),
          new_connections(new_connections) {}

void ClientLogin::run() {
    is_running = true;
    try {
        fprintf(stderr, "[ClientLogin]: Nuevo jugador en el lobby.\n");
        new_connections.push(new NewConnection(peer));
    } catch (const std::exception& e) {
        try {
            peer.shutdown();
        } catch (const Exception& e) {
            fprintf(stderr, "Warning: error while shutting-down client_login.");
        }
        peer.close();
        fprintf(stderr, "%s\n", e.what());
    } catch (...) {
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

ClientLogin::~ClientLogin() = default;
