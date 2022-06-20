#include "../../includes/Control/ClientConnection.h"


void ClientConnection::_finishThread() {
    std::unique_lock<std::mutex> l(m);
    if ((++finished_threads) == 2) {
        finished_connections.push(new InstanceId(id));
    }
}

void ClientConnection::_freeNotifications() {
    notifications.close();
    Command* notification = nullptr;
    while ((notification = notifications.pop())) {
        delete notification;
    }
}

void ClientConnection::_sender() {
    try {
        Protocol protocol;
        Command* notification = nullptr;
        bool socket_valid = true;
        while ((notification = notifications.pop())) {
            // TODO SIEMPRE ENVIA 1 DE RESPUESTA
            socket_valid = protocol.sendResponse(peer, 1);
            delete notification;
            if (!socket_valid) {
                break;
            }
        }
    } catch (const std::exception& e) {
        stop();
        fprintf(stderr, "ClientConnection // _sender: %s\n", e.what());
    } catch (...) {
        stop();
        fprintf(stderr, "ClientConnection // _sender: Unknown error.\n");
    }
    _finishThread();
}

void ClientConnection::_receiver() {
    try {
        uint8_t opcode = 0;
        while (peer.recv(reinterpret_cast<char *>(opcode), sizeof(uint16_t))) {
            if (opcode != 0) {
                _receiveCommand();
            } else {
                break;
            }
        }
    } catch (const std::exception& e) {
        stop();
        fprintf(stderr, "ClientConnection::_receiver: %s\n", e.what());
    } catch (...) {
        // Error desconocido
        stop();
        fprintf(stderr, "ClientConnection::_receiver: Unknown error.\n");
    }
    this->notifications.close();
    _finishThread();
}

void ClientConnection::_receiveCommand() {
    uint8_t opcode_cmd = 0;
    peer.recv(reinterpret_cast<char *>(opcode_cmd), sizeof(uint16_t));
    try {
        Command* cmd = CommandFactory::newCommand(id, opcode_cmd, peer);
        commands.push(cmd);
    } catch (const UnknownCommandException& e) {
    }
}

ClientConnection::ClientConnection(
        const InstanceId id, const Id map, Socket& peer,
        NonBlockingQueue<InstanceId*>& finished_connections,
        NonBlockingQueue<Command*>& commands)
        : id(id),
          map(map),
          peer(std::move(peer)),
          finished_connections(finished_connections),
          finished_threads(0),
          commands(commands) {}

void ClientConnection::start() {
    std::cout << "Iniciando hilos sender/receiver del cliente" << std::endl;
    sender = std::thread(&ClientConnection::_receiver, this);
    receiver = std::thread(&ClientConnection::_sender, this);
}

void ClientConnection::push(Command* notification) {
    notifications.push(notification);
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
        fprintf(stderr, "CLIENTE %i: error in socket::shutdown. Aborting.\n",
                id);
    }
}

void ClientConnection::changeMap(Id map_id) {
    this->map = map_id;
}

void ClientConnection::stop() {
    notifications.close();
    try {
        peer.shutdown();
    } catch (const Exception& e) {
        fprintf(stderr, "CLIENTE %i: error in socket::shutdown. Aborting.\n",
                id);
    }
}

ClientConnection::~ClientConnection() {
    _freeNotifications();
}
