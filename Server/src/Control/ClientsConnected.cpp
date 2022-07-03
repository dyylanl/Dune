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
            std::forward_as_tuple(id, peer, finished_connections,commands));
    clients.at(id).sendEstablishConnection();
}

void ClientsConnected::remove(const InstanceId id) {
    if (clients.count(id) == 0) {
        throw Exception("[CLIENTS]: Se intenta remover un id %i que no existe.\n",id);
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

void ClientsConnected::notify(const InstanceId id, Response* notification) {
    if (clients.count(id) == 0) {
        throw Exception("ActiveClients::notify: invalid client id.");
    }
    clients.at(id).push(notification);
}

void ClientsConnected::initGame(std::vector<std::vector<char>>& map) {
    for (auto it = clients.begin(); it != clients.end(); it++) {
        it->second.sendInitGame(map);
    }
}

void ClientsConnected::sendInitBuildings(std::vector<BuildingDTO> buildings) {
    for (auto it = clients.begin(); it != clients.end(); it++) {
        it->second.sendBuildings(buildings);
    }
}

std::vector<InstanceId> ClientsConnected::getAllPlayers() {
    std::vector<InstanceId> players;
    for (auto it = clients.begin(); it != clients.end(); it++) {
        players.push_back(it->second.getId());
    }
    return players;
}

void ClientsConnected::start() {
    for (auto it = clients.begin(); it != clients.end(); it++) {
        it->second.start();
    }
}

void ClientsConnected::sendSnapshot(Map &map) {
    for (auto it = clients.begin(); it != clients.end(); it++) {
        it->second.sendBuildings(map.getBuildings());
    }
    for (auto it = clients.begin(); it != clients.end(); it++) {
        it->second.sendUnits(map.getUnits());
    }
}
