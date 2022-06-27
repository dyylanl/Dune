#include "../../includes/Control/ClientConnection.h"


void ClientConnection::_finishThread() {
    std::unique_lock<std::mutex> l(m);
    if ((++finished_threads) == 2) {
        finished_connections.push(new InstanceId(id));
    }
}

void ClientConnection::_freeNotifications() {
    /*notifications.close();
    Command* notification = nullptr;
    while ((notification = notifications.pop())) {
        delete notification;
    }*/
}

// hilo sender -- envia respuesta al cliente
// todo: implementar logica de envio de informacion pertinente al player
void ClientConnection::_sender() {
    try {
        //std::cout << "Sender comenzando ejecucion." << std::endl;
        /*Protocol protocol;
        Command* command = nullptr;
        bool socket_valid = true;
        while ((command = notifications.pop())) {
            // aca hay que ejecutar una logica
            // aca se mandaria el snapshot
            socket_valid = protocol.sendResponse(peer, 1);
            delete command;
            if (!socket_valid) {
                break;
            }*/
    } catch (const std::exception& e) {
            stop();
            fprintf(stderr, "[ClientConnection]: %s\n", e.what());
    } catch (...) {
        stop();
        fprintf(stderr, "[ClientConnection]: Ocurrio un error en el hilo sender.\n");
    }
    _finishThread();
}

void ClientConnection::_receiver() {
    try {
        //std::cout << "Receiver comenzando ejecucion..." << std::endl;
        uint8_t opcode = 0;
        while (peer.recv(reinterpret_cast<char *>(opcode), sizeof(uint16_t))) {
            if (opcode != 0) {
                // lo unico que hace el hilo receiver es pushear a la cola de comandos
                _receiveCommand();
            } else {
                break;
            }
        }
    } catch (const std::exception& e) {
        stop();
        fprintf(stderr, "[ClientConnection]: %s\n", e.what());
    } catch (...) {
        stop();
        fprintf(stderr, "[ClientConnection]: Ocurrio un error en el hilo receiver.\n");
    }
    //this->notifications.close();
    _finishThread();
}

void ClientConnection::_receiveCommand() {
    uint8_t opcode_cmd = 0;
    peer.recv(reinterpret_cast<char *>(opcode_cmd), sizeof(uint16_t));
    try {
        std::cout << "Jugador recibio: " << opcode_cmd << std::endl;
        /*Command* cmd = CommandFactory::newCommand(id, opcode_cmd, peer);
        commands.push(cmd);*/
    } catch (const Exception& e) {
    }
}

ClientConnection::ClientConnection(
        const InstanceId id, 
        const Id map_id1,
        Socket& peer,
        NonBlockingQueue<InstanceId*>& finished_connections)
        : id(id),
          map_id(map_id1),
          peer(std::move(peer)),
          finished_connections(finished_connections),
          finished_threads(0),
          protocol()  {}

void ClientConnection::start() {
    // si llegamos hasta aca es porque el jugador se pudo conectar entonces se lo hacemos saber al cliente
    protocol.sendEstablishConnection(peer);
    std::cout << "Envio conexion establecida [9]" << std::endl;
    sender = std::thread(&ClientConnection::_receiver, this);
    receiver = std::thread(&ClientConnection::_sender, this);
}

void ClientConnection::join() {
    if (sender.joinable()) {
        sender.join();
    }

    if (receiver.joinable()) {
        receiver.join();
    }

    try {
        peer.shutdown();
    } catch (const Exception& e) {
        fprintf(stderr, "[ClientConnection]: Ocurrio un erro en el join del player(id): %i \n",id);
    }
}

void ClientConnection::stop() {
    //notifications.close();
    try {
        peer.shutdown();
    } catch (const Exception& e) {
        fprintf(stderr, "[ClientConnection]: Error en el stop del player (id): %i\n",id);
    }
}

ClientConnection::~ClientConnection() {
    _freeNotifications();
}


void ClientConnection::sendInitGame(std::vector<std::vector<char>>& map) {
    protocol.sendInitGame(peer);
    protocol.sendMap(peer, map);
    std::cout << "Envio partida completa [10] y mapa" << std::endl;
}