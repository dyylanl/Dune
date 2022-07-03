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

    void add(const InstanceId id, const Id map, Socket& peer);
    void remove(const InstanceId id);
    /*
     * [WARNING] CIERRE FORZOSO
     */
    void stop();
    ~ClientsConnected();

    void notify(Id player_id, Response* resp);


    void initGame(std::vector<std::vector<char>>& map);

    void sendInitBuildings(std::vector<BuildingDTO> buildings);

    std::vector<InstanceId> getAllPlayers();

    void start();

};


#endif  // __ACTIVE_CLIENTS_H__
