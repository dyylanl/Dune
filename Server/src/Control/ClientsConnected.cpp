#include "../../includes/Control/ClientsConnected.h"

ClientsConnected::ClientsConnected(
        NonBlockingQueue<Command*>& commands,
        NonBlockingQueue<InstanceId*>& finished_connections) :
        commands(commands),
        finished_connections(finished_connections),
        clients() {}

void ClientsConnected::add(const InstanceId id, const Id map_id, Socket& peer) {
    if (clients.count(id) > 0) {
        throw Exception("[ClientsConnected]: Este jugador ya existe.\n");
    }
    clients.emplace(
            std::piecewise_construct, std::forward_as_tuple(id),
            std::forward_as_tuple(id, map_id, peer, finished_connections, commands));
    clients.at(id).start();
}

void ClientsConnected::remove(const InstanceId id) {
    if (clients.count(id) == 0) {
        throw Exception("[ClientsConnected]: Se intenta remover una conexion que no existe.\n");
    }
    clients.at(id).join();
    clients.erase(id);
}

void ClientsConnected::changeMap(const InstanceId id, const Id new_map) {
    this->clients.at(id).changeMap(new_map);
}

void ClientsConnected::stop() {
    for (auto it = clients.begin(); it != clients.end(); it++) {
        it->second.stop();
        it->second.join();
    }
    clients.clear();
}

ClientsConnected::~ClientsConnected() = default;
