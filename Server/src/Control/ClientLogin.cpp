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
        std::string name;
        uint16_t len_name = protocol.recvCommand(peer);
        name = protocol.recvName(peer, len_name);
        std::cout << "[ClientLogin]: Se conecto " << name << std::endl;
        uint16_t command = protocol.recvCommand(peer);
        execute(command);
        //new_connections.push(new NewConnection(peer, name, house));
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

void ClientLogin::execute(uint16_t command) {
    if (command == 1) {
        std::cout << "El jugador creara una partida" << std::endl;
    }
    if (command == 2) {
        std::cout << "El jugador se unira una partida existente" << std::endl;
    }
    if (command == 3) {
        std::cout << "El jugador desea listar las partidas" << std::endl;
    }
}

ClientLogin::~ClientLogin() = default;
