//
// Created by riclui on 29/06/22.
//

#ifndef DUNE_CLOSEDQUEUE_H
#define DUNE_CLOSEDQUEUE_H


#include <exception>
#include <string>

class ClosedQueue : public std::exception{
private:
    std::string what_;
public:
    explicit ClosedQueue(std::string msg) { what_ = std::move(msg); }
    [[nodiscard]] const char* what() const noexcept override  { return what_.c_str(); }
};


#endif //DUNE_CLOSEDQUEUE_H
