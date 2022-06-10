#include "../../includes/Control/ClientLogin.h"
#include "../../../Common/includes/Exceptions/LibError.h"

#define JOIN 1
#define LIST 2
#define CREATE 3

void ClientLogin::execute(int command) {
    if (command == JOIN) {
        executeJoin();
    } else if (command == LIST) {
        executeList();
    } else if (command == CREATE) {
        executeCreate();
    } else {
        throw Exception("Invalid command.");
    }
}

void ClientLogin::executeList() {
    std::vector<std::string> list = game.listGames();
    protocol.sendGameList(peer, list);
}

void ClientLogin::executeCreate() {
    int house = 0, req = 0;
    std::string name;
    protocol.recvCreate(peer, house, req, name);
    int resp = game.createGame(house, req, name);
    protocol.sendResponse(peer, resp);
}

void ClientLogin::executeJoin() {
    std::string name;
    protocol.recvJoin(peer, name);
    int resp = game.acceptPlayer(name);
    protocol.sendResponse(peer, resp);
}

// ----------------------------------------------------------------------------------------------------------------

ClientLogin::ClientLogin(Socket& peer, Game &game_r)
        : is_running(true),
          peer(std::move(peer)),
          protocol(),
          game(game_r) {}

void ClientLogin::run() {
    try {
        while (is_running) {
            uint16_t command = protocol.recvCommand(peer);
            if (is_running) {
                execute(command);
            }
        }
    } catch (const LibError& lib_error) {
    } catch (const std::exception& excep) {
        try {
            peer.shutdown(2);
        } catch (const LibError& lib_excep) {
        } catch (const Exception& err) {
            fprintf(stderr,
                    "[ClientLogin]: Error apagando el socket del client.\n");
        }
        //peer.close();
    } catch (...) {
        try {
            peer.shutdown(2);
        } catch (const Exception& err1) {
            fprintf(stderr,
                    "[ClientLogin]: Error apagando el socket del client.\n");
        }
        //peer.close();
        fprintf(stderr,
                "[ClientLogin]: Error desconocido.\n");
    }
    is_running = false;
}

bool ClientLogin::isRunning() const {
    return is_running;
}

void ClientLogin::stop() {
    is_running = false;
    try {
        peer.shutdown(2);
    } catch (const LibError& err2) {
        fprintf(stderr, "[ClientLogin]: %s\n", err2.what());
    } catch (const Exception& err3) {
        fprintf(stderr, "[ClientLogin]: Error apagando el socket.\n");
    }
    peer.close();
}

ClientLogin::~ClientLogin() = default;