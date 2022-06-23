#include "../../includes/Control/Engine.h"


void Engine::_processNewConnections() {
    NewConnection* new_connection = nullptr;
    while ((new_connection = new_connections.pop())) {
        protocol.sendGameList(new_connection->peer,game.listGames());
        protocol.sendMap(new_connection->peer,game.getMap());
        Id id = new_connection->getId();
        auto map_id = this->game.getMapId(id);
        established_connections.add(id, map_id, (*new_connection).peer);
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
        fprintf(stderr, "[ENGINE]: Procesando comando...\n");
        std::cout << "Ejecutando comando: " << command_process << std::endl;
        std::cout << "Pusheando snapshot" << std::endl;
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
    {
        InstanceId* p = nullptr;
        while ((p = finished_connections.pop())) {
            delete p;
        }
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

