//
// Created by riclui on 16/06/22.
//

#ifndef DUNE_ACTION_H
#define DUNE_ACTION_H

#include "SDL2pp/Point.hh"

class Action {
private:
    int m_action;
    int m_id;
    int m_object;
    SDL2pp::Point m_position;

public:

    int getAction() const {return m_action;}

    int getId() const {return m_id;}

    int getObject() const {return m_object;}

    int getPosX() const {return m_position.GetX();}

    int getPosY() const {return m_position.GetY();}

    Action(int action, int id, int object, SDL2pp::Point position) : m_action(action), m_id(id), m_object(object), m_position(position) {}
};


#endif //DUNE_ACTION_H
