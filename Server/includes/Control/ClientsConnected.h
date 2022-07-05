#ifndef __ACTIVE_CLIENTS_H__
#define __ACTIVE_CLIENTS_H__

#include <unordered_map>
#include "../../../Common/includes/Exceptions/Exception.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "ClientConnection.h"

class Command;

class ClientsConnected {
private:
    NonBlockingQueue<Command*>& commands;
    NonBlockingQueue<InstanceId*>& finished_connections;
    std::unordered_map<InstanceId, ClientConnection> clients;

public:
    ClientsConnected(NonBlockingQueue<Command*>& commands, NonBlockingQueue<InstanceId*>& finished_connections);
    ClientsConnected(const ClientsConnected&) = delete;
    ClientsConnected& operator=(const ClientsConnected&) = delete;
    ClientsConnected(ClientsConnected&& other) = delete;
    ClientsConnected& operator=(ClientsConnected&& other) = delete;

    void add(const InstanceId id, Socket peer);
    void remove(const InstanceId id);
    /*
     * [WARNING] CIERRE FORZOSO
     */
    void stop();
    ~ClientsConnected();

    void notify(Id player_id, Response* resp);

    void initGame(std::vector<std::vector<char>>& map);

    void sendBuildings(std::vector<BuildingDTO> buildings);
    void sendUnits(std::vector<UnitDTO> units);

    std::vector<InstanceId> getAllPlayers();

    void start();
};


#endif  // __ACTIVE_CLIENTS_H__
