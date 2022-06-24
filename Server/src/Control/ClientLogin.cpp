#include "../../includes/Control/ClientLogin.h"
#include "../../includes/defs.h"
#include "../../includes/Model/Game.h"
#include "../../includes/Model/Player.h"

#define CREATE_GAME 1
#define JOIN_GAME 2
#define LIST_GAMES 3
#define SUCCESS 0
#define ERROR 1

ClientLogin::ClientLogin(Game& game1,Socket& peer, YAMLReader& reader1,
                         NonBlockingQueue<NewConnection*>& new_connections)
        : is_running(false),
          peer(std::move(peer)),
          protocol(),
          reader(reader1),
          new_connections(new_connections),
          game(game1) {}

/*
 * El cliente me enviara
 *  1° Nombre del jugador
 *  2° Crear, unirse o listar partidas.
 */
void ClientLogin::run() {
    is_running = true;
    try {
        std::string name;
        uint16_t len_name = protocol.recvCommand(peer);
        name = protocol.recvName(peer, len_name);
        std::cout << "Cliente logeado: " << name << std::endl;
        uint16_t command = protocol.recvCommand(peer); // este comando puede ser 1 2 o 3
        execute(command, name); // si devuelve 0 es porque el cliente ya se unio a una partida o la creo
    } catch (const std::exception& e) {
        try {
            peer.shutdown();
        } catch (const Exception& e) {
            fprintf(stderr, "[ClientLogin]: Error apagando el socket.\n");
        }
        peer.close();
        fprintf(stderr, "[ClientLogin]: %s\n", e.what());
    } catch (...) {
        try {
            peer.shutdown();
        } catch (const Exception& e) {
            fprintf(stderr, "[ClientLogin]: Error apagando el peer.\n");
        }
        peer.close();
        fprintf(stderr, "[ClientLogin]: Error en el run.\n");
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
            fprintf(stderr, "[ClientLogin]: Error en el stop.\n");
        }
        peer.close();
    }
}

int ClientLogin::execute(uint16_t command, std::string name_player) {
    /*
     * Si el comando recibido es crear entonces:
     *  1° Recv Nombre de la partida
     *  2° Recv Jugadores requeridos
     *  3° Recv Mapa en el que se jugara
     *  4° Envio respuesta si se pudo crear o no
     */
    if (command == CREATE_GAME) {
        std::string name_game;
        uint16_t len_name = protocol.recvCommand(peer);
        name_game = protocol.recvName(peer, len_name);
        uint16_t map_id = protocol.recvCommand(peer);
        uint16_t resp = game.createGame(map_id, name_game);
        protocol.sendResponse(peer, resp);
        if (resp == SUCCESS) {
            new_connections.push(new NewConnection(peer, name_player, name_game, map_id));
            return SUCCESS;
        }
    }
    /*
     * Si el comando es join entonces:
     *  1° Le pido el nombre a la partida que desea unirse
     *  2° Envio la respuesta si se pudo unir o no
     */
    else if (command == JOIN_GAME) {
        std::cout << "El jugador se unira una partida existente" << std::endl;
        std::string name_game;
        uint16_t len_name = protocol.recvCommand(peer);
        name_game = protocol.recvName(peer, len_name);
        uint16_t resp = game.acceptPlayer(name_game);
        Id map_id = game.getMapId(name_game);
        protocol.sendResponse(peer, resp);
        if (resp == SUCCESS) {
            new_connections.push(new NewConnection(peer, name_player, name_game, map_id));
            return SUCCESS;
        }
    }
    /*
     * Envio la lista de partidas actuales
     */
    else if (command == LIST_GAMES) {
        std::cout << "El jugador desea listar las partidas" << std::endl;
        protocol.sendGameList(peer, game.listGames());
        return 1;
    }
    return 1;
}

ClientLogin::~ClientLogin() = default;
