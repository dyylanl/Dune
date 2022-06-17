//
// Created by riclui on 15/06/22.
//

#ifndef DUNE_UNIDAD_H
#define DUNE_UNIDAD_H


#include <string>
#include "SDL2pp/Point.hh"

class Unidad {
private:
    int m_id;
    std::string m_unitType;
    int m_player;
    SDL2pp::Point m_position;
    SDL2pp::Point m_posAction;
    int m_life;
    bool m_action;

public:
    Unidad() : m_id(0), m_player(0), m_life(0), m_action(false) {}

    Unidad(int id, std::string &type, int &player,SDL2pp::Point &position, SDL2pp::Point &posAction,int &life, bool &action)
    : m_id(id), m_unitType(type), m_player(player), m_position(position), m_posAction(posAction), m_life(life), m_action(action) {}

    void set(std::string &type, int &player, int &posX, int &posY, int &posActX, int &posActY ,int &life, bool &action) {
        m_unitType = type;
        m_player = player;
        m_position.SetX(posX);
        m_position.SetY(posY);
        m_posAction.SetX(posActX);
        m_posAction.SetY(posActY);
        m_life = life;
        m_action = action;
    }

    std::string& getUnitType() {
        return m_unitType;
    }

    SDL2pp::Point getPosition() {
        return m_position;
    }

    int getID() {
        return 0;
    }
};


#endif //DUNE_UNIDAD_H
