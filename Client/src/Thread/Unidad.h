//
// Created by riclui on 15/06/22.
//

#ifndef DUNE_UNIDAD_H
#define DUNE_UNIDAD_H


#include <string>
#include "SDL2pp/Point.hh"

class Unidad {
private:
    std::string m_type;
    int m_player;
    SDL2pp::Point m_position;
    SDL2pp::Point m_posAction;
    int m_life;
    bool m_action;

public:
    Unidad(std::string &type, int &player,SDL2pp::Point &position, SDL2pp::Point &posAction,int &life, bool &action)
    : m_type(type), m_player(player), m_position(position), m_posAction(posAction), m_life(life), m_action(action) {}
};


#endif //DUNE_UNIDAD_H
