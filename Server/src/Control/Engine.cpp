#include "../../includes/Control/Engine.h"
#include "../../includes/Control/RateController.h"

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
    for (int i = 0; i < COMMANDS_COUNT; i++) {
        while ((cmd = commands.pop())) {
            if (cmd == nullptr) {return;}
            try {
                cmd->exec(map);
            } catch (const std::exception& e) {
                Response* reply = new Response(INVALID_COMMAND, e.what());
                established_connections.notify(cmd->getCaller(), reply);
            }
            delete cmd;
        }
    }
}

void Engine::_processFinishedConnections() {
    InstanceId* finished_connection = nullptr;
    while ((finished_connection = finished_connections.pop())) {
        //map.delete(*finished_connection); TODO: BORRAR JUGADOR
        established_connections.remove(*finished_connection);
        delete finished_connection;
        fprintf(stderr, "Se ha desconectado un jugador.\n");
        current_players -= 1;
    }
}

void Engine::clearAll() {
    {
        InstanceId* p = nullptr;
        while ((p = finished_connections.pop())) {
            delete p;
        }
    }
    {
        InstanceId* p = nullptr;
        while ((p = finished_connections.pop())) {
            //map.deleteCharacter(*p); TODO: BORRAR JUGADOR
        }
    }
    {
        Command* p = nullptr;
        while ((p = commands.pop())) {
            delete p;
        }
    }
}

void Engine::_loopIteration(int it) {
    _processCommands();
    established_connections.sendBuildings(map.getBuildings());   // envio el centro de construccion de cada jugador de la partida
    //map.updateSpice(it);
    //map.update(it);
    //established_connections.updateClients();
    _processFinishedConnections();
}

Engine::Engine(MapDTO map_dto)
        : keep_executing(true),
          rate(30),
          map(map_dto.path),
          current_players(0),
          req_players(map_dto.max_players),
          map_id(map_dto.map_id),
          name_game(map_dto.name_map),
          finished_connections(),
          commands(),
          established_connections(commands, finished_connections) {}


void Engine::run() {
    fprintf(stderr, "[Engine]: Empezando ejecución.\n");
    established_connections.initGame(map.getMap());     // envio terrenos
    RateController rate_controller(rate);
    established_connections.start();
    // GAME-LOOP
    while (keep_executing) {
        rate_controller.start();
        _loopIteration(rate_controller.getRateLoop());
        uint64_t sleep_time = rate_controller.finish();
        rate_controller.sleepFor(sleep_time);
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
        current_players += 1;
        established_connections.add((InstanceId)current_players,client.map_id,client.peer);
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
