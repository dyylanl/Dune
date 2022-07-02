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
        int t = system("sleep 2");
        t++;
        Command* cmd = commands.pop();
        if (cmd != nullptr) {
            std::cout << "Enviando comando llamado por: " << cmd->getCaller() << std::endl;
        }
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
        uint8_t opcode = 0;
        while ((opcode = protocol.recvResponse(peer))) { // este recv se usa para saber si esperamos un comando o un fin de conexion
            if (opcode != 0) { // si el opcode recibido es 0 entonces significa que el cliente cerro la comunicacion
                // lo unico que hace el hilo receiver es pushear a la cola de comandos
                _receiveCommand(opcode);
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
    //_finishThread();
}

void ClientConnection::_receiveCommand(uint8_t opcode) {
    try {
        Command* cmd = CommandFactory::newCommand(id,opcode,peer);
        commands.push(cmd);
    } catch (const Exception& e) {
    }
}

ClientConnection::ClientConnection(
        const InstanceId id, 
        Socket& peer,
        NonBlockingQueue<Command*>& commands1,
        NonBlockingQueue<InstanceId*>& finished_connections)
        : id(id),
          peer(std::move(peer)),
          finished_connections(finished_connections),
          finished_threads(0),
          protocol(),
          commands(commands1)  {}

void ClientConnection::start() {
    // si llegamos hasta aca es porque el jugador se pudo conectar entonces se lo hacemos saber al cliente
    protocol.sendEstablishConnection(peer);
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
        fprintf(stderr, "[ClientConnection]: Ocurrio un error en el ::join del player: %i (id) \n",id);
    }
}

void ClientConnection::stop() {
    //notifications.close();
    try {
        peer.shutdown();
    } catch (const Exception& e) {
        fprintf(stderr, "[ClientConnection]: Error en el ::stop del player (id): %i\n",id);
    }
}

ClientConnection::~ClientConnection() {
    _freeNotifications();
}


void ClientConnection::sendInitGame(std::vector<std::vector<char>>& map) {
    protocol.sendInitGame(peer);
    protocol.sendMap(peer, map);
}

void ClientConnection::sendInitBuildings(std::vector<BuildingDTO> buildings) {
    protocol.sendInitBuildings(peer, buildings);
}