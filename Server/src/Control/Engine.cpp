#include "../../includes/Control/Engine.h"
#define SUCCESS 0
#define ERROR 1



#include "../../includes/Control/Engine.h"

//-----------------------------------------------------------------------------
// Métodos privados

/*
 * 1° Popea un comando
 * 2° Ejecuta ese comando
 * 3° Pushea el resultado de ese comando en snapshot
 * 4° Vuelve a 1°
 */

void Engine::_processCommands() {
    Command* cmd = nullptr;
    while ((cmd = commands.pop())) {
        std::cout << "[ENGINE]: Procesando comando..." << std::endl;
        try {
            cmd->exec(map);
        } catch (const std::exception& e) {
            Response* reply = new Response(INVALID_COMMAND, e.what());
            established_connections.notify(cmd->getCaller(), reply);
        }
        delete cmd;
    }
}

void Engine::_processFinishedConnections() {
    InstanceId* finished_connection = nullptr;
    while ((finished_connection = finished_connections.pop())) {
        //map.deleteCharacter(*finished_connection); TODO: BORRAR JUGADOR
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
    //std::cout << "[ENGINE]: It: " << it << std::endl;
    _processCommands();
    /*game.actCharacters(it);
    game.actCreatures(it);
    game.spawnNewCreatures(it);TODO: LOGICA DEL JUEGO
    game.persistPeriodicData(database, it);
    game.updateDroppedItemsLifetime(it);
    game.updateResurrectingPlayersCooldown(it);*/
    _processFinishedConnections();
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// API Pública

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
    fprintf(stderr, "ENGINE: Empezando ejecución.\n");
    established_connections.initGame(map.getMap());     // envio terrenos
    established_connections.sendInitBuildings(map.getBuildings());   // envio el centro de construccion de cada jugador de la partida
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = t1;
    std::chrono::duration<float, std::milli> diff;
    int rest = 0;
    int behind = 0;
    int lost = 0;
    int it = 1;
    established_connections.start();
    while (keep_executing) {
        _loopIteration(it);
        it = 0;
        t2 = std::chrono::steady_clock::now();
        diff = t2 - t1;
        rest = rate - std::ceil(diff.count());
        if (rest < 0) {
            fprintf(stderr, ">> Ciclo principal: pérdida de frame/s.\n");
            behind = -rest;
            lost = rate + (behind - behind % rate);
            rest = rate - behind % rate;
            t1 += std::chrono::milliseconds(lost);
            it += std::floor(lost / rate);
        }
        //fprintf(stderr, "ENGINE: Sleeping for %i ms.\n", rest);
        std::this_thread::sleep_for(std::chrono::milliseconds(rest));
        t1 += std::chrono::milliseconds(rate);
        it += 1;
    }
    //-------------------------------------------------------------------------
    // Salimos ordenadamente:
    // Terminamos las conexiones
    established_connections.stop();
    // Vaciamos las colas para no perder memoria:
    clearAll();
    fprintf(stderr, "ENGINE: Terminando ejecución.\n");
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
        std::cout << "[ENGINE]: Cliente aceptado." << std::endl;
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

//-----------------------------------------------------------------------------












