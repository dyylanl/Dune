//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTON_H
#define DUNE_BUTTON_H


#include "SDL2pp/SDL2pp.hh"

class Button {
private:
    std::string m_name;
    SDL2pp::Point m_position;
    SDL2pp::Point m_size;
    bool m_select;
public:
    Button(std::string name, SDL2pp::Point position, SDL2pp::Point size) : m_name(name), m_position(position), m_size(size), m_select(false){}

    SDL2pp::Rect getShape() {
        return SDL2pp::Rect(m_position, m_size);
    }

    void draw(SDL2pp::Renderer &renderer);
};


#endif //DUNE_BUTTON_H
