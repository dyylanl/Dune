#include "../../includes/Control/ClientConnection.h"

void ClientConnection::_finishThread() {
    std::unique_lock<std::mutex> l(m);
    fprintf(stderr, "CLIENTE %i: se llamó a _finishThread.\n", id);
    if ((++finished_threads) == 2) {
        fprintf(stderr,"CLIENTE %i: _finishThread agrega conexión terminada a la cola.\n",id);
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
        fprintf(stderr, "CLIENTE %i: Sender comienza su ejecución.\n", id);
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
        fprintf(stderr, "ClientConnection // _sender: %s\n", e.what());
    } catch (...) {
        stop();
        fprintf(stderr, "ClientConnection // _sender: Unknown error.\n");
    }
    _finishThread(); // TODO DESCOMENTAR ESTO
    fprintf(stderr, "CLIENTE %i: Sender finaliza su ejecución.\n", id);
}

void ClientConnection::_receiver() {
    fprintf(stderr, "CLIENTE %i: Receiver comienza su ejecución.\n", id);
    try {
        uint8_t opcode;
        while ((opcode = protocol.recvOneByte(peer))) {
            fprintf(stderr, "CLIENTE %i: Receiver ejecutando opcode: %i.\n", id,opcode);
            if (opcode != 0) {
                _receiveCommand(opcode);
            } else {
                throw Exception("[CLIENT %i] INVALID OPCODE.\n",id);
            }
        }
    } catch (const std::exception& e) {
        stop();
        fprintf(stderr, "ClientConnection::_receiver: %s\n", e.what());
    } catch (...) {
        stop();
        fprintf(stderr, "ClientConnection::_receiver: Unknown error.\n");
    }
    this->responses.close();
    _finishThread();
    fprintf(stderr, "CLIENTE %i: Receiver finaliza su ejecución.\n", id);
}

void ClientConnection::_receiveCommand(uint8_t opcode) {
    try {
        Command* cmd = CommandFactory::newCommand(id, opcode, peer);
        commands.push(cmd);
    } catch (const UnknownCommandException& e) {
        // Comando desconocido. Envio error.
        Response* reply_error = new Response(INVALID_COMMAND, e.what());
        this->responses.push(reply_error);
    }
}


ClientConnection::ClientConnection(
        const InstanceId id, Socket& peer,
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
        fprintf(stderr, "CLIENTE %i: error in socket::shutdown. Aborting.\n",
                id);
    }
}

void ClientConnection::stop() {
    responses.close();
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



void ClientConnection::sendInitGame(std::vector<std::vector<char>>& map) {
    try {
        protocol.sendInitGame(peer);
        protocol.sendMap(peer, map);
    } catch (const Exception &e) {
        std::cout << "Error enviando el mapa" << std::endl;
    }
}

void ClientConnection::sendInitBuildings(std::vector<BuildingDTO> buildings) {
    try {
        protocol.sendInitBuildings(peer, buildings);
    } catch (const Exception &e) {
        std::cout << "Error enviando el centro de construccion." << std::endl;
    }
}

void ClientConnection::sendEstablishConnection() {
    protocol.sendEstablishConnection(peer);
}
