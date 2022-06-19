#include "../../includes/Control/ClientConnection.h"

void ClientConnection::_finishThread() {
    std::unique_lock<std::mutex> l(m);
    if ((++finished_threads) == 2) {
        finished_connections.push(new InstanceId(this->connection_id));
        join();
    }
    std::cout << "Se llamo al finishThread ahora el contador es: " << finished_threads << std::endl;
}
// todo: implementar clase Comando
void ClientConnection::_sender() {
    try {
        Protocol protocol;
        int* snapshot_send = nullptr;
        bool socket_valid = true;
        // loop del sender: envia tldo crudo asi como viene al cliente (por ahora nomas)
        while ((snapshot_send = this->snapshot.pop())) {
            socket_valid = protocol.sendResponse(peer, *snapshot_send);
            delete snapshot_send;
            if (!socket_valid) {
                break;
            }
        }
    } catch (const std::exception& e) {
        stop();
        fprintf(stderr, "[ClientConnection]|[_sender]: %s\n", e.what());
    } catch (...) {
        stop();
        fprintf(stderr, "\"[ClientConnection]|[_sender]: ERROR");
    }
    _finishThread(); // de esta manera aviso que el hilo sender finaliza
}

void ClientConnection::_receiver() {
    try {
        Protocol protocol;
        uint8_t command_recv;
        while ((command_recv = protocol.recvCommand(peer))) {
            if (command_recv != 0) {
                this->commands.push(reinterpret_cast<int *>(&command_recv)); // pusheo el comando q recibio a la cola de comandos
            } else { // si recibio 0 es pq el cliente finalizo la comunicacion, entonces cierro todo
                _finishThread(); // fin hilo receiver
                break;
            }
        }
    } catch (const Exception& e) {
        fprintf(stderr, "\"[ClientConnection]|[_receiver]: %s\n", e.what());
    }
    this->snapshot.close();
    _finishThread(); // fin hilo receiver
}

// --------------------- API PUBLICA --------------------- //

ClientConnection::ClientConnection(const InstanceId id,
                                   const Id map1,
                                   Socket& peer1,
                                   NonBlockingQueue<InstanceId*>& finished_connections1,
                                   NonBlockingQueue<int*>& commands1) :

                                   connection_id(id),
                                   peer(std::move(peer1)),
                                   finished_connections(finished_connections1),
                                   map(map1),
                                   finished_threads(0),
                                   commands(commands1) {}

void ClientConnection::start() {
    try {
        std::cout << "[ClientConnection]: Lanzo hilos enviadores y recibidores." << std::endl;
        this->sender = std::thread(&ClientConnection::_receiver, this);
        this->receiver = std::thread(&ClientConnection::_sender, this);
    } catch (...) {
        std::cout << "Error desconocido" << std::endl;
    }

}

void ClientConnection::push(int command) {
    snapshot.push(&command);
}

void ClientConnection::stop() {
    // detengo el sender
    snapshot.close();
    try {
        // detengo el receiver
        peer.shutdown();
    } catch (const Exception &e) {
        fprintf(stderr, "[ClientConnection]: Ocurrio un error apagando el socket del cliente.\n");
    }
}

void ClientConnection::join() {
    if (sender.joinable()) {
        sender.join();
    }
    if (receiver.joinable()) {
        receiver.join();
    }
    try {
        // no tiene sentido joinear el sender y receiver y dejar el socket en marcha
        peer.shutdown();
    } catch (const Exception &e) {
        fprintf(stderr, "[ClientConnection]: Ocurrio un error apagando el socket del cliente.\n");
    }
}

ClientConnection::~ClientConnection() = default;
