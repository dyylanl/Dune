#include "../../includes/Control/ClientLogin.h"
#include "../../includes/Model/Player.h"

#define CREATE_GAME 1
#define JOIN_GAME 2
#define LIST_GAMES 3

#define SUCCESS 0
#define ERROR 1

ClientLogin::ClientLogin(Game& game1, Socket& peer) :
        is_running(true),
        peer(std::move(peer)),
        protocol(),
        game(game1) {}

/*
 * recv len name_player
 * recv namePlayer
 * recv command
 * ejecuto comando
 */
void ClientLogin::run() {
    try {
        std::string name;
        name = protocol.recvName(peer);
        while (is_running) {
            uint8_t command = protocol.recvCommand(peer); // este comando puede ser 1 2 o 3
            execute(command, name); // si devuelve 0 es porque el cliente ya se unio a una partida o la crea si devuelve 1 hay q volver a recibir el comando que indique
        }
    } catch (const std::exception& e) {
        try {
            peer.shutdown();
        } catch (const Exception& e) {
            fprintf(stderr, "[ClientLogin]: Error apagando el socket.\n");
        }
        peer.close();
        fprintf(stderr, "[ClientLogin]: CLOSE %s\n", e.what());
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

void ClientLogin::execute(uint8_t command, std::string name_player) {
    /*
     * Si el comando recibido es crear entonces:
     *  1° Recv Nombre de la partida
     *  2° Send Mapas cargados en el servidor
     *  3° Recv Mapa en el que se jugara
     *  4° Game crea partida
     *  5° Envio respuesta si se pudo crear o no
     *  6° Si se pudo crear game acepta el player
     */
    if (command == CREATE_GAME) {
        std::string name_game;
        name_game = protocol.recvName(peer/*, len_name*/); // recibo el nombre de la partida
        protocol.sendMapsCreated(peer, game.getMapsLoads()); // envio mapas que cargo el server
        uint8_t map_id = protocol.recvOneByte(peer); // recibo el mapa que eligio para crear la partida
        uint16_t flag_create = game.createGameAndAcceptPlayer(map_id, name_game, std::move(peer), name_player); // pido al game que cree esa partida
        if (flag_create == SUCCESS) { // si la respuesta es 0 entonces el game me creo la partida
            is_running = false;
        } else {
            protocol.sendCreateGameInvalid(peer);
            return;
        }
    }
        /*
         * Si el comando es join entonces:
         *  1° Le pido el nombre a la partida que desea unirse
         *  2° Envio la respuesta si se pudo unir o no
         */
    else if (command == JOIN_GAME) {
        std::string name_game = protocol.recvName(peer);
        if (game.acceptNewPlayer(name_game)) {
            game.acceptPlayer(std::move(peer), name_player, name_game);
            is_running = false;
        } else {
            protocol.sendAcceptPlayerInvalid(peer);
            return;
        }
    }
        /*
         * Envio la lista de partidas actuales
         */
    else if (command == LIST_GAMES) {
        protocol.sendGameList(peer, game.listGames());
        return;
    }
}


ClientLogin::~ClientLogin() = default;
