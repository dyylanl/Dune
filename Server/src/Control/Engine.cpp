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
        //command_process->exec(game);
        delete command_process;
    }*/
}

void Engine::_processFinishedConnections() {
    /*InstanceId* finished_connection = nullptr;
    while ((finished_connection = finished_connections.pop())) {
        delete finished_connection;
        fprintf(stderr, "[ENGINE]: Se ha desconectado un jugador.\n");
    }*/
}

void Engine::_freeQueues() {
       /* InstanceId* p = nullptr;
        while ((p = finished_connections.pop())) {
            delete p;
        }*/
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
    _freeQueues();
    fprintf(stderr, "[ENGINE]: Terminando ejecución.\n");
}

void Engine::stop() {
    keep_executing = false;
}

Engine::~Engine() {
    std::cout << "[ENGINE]: Destruyendo engine." << std::endl;
}


/*
 * Que el engine procese una nueva conexion significa que este cliente ya decidio si
 * creo una partida o se unio a una
 * 1) obtengo el nombre a la partida que decidio unirse
 * 2) le envio el mapa de la partida a la que se unio
 * 3) lo agrego al contenedor de conexiones establecidas
 */
uint16_t Engine::addClient(NewConnection *client) {
    uint16_t ret = ERROR;
    if (current_players < req_players) {
        current_players += 1;
        InstanceId id = current_players;
        std::cout << name_game << " " << current_players << "/" << req_players  << " mapa " << map_id  << std::endl;
        established_connections.add(id,client->map_id,client->peer);
        ret = SUCCESS;
    }
    if (current_players == req_players) {
        established_connections.initGame();
        this->run();
        ret = SUCCESS;
    }
    return ret;
}