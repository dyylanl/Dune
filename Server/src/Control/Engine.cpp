#include "../../includes/Control/Engine.h"

//-----------------------------------------------------------------------------
// Métodos privados

void Engine::_processNewConnections() {
    NewConnection* new_connection = nullptr;
    while ((new_connection = new_connections.pop())) {
        protocol.sendGameList(new_connection->peer,game.listGames());
        protocol.sendMap(new_connection->peer,game.getMap());
        int map_id = protocol.recvCommand(new_connection->peer); // el cliente le envia con q partida va a jugar
        auto id = this->game.getConnectionId();
        ClientConnection connection(id, this->game.getMapId(map_id),new_connection->peer,finished_connections,commands);
        established_connections.push_back(&connection);
        //connection.start();
        delete new_connection;
    }
}

void Engine::_processCommands() {
    int* command_process = nullptr;
    while ((command_process = commands.pop())) {
        fprintf(stderr, "[ENGINE]: Procesando comando...\n");
        std::cout << "Ejecutando comando: " << command_process << std::endl;
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

Engine::Engine(ConfigurationReader& reader1,
               NonBlockingQueue<NewConnection*>& new_connections)
        : keep_executing(true),
          reader(reader1),
          protocol(),
          rate(30),
          new_connections(new_connections),
          finished_connections(),
          established_connections(),
          game(rate, reader1) {
    int fps = reader.getFPS();
    this->rate = 1000 / fps;
}

void Engine::run() {
    fprintf(stderr, "[ENGINE]: Empezando ejecución.\n");

    // Variables para controlar el frame-rate
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

