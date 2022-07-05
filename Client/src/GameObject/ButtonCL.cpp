//
// Created by riclui on 22/06/22.
//

#include "ButtonCL.h"
#include "../Action/SelectCL.h"

ButtonCL::ButtonCL(char textureID, SDL2pp::Point position, int id, char type, char player, int actionTime, bool selectStatus, bool ready)
        : GameObject(textureID, position, SDL2pp::Point(66, 66)), m_id(id), m_type(type), m_player(player)
        , m_time(actionTime), m_selectStatus(selectStatus), m_ready(ready) {}

void ButtonCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    textureManager.draw(renderer, m_textureID, m_position, m_size);
}
