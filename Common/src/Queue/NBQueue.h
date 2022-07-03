//
// Created by riclui on 29/06/22.
//

#ifndef DUNE_NBQUEUE_H
#define DUNE_NBQUEUE_H

#include <mutex>
#include <queue>
#include "EmptyQueue.h"

template <class T>
class NBQueue {
private:
    std::mutex m;
    std::queue<T> queue;

public:
    NBQueue() = default;
    NBQueue(const NBQueue&) = delete;
    NBQueue& operator=(const NBQueue&) = delete;
    NBQueue(NBQueue&& other) = delete;
    NBQueue& operator=(NBQueue&& other) = delete;

    void push(T &&t) {
        std::unique_lock<std::mutex> l(m);
        queue.push(std::move(t));
    }

    T&& front() {
        std::unique_lock<std::mutex> l(m);
        if (queue.empty()) {
            throw EmptyQueue("front into a empty queue");
        }
        return std::move(queue.front());
    }

    void pop() {
        std::unique_lock<std::mutex> l(m);
        if (queue.empty()) {
            throw EmptyQueue("pop into a empty queue");
        }
        queue.pop();
    }

    ~NBQueue() = default;
};


#endif //DUNE_NBQUEUE_H
