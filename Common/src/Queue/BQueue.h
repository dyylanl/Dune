//
// Created by riclui on 29/06/22.
//

#ifndef DUNE_BQUEUE_H
#define DUNE_BQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include "EmptyQueue.h"
#include "ClosedQueue.h"

template <class T>
class BQueue {
private:
    std::mutex m;
    std::queue<T> queue;
    std::condition_variable cv;
    bool permanently_closed;

public:
    BQueue() : permanently_closed(false) {}
    BQueue(const BQueue&) = delete;
    BQueue& operator=(const BQueue&) = delete;
    BQueue(BQueue&& other) = delete;
    BQueue& operator=(BQueue&& other) = delete;

    // Inserta t y notifica a todos los hilos.
    void push(T &t) {
        std::unique_lock<std::mutex> l(m);
        queue.push(std::move(t));
        cv.notify_all();
    }

    // Retorna el elemento de la cola y si esta vacia deja en wait al
    // hilo q solicita dicho elemento.
    bool pop(T &t) {
        std::unique_lock<std::mutex> l(m);
        while (queue.empty()) {
            if (permanently_closed) {
                throw ClosedQueue("Cola cerrada");
            }
            cv.wait(l);
        }
        t = std::move(queue.front());
        queue.pop();
        return true;
    }

    // cierra la cola y le avisa a todos los hilos.
    void close() {
        std::unique_lock<std::mutex> l(m);
        permanently_closed = true;
        cv.notify_all();
    }
};


#endif //DUNE_BQUEUE_H
