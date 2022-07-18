#include "../../includes/Control/ClientConnection.h"
#include "../../includes/Model/DTOs/snapshot.h"

void ClientConnection::_finishThread() {
    std::unique_lock<std::mutex> l(m);
    if ((++finished_threads) == 2) {
        finished_connections.push(new InstanceId(id));
    }
}

void ClientConnection::_freeNotifications() {
    Snapshot* snap = nullptr;
    while ((snap = snapshots.pop())) {
        delete snap;
    }
    Command* cmd = nullptr;
    while ((cmd = commands.pop())) {
        delete cmd;
    }
}

void ClientConnection::_sender() {
    try {
        Snapshot* snap = nullptr;
        while ((snap = snapshots.pop())) {
            int count = (int)(snap->buildings.size() + snap->units.size());
            protocol.sendCountObject(peer, count);
            for (auto &b: snap->buildings) {
                protocol.sendBuild(peer, b);
            }
            for (auto &u: snap->units) {
                protocol.sendUnit(peer, u);
            }
            protocol.sendPlayer(peer, snap->getPlayer(this->id));
            delete snap;
        }
    } catch (const std::exception& e) {
        stop();
    } catch (...) {
        stop();
        fprintf(stderr, "[ClientConnection]: Error desconocido.\n");
    }
   this->snapshots.close();
    _finishThread();
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
        fprintf(stderr, "[ClientConnection] Error en el hilo receiver %s\n", e.what());
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

void ClientConnection::push(std::vector<BuildingDTO> buildings, std::vector<UnitDTO> units, std::vector<PlayerDTO> players) {
    snapshots.push(new Snapshot(buildings,units,players)); //este new Snap es eliminado en cada ciclo del _sender
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
    this->snapshots.close();
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


void ClientConnection::sendEstablishConnection(Position initial_pos) {
    protocol.sendEstablishConnection(peer);
    protocol.sendPosition(peer, initial_pos.getX(),initial_pos.getY());
}