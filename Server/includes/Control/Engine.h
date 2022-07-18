#ifndef __ENGINE_H__
#define __ENGINE_H__


#include <cstdio>
#include <atomic>
#include <chrono>
#include <cmath>
#include <iostream>
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../../../Common/includes/Thread.h"
#include "../../includes/Model/DTOs/MapDTO.h"
#include "../../config/MapReader.h"
#include "../../includes/Model/Map.h"
#include "ClientsConnected.h"
#include "NewConnection.h"
#include "Commands/Command.h"
#include "../../config/ConfigReader.h"

class Engine : public Thread {
private:

    std::atomic_bool keep_executing;
    int rate;
    int current_players;
    int req_players;
    bool started;

    // jugadores que se desconectaron
    NonBlockingQueue<InstanceId*> finished_connections;

    //      comandos que recibe de los clientes
    NonBlockingQueue<Command*> commands;
    //      la que envia el server
    //NonBlockingQueue<Command*> snapshot;

    //      clientes conectados a esta partida
    ClientsConnected established_connections;

    ConfigurationReader& config;
    Model model;

    void _processFinishedConnections();
    void _processCommands();
    void _loopIteration(int it);
    void clearAll();
public:
    // el mapDTO que recibe solo tiene la ruta al yaml y el nombre que se eligio para crearlo
    //Engine(MapDTO map);
    Engine(ConfigurationReader& config, std::string map_path, int total_players);
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&& other) = delete;
    Engine& operator=(Engine&& other) = delete;
    void run() override;
    void stop();
    ~Engine() override;
    /*
    *   Retorna 0 si pudo unir el nuevo jugador a la partida
    *   Retorna 1 si no pudo unir el jugador a la partida (es decir, esta completa)
    */
    uint16_t addClient(NewConnection newPlayer);

    /*
    *   Devuelve una lista de todos los id's conectados.
    */
    std::vector<Id> getAllPlayers();

    int getCurrentPlayers() {return model.getCurrentPlayers();}
    int getMaxPlayers() {return model.getMaxPlayers();}
    bool isStarted() {return started;}


};


#endif  // __ENGINE_H__