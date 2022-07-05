#include "../../includes/Control/ClientConnection.h"

void ClientConnection::_finishThread() {
    std::unique_lock<std::mutex> l(m);
    if ((++finished_threads) == 2) {
        finished_connections.push(new InstanceId(id));
    }
}

void ClientConnection::_freeNotifications() {
    responses.close();
    Response* notification = NULL;
    while ((notification = responses.pop())) {
        delete notification;
    }
}

void ClientConnection::_sender() {
    try {
        Response* notification = nullptr;
        bool socket_valid = true;
        while ((notification = responses.pop())) {
            fprintf(stderr, "CLIENTE %i: Sender popeo una respuesta.\n", id);
            socket_valid = notification->send(this->id, peer);
            delete notification;
            if (!socket_valid) {
                break;
            }
        }
    } catch (const std::exception& e) {
        stop();
        fprintf(stderr, "[ClientConnection]: Error en el hilo sender: %s\n", e.what());
    } catch (...) {
        stop();
        fprintf(stderr, "[ClientConnection]: Error desconocido.\n");
    }
    _finishThread(); // TODO DESCOMENTAR ESTO
}

void ClientConnection::_receiver() {
    try {
        uint8_t opcode;
        while ((opcode = protocol.recvOneByte(peer))) {
            if (opcode != 0) {
                _receiveCommand(opcode);
            } else {
                throw Exception("[CLIENT %i] Se recibe opcode invalido.\n",id);
            }
        }
    } catch (const std::exception& e) {
        stop();
        fprintf(stderr, "[ClientConnection] Error en el hilo _receiver %s\n", e.what());
    } catch (...) {
        stop();
        fprintf(stderr, "[ClientConnection] Error desconocido.\n");
    }
    this->responses.close();
    _finishThread();
}

void ClientConnection::_receiveCommand(uint8_t opcode) {
    try {
        std::cout << "Ejecutando comando con opcode: " << std::to_string(opcode) << std::endl;
        Command* cmd = CommandFactory::newCommand(id, opcode, peer);
        commands.push(cmd);
    } catch (const UnknownCommandException& e) {
        Response* reply_error = new Response(INVALID_COMMAND, e.what());
        this->responses.push(reply_error);
    }
}

ClientConnection::ClientConnection(
        const InstanceId id, Socket peer,
        NonBlockingQueue<InstanceId*>& finished_connections,
        NonBlockingQueue<Command*>& commands)
        : id(id),
          peer(std::move(peer)),
          finished_connections(finished_connections),
          finished_threads(0),
          commands(commands) {}

void ClientConnection::start() {
    sender = std::thread(&ClientConnection::_receiver, this);
    receiver = std::thread(&ClientConnection::_sender, this);
}

void ClientConnection::push(Response* notification) {
    responses.push(notification);
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
        //fprintf(stderr, "CLIENTE %i: Error en el join: %s.\n", id, e.what());
    }
}

void ClientConnection::stop() {
    responses.close();
    try {
        peer.shutdown();
    } catch (const Exception& e) {
        fprintf(stderr, "CLIENTE %i: Error apagando en el stop: %s.\n", id, e.what());
    }
}

ClientConnection::~ClientConnection() {
    _freeNotifications();
}

void ClientConnection::sendInitGame(std::vector<std::vector<char>>& map) {
    try {
        protocol.sendInitGame(peer);
        protocol.sendMap(peer, map);
    } catch (const Exception &e) {
        std::cout << "Error enviando el mapa" << std::endl;
    }
}

void ClientConnection::sendBuildings(std::vector<BuildingDTO> buildings) {
    
    try {
        protocol.sendBuildings(peer, buildings);
    } catch (const Exception &e) {
        std::cout << "Error enviando construcciones." << std::endl;
    }
}

void ClientConnection::sendUnits(std::vector<UnitDTO> units) {
    try {
        protocol.sendUnits(peer, units);
    } catch (const Exception &e) {
        std::cout << "Error enviando unidades." << std::endl;
    }
}

void ClientConnection::sendEstablishConnection() {
    protocol.sendEstablishConnection(peer);
}