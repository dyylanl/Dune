#include "../../includes/Control/Engine.h"


/*
 * A cada nueva conexion le envia el mapa de terrenos correspondiente
 */
void Engine::_processNewConnections() {
    NewConnection* new_connection = nullptr;
    while ((new_connection = new_connections.pop())) {
        protocol.sendMap(new_connection->peer, this->game.getMap());
        //protocol.recvCommand(new_connection->peer);
        delete new_connection;
        fprintf(stderr, "Se ha conectado un jugador.\n");
    }
}


void Engine::_processCommands() {
    fprintf(stderr, "Se ha procesado un comando.\n");

}


void Engine::_processFinishedConnections() {
    fprintf(stderr, "Se ha desconectado un jugador.\n");
}


void Engine::_loopIteration(int it) {
    _processNewConnections();
}

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
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = t1;
    std::chrono::duration<float, std::milli> diff;
    int rest = 0, behind = 0, lost = 0;
    int it = 1;
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
