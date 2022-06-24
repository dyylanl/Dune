#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

#include <condition_variable>
#include <exception>
#include <mutex>
#include <queue>

template <class T>
class BlockingQueue {
private:
    std::mutex m;
    std::queue<T> queue;
    std::condition_variable cv;
    bool permanently_closed;

public:
    BlockingQueue() : permanently_closed(false) {}
    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;
    BlockingQueue(BlockingQueue&& other) = delete;
    BlockingQueue& operator=(BlockingQueue&& other) = delete;

    // Inserta t y notifica a todos los hilos.
    void push(T t) {
        std::unique_lock<std::mutex> l(m);
        queue.push(t);
        cv.notify_all();
    }

    // Retorna el elemento de la cola y si esta vacia deja en wait al
    // hilo q solicita dicho elemento.
    T pop() {
        std::unique_lock<std::mutex> l(m);
        while (queue.empty()) {
            if (permanently_closed) {
                return NULL;
            }

            cv.wait(l);
        }

        T t = queue.front();
        queue.pop();
        return t;
    }

    // cierra la cola y le avisa a todos los hilos.
    void close() {
        std::unique_lock<std::mutex> l(m);
        permanently_closed = true;
        cv.notify_all();
    }

    // si T es pointer
    /*~BlockingQueue() {
        while (!queue.empty()) {
            T t = queue.front();
            queue.pop();
            delete t;
        }
    }*/
};

#endif  // __BLOCKING_QUEUE_H__
