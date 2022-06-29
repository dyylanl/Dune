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
            std::forward_as_tuple(id, peer, commands,finished_connections));
    clients.at(id).start();
}

void ClientsConnected::remove(const InstanceId id) {
    if (clients.count(id) == 0) {
        throw Exception("[ClientsConnected]: Se intenta remover una conexion que no existe.\n");
    }
    clients.at(id).join();
    clients.erase(id);
}

void ClientsConnected::stop() {
    for (auto it = clients.begin(); it != clients.end(); it++) {
        it->second.stop();
        it->second.join();
    }
    clients.clear();
}

ClientsConnected::~ClientsConnected() = default;



void ClientsConnected::initGame(std::vector<std::vector<char>>& map) {
    for (auto it = clients.begin(); it != clients.end(); it++) {
        it->second.sendInitGame(map);
    }
}

void ClientsConnected::sendInitBuildings(std::vector<BuildingDTO> buildings) {
    for (auto it = clients.begin(); it != clients.end(); it++) {
        it->second.sendInitBuildings(buildings);
    }
}

std::vector<InstanceId> ClientsConnected::getAllPlayers() {
    std::vector<InstanceId> players;
    for (auto it = clients.begin(); it != clients.end(); it++) {
        players.push_back(it->second.getId());
    }
    return players;
}