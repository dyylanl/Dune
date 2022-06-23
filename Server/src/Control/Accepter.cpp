#include "../../includes/Control/Accepter.h"

void Accepter::_acceptClient(int next_id) {
    Socket peer = socket.accept();
    if (keep_accepting) {
        auto client = new ClientLogin(next_id,game,peer, reader, new_connections);
        client_logins.emplace_back(client);
        client->start();
    }
}

void Accepter::_joinFinishedLogins() {
    for (auto client = client_logins.begin(); client != client_logins.end();) {
        if (!((*client)->isRunning())) {
            (*client)->join();
            delete (*client);
            client = client_logins.erase(client);
        } else {
            client++;
        }
    }
}

void Accepter::_joinLogins() {
    for (auto client = client_logins.begin(); client != client_logins.end();) {
        (*client)->stop();
        (*client)->join();
        delete (*client);
        client = client_logins.erase(client);
    }
}

// --------------------- // ---------------- //

Accepter::Accepter(Game& game1, const std::string& port, const int max_clients_queued,
                   YAMLReader& reader1,
                   NonBlockingQueue<NewConnection*>& new_connections1)
        : socket(port, max_clients_queued),
          reader(reader1),
          new_connections(new_connections1),
          keep_accepting(true),
          game(game1) {}

void Accepter:: run() {
    int next_id = 1;
    fprintf(stderr, "[Accepter]: Comenzando ejecucion.\n");
    try {
        while (keep_accepting) {
            _acceptClient(next_id);
            _joinFinishedLogins();
            next_id++;
        }
    } catch (const ClosedSocketException& e) {
    } catch (const std::exception& e) {
        fprintf(stderr, "%s\n", e.what());
    } catch (...) {
        fprintf(stderr, "[Accepter]Ocurrio un error en ejecucion.\n");
    }
    _joinLogins();
    fprintf(stderr, "[Accepter]: Terminando ejecucion.\n");
}

void Accepter::stop() {
    keep_accepting = false;
    try {
        socket.shutdown();
    } catch (const Exception& e) {
        fprintf(stderr,
                "[Accepter]: Error apagando el socket.\n");
    }
    socket.close();
}

Accepter::~Accepter() {
    _joinLogins();
}
