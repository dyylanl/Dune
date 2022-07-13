#include "../../includes/Control/Engine.h"
#include "../../../Common/includes/RateController.h"

#define SUCCESS 0
#define ERROR 1
#define COMMANDS_COUNT 20

/*
 * 1° Popea un comando
 * 2° Ejecuta ese comando
 * 3° Pushea el resultado de ese comando en snapshot
 * 4° Vuelve a 1°
 */
void Engine::_processCommands() {
    Command* cmd = nullptr;
    while ((cmd = commands.pop())) {
        if (cmd == nullptr) {return;}
        try {
            cmd->exec(model);
        } catch (const std::exception& e) {
            std::cout << "Ejecuto comando invalido" << std::endl;
        }
        delete cmd;
    }
}

void Engine::_processFinishedConnections() {
    InstanceId* finished_connection = nullptr;
    while ((finished_connection = finished_connections.pop())) {
        model.deletePlayer(*finished_connection);
        established_connections.remove(*finished_connection);
        delete finished_connection;
        fprintf(stderr, "[Engine]: Se ha desconectado un jugador.\n");
        if (model.getCurrentPlayers() == 0) {
            keep_executing = false;
            fprintf(stderr, "[Engine]: Partida finalizada.\n");
        }
    }
}

void Engine::clearAll() {
    {
        InstanceId* client = nullptr;
        while ((client = finished_connections.pop())) {
            delete client;
        }
    }
    {
        InstanceId* client = nullptr;
        while ((client = finished_connections.pop())) {
            model.deletePlayer(*client);
        }
    }
    {
        Command* command = nullptr;
        while ((command = commands.pop())) {
            delete command;
        }
    }
}

void Engine::_loopIteration(int it) {
    _processCommands();
    established_connections.sendSnapshot(model.getBuildings(), model.getUnits());
    //map.updateSpice(it);
    //map.update(it);
    //established_connections.updateClients();
    _processFinishedConnections();
}


void Engine::run() {
    fprintf(stderr, "[Engine]: Empezando ejecución.\n");
    established_connections.initGame(model.getMap());     // envio terrenos
    RateController rate_controller(rate);
    established_connections.start();
    rate_controller.start();
    started = (true);
    // GAME-LOOP
    while (keep_executing) {
        _loopIteration(rate_controller.getRateLoop());
        rate_controller.finish();
    }
    established_connections.stop();
    clearAll();
    fprintf(stderr, "[Engine]: Terminando ejecución.\n");
}

void Engine::stop() {
    keep_executing = false;
}

/*
 * Que el engine procese una nueva conexion significa que este cliente ya decidio si
 * creo una partida o se unio a una
 * 1) obtengo el nombre a la partida que decidio unirse
 * 2) le envio el mapa de la partida a la que se unio
 * 3) lo agrego al contenedor de conexiones establecidas
 */
uint16_t Engine::addClient(NewConnection client) {
    uint16_t ret = ERROR;
    if (current_players < req_players) {
        established_connections.add((InstanceId)current_players,std::move(client.peer));
        model.addPlayer((InstanceId)current_players);
        current_players += 1;
        if (current_players == req_players) {
            this->start();
        }
        ret = SUCCESS;
    }
    return ret;
}


std::vector<InstanceId> Engine::getAllPlayers() {
    return established_connections.getAllPlayers();
}

Engine::~Engine() {}

Engine::Engine(ConfigurationReader &config1, std::string map_path, int total_players) :
                                    keep_executing(true),
                                    rate(config1.getFPS()),
                                    current_players(0),
                                    req_players(total_players),
                                    started(false),
                                    finished_connections(),
                                    commands(),
                                    established_connections(commands, finished_connections),
                                    config(config1),
                                    model(config, map_path)
                                    {
                                    }

