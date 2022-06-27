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
        int resp = 1;
        while (is_running && resp == ERROR) {
            uint16_t command = protocol.recvCommand(peer); // este comando puede ser 1 2 o 3
            resp = execute(command, name); // si devuelve 0 es porque el cliente ya se unio a una partida o la crea si devuelve 1 hay q volver a recibir el comando que indique
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

uint16_t ClientLogin::execute(uint16_t command, std::string name_player) {
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
        uint16_t map_id = protocol.recvCommand(peer); // recibo el mapa que eligio para crear la partida
        uint16_t resp_create_game = game.createGame(map_id, name_game); // pido al game que cree esa partida
        if (resp_create_game == SUCCESS) { // si la respuesta es 0 entonces el game me creo la partida
            game.acceptPlayer(peer, name_player, name_game, map_id); // si la partida se creo entonces le digo al game que me acepte este player
            is_running = false;
            return SUCCESS;
        } else {
            protocol.sendCreateGameInvalid(peer);
            return ERROR;
        }
    }
    /*
     * Si el comando es join entonces:
     *  1° Le pido el nombre a la partida que desea unirse
     *  2° Envio la respuesta si se pudo unir o no
     */
    else if (command == JOIN_GAME) {
        std::string name_game;
        //uint16_t len_name = protocol.recvCommand(peer);
        name_game = protocol.recvName(peer/*, len_name*/);
        Id map_id = game.getMapId(name_game);
        game.acceptPlayer(peer, name_player, name_game, map_id);
        is_running = false;
        return SUCCESS;
    }
    /*
     * Envio la lista de partidas actuales
     */
    else if (command == LIST_GAMES) {
        protocol.sendGameList(peer, game.listGames());
        return ERROR;
    }
    return ERROR;
}

ClientLogin::~ClientLogin() = default;
