#include "../../includes/Control/Engine.h"

/*
 * Que el engine procese una nueva conexion significa que este cliente ya decidio si
 * creo una partida o se unio a una
 * 1) obtengo el nombre a la partida que decidio unirse
 * 2) le envio el mapa de la partida a la que se unio
 * 3) lo agrego al contenedor de conexiones establecidas
 */
void Engine::_processNewConnections() {
    NewConnection* new_connection = nullptr;
    std::string name_game;
    while ((new_connection = new_connections.pop())) {
        name_game = new_connection->name_game;
        std::vector<std::vector<char>>& map = game.getMap(name_game);
        Id map_id = game.getMapId(name_game);
        protocol.sendMap(new_connection->peer,map);
        established_connections.add(game.getConnectionId(),map_id,new_connection->peer);
        delete new_connection;
    }
}

/*
 * 1° Popea un comando
 * 2° Ejecuta ese comando
 * 3° Pushea el resultado de ese comando en snapshot
 * 4° Vuelve a 1°
 */
void Engine::_processCommands() {
    Command* command_process = nullptr;
    while ((command_process = commands.pop())) {
        command_process->exec(game);
        delete command_process;
    }
}

void Engine::_processFinishedConnections() {
    InstanceId* finished_connection = nullptr;
    while ((finished_connection = finished_connections.pop())) {
        delete finished_connection;
        fprintf(stderr, "[ENGINE]: Se ha desconectado un jugador.\n");
    }
}

void Engine::_freeQueues() {
        InstanceId* p = nullptr;
        while ((p = finished_connections.pop())) {
            delete p;
        }
}

void Engine::_loopIteration(int it) {
    _processNewConnections();
    _processCommands();
    _processFinishedConnections();
}

//-----------------------------------------------------------------------------
// API Pública

Engine::Engine(Game& game1, ConfigurationReader& reader1,
               NonBlockingQueue<NewConnection*>& new_connections)
        : keep_executing(true),
          reader(reader1),
          protocol(),
          rate(30),
          new_connections(new_connections),
          finished_connections(),
          game(game1),
          commands(),
          snapshot(),
          established_connections(commands, finished_connections) {
    int fps = reader.getFPS();
    this->rate = 1000 / fps;
}

void Engine::run() {
    fprintf(stderr, "[ENGINE]: Empezando ejecución.\n");
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = t1;
    std::chrono::duration<float, std::milli> diff{};
    int rest = 0, behind = 0, lost = 0;
    int it = 1;
    // LOP GAME = OJO CON LO Q TOCAN ACÁ
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

Engine::~Engine() = default;

