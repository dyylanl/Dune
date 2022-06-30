#include "../../includes/Control/Engine.h"
#define SUCCESS 0
#define ERROR 1

/*
 * 1° Popea un comando
 * 2° Ejecuta ese comando
 * 3° Pushea el resultado de ese comando en snapshot
 * 4° Vuelve a 1°
 */
void Engine::_processCommands() {
    /*Command* command_process = nullptr;
    while ((command_process = commands.pop())) {
        std::cout << "Ejecutando comando." << std::endl;
        delete command_process;
    }*/
}

void Engine::_processFinishedConnections() {
    InstanceId* finished_connection = nullptr;
    while ((finished_connection = finished_connections.pop())) {
        delete finished_connection;
        fprintf(stderr, "[ENGINE]: Se ha desconectado un jugador.\n");
    }
}

void Engine::_loopIteration(int it) {
    _processCommands();
    _processFinishedConnections();

}

// ---------------------------------------------- //

Engine::Engine(MapDTO map_dto) : 
        keep_executing(true),
        rate(30),
        map(map_dto.path),
        current_players(0),
        req_players(map_dto.max_players),
        map_id(map_dto.map_id),
        name_game(map_dto.name_map),
        finished_connections(),
        commands(),
        established_connections(commands, finished_connections)
{

}

void Engine::run() {
    fprintf(stderr, "[ENGINE]: Empezando partida.\n");
    established_connections.initGame(map.getMap());     // envio terrenos
    established_connections.sendInitBuildings(map.getBuildings());   // envio el centro de construccion de cada jugador de la partida
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = t1;
    std::chrono::duration<float, std::milli> diff{};
    int rest = 0, behind = 0, lost = 0;
    int it = 1;
    // LOOP GAME = OJO CON LO Q TOCAN ACÁ
    while (keep_executing) {
        _loopIteration(it);
        it = 0;
        t2 = std::chrono::steady_clock::now();
        diff = t2 - t1;
        rest = rate - std::ceil(diff.count());
        if (rest < 0) {
            behind = -rest;
            lost = rate + (behind - behind % rate);
            rest = rate - behind % rate;
            t1 += std::chrono::milliseconds(lost);
            it += std::floor(lost / rate);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(rest));
        t1 += std::chrono::milliseconds(rate);
        it += 1;
    }
    clearAll();
    fprintf(stderr, "[ENGINE]: Terminando ejecución.\n");
}

void Engine::clearAll() {
    InstanceId* id_dlt = nullptr;
    while ((id_dlt = finished_connections.pop())) {
        std::cout << "[ENGINE]: Eliminando jugador." << std::endl;
        established_connections.remove(*id_dlt);
        delete id_dlt;
    }
    /*Command* command = nullptr;
    while ((command = commands.pop())) {
        delete command;
    }*/
}

void Engine::stop() {
    keep_executing = false;
}

Engine::~Engine() {}


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
            ret = SUCCESS;
        }
        ret = SUCCESS;
    }
    return ret;
}


std::vector<InstanceId> Engine::getAllPlayers() {
    return established_connections.getAllPlayers();
}