#include "../../includes/Control/Accepter.h"

// --------- METODOS PRIVADOS --------- //

void Accepter::_acceptClient() {
    Socket peer = socket.accept();
    if (keep_accepting) {
        auto client = new ClientLogin(peer, reader, new_connections);
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

Accepter::Accepter(const std::string& port, const int max_clients_queued,
                   YAMLReader& reader1,
                   NonBlockingQueue<NewConnection*>& new_connections1)
        : socket(port, max_clients_queued),
          reader(reader1),
          new_connections(new_connections1),
          keep_accepting(true) {}

void Accepter:: run() {
    try {
        while (keep_accepting) {
            _acceptClient();
            _joinFinishedLogins();
        }
    } catch (const ClosedSocketException& e) {
    } catch (const std::exception& e) {
        fprintf(stderr, "%s\n", e.what());
    } catch (...) {
        fprintf(stderr, "Unknown error.\n");
    }
    _joinLogins();
}

void Accepter::stop() {
    keep_accepting = false;
    try {
        socket.shutdown();
    } catch (const Exception& e) {
        fprintf(stderr,
                "Warning: error while shutting-down accepter. Aborting.\n");
    }
    socket.close();
}

Accepter::~Accepter() {
    _joinLogins();
}
