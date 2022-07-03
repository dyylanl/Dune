#include "../includes/Thread.h"
#include "../includes/Exceptions/ClosedSocketException.h"

Thread::Thread() : thread() {}

Thread::Thread(Thread&& other) {
    this->thread = std::move(other.thread);
}

Thread& Thread::operator=(Thread&& other) {
    this->thread = std::move(other.thread);
    return *this;
}

void Thread::start() {
    this->thread = std::thread(&Thread::safe_run, this);
}

void Thread::safe_run() {
    try {
        this->run(); // <- este es el método abstracto que todos los hijos implementan
    } catch(const ClosedSocketException &e) { // si el hilo ejecutaba comnunicación por un socket y lo cerraro (y se señalizó debidamente el cierre del hilo) entonce sno es un error
        fprintf(stderr, "Socket closed exception.\n");
    } catch(const std::exception &e) {
        fprintf(stderr, "%s\n", e.what());
    } catch(...) {
        fprintf(stderr, "Unknown error in thread.\n");
    }
}

bool Thread::joinable() {
    return thread.joinable();
}

void Thread::join() {
    if (thread.joinable()) {
        thread.join();
    }
}

Thread::~Thread() {
    join();
}

//-----------------------------------------------------------------------------
