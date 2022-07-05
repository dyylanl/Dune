#include "../../includes/Control/ClientConnection.h"

void ClientConnection::_finishThread() {
    std::unique_lock<std::mutex> l(m);
    if ((++finished_threads) == 2) {
        finished_connections.push(new InstanceId(id));
    }
}

void ClientConnection::_freeNotifications() {
    buildings.close();
    units.close();
    /*BuildingDTO* buildsDTO = nullptr;
    while ((buildsDTO = buildings.pop())) {
        delete buildsDTO;
    }
    UnitDTO* unitsDTO = nullptr;
    while ((unitsDTO = units.pop())) {
        delete unitsDTO;
    }*/
}

void ClientConnection::_sender() {
    try {
        BuildingDTO* build = nullptr;
        while ((build = buildings.pop())) {
            protocol.sendBuild(peer, *build);
        }
        delete build;
        UnitDTO* unit = nullptr;
        while ((unit = units.pop())) {
            protocol.sendUnit(peer, *unit);
        }
        delete unit;
    } catch (const std::exception& e) {
        stop();
        //fprintf(stderr, "[ClientConnection]: Error en el hilo sender: %s\n", e.what()); ya esta cerrado el socket no se puede hacer un send
    } catch (...) {
        stop();
        fprintf(stderr, "[ClientConnection]: Error desconocido.\n");
    }
    this->buildings.close();
    this->units.close();
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
    _finishThread();
}

void ClientConnection::_receiveCommand(uint8_t opcode) {
    try {
        Command* cmd = CommandFactory::newCommand(id, opcode, peer);
        commands.push(cmd);
    } catch (const UnknownCommandException& e) {
        return;
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

void ClientConnection::pushBuilding(BuildingDTO* building1) {
    buildings.push(building1);
}

void ClientConnection::pushUnit(UnitDTO* unit1) {
    units.push(unit1);
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
        // si el cliente se va el socket se apaga
        //fprintf(stderr, "CLIENTE %i: Error en el join: %s.\n", id, e.what());
    }
}

void ClientConnection::stop() {
    this->buildings.close();
    this->units.close();
    try {
        peer.shutdown();
    } catch (const Exception& e) {
        //fprintf(stderr, "CLIENTE %i: Error apagando en el stop: %s.\n", id, e.what());
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


void ClientConnection::sendEstablishConnection() {
    protocol.sendEstablishConnection(peer);
}