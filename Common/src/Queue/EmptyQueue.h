//
// Created by riclui on 29/06/22.
//

#ifndef DUNE_EMPTYQUEUE_H
#define DUNE_EMPTYQUEUE_H


#include <exception>
#include <string>

class EmptyQueue : public std::exception{
private:
    std::string what_;
public:
    explicit EmptyQueue(std::string msg) { what_ = std::move(msg); }
    [[nodiscard]] const char* what() const noexcept override  { return what_.c_str(); }
};


#endif //DUNE_EMPTYQUEUE_H
