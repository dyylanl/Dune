#include "../../includes/Control/Engine.h"

//-----------------------------------------------------------------------------
// Métodos privados

void Engine::_processNewConnections() {
    NewConnection* connection = nullptr;
    while ((connection = new_connections.pop())) {
        fprintf(stderr, "Se ha conectado un jugador.\n");
        // Envio un tanque para probar...
        protocol.sendUnit(connection->peer, 'T');
    }
}

void Engine::_processCommands() {
    fprintf(stderr, "Se ha procesado un comando.\n");

}

void Engine::_processFinishedConnections() {
    fprintf(stderr, "Se ha desconectado un jugador.\n");
}


void Engine::_loopIteration(int it) {
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// API Pública

Engine::Engine(YAMLReader& reader1,
               NonBlockingQueue<NewConnection*>& new_connections)
        : keep_executing(true),
          reader(reader1),
          rate(30),  // default value
          new_connections(new_connections),
          game(rate, reader1),
          protocol(){}

void Engine::run() {
    fprintf(stderr, "ENGINE: Empezando ejecución.\n");
    // Variables para controlar el frame-rate
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = t1;
    std::chrono::duration<float, std::milli> diff{};
    int rest = 0, behind = 0, lost = 0;
    int it = 1;

    while (keep_executing) {
        _processNewConnections();
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
        std::this_thread::sleep_for(std::chrono::milliseconds(rest));
        t1 += std::chrono::milliseconds(rate);
        it += 1;
    }
    fprintf(stderr, "ENGINE: Terminando ejecución.\n");
}

void Engine::stop() {
    keep_executing = false;
}

Engine::~Engine() = default;

void Engine::_sendDifferentialBroadcasts() {

}

//-----------------------------------------------------------------------------
