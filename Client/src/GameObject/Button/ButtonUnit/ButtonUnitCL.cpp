//
// Created by riclui on 27/06/22.
//

#include "ButtonUnitCL.h"
#include "../../../Action/SelectCL.h"
#include "../../../Action/CreateUniTCL.h"

ButtonUnitCL::ButtonUnitCL(char textureID, SDL2pp::Point position, int id, char player, int constructionTime,
                           bool selectStatus, bool ready)
        : GameObject(textureID, position, SDL2pp::Point(66, 66)), m_unitType(id), m_player(player)
        , m_constructionTime(constructionTime), m_selectStatus(selectStatus), m_ready(ready) {}

void ButtonUnitCL::update(EventManager &eventManager, BQueue<std::unique_ptr<CommandCL>> &queue) {
    if (eventManager.mouseButtonDown(LEFT) && !m_selectStatus) {
        SDL2pp::Rect shape = SDL2pp::Rect(m_position, m_size);
        SDL2pp::Point point = eventManager.getMouse();
        if (SDL_PointInRect(&point, &shape)) {
            std::unique_ptr<CommandCL> command(new CreateUniTCL(m_unitType));
            std::cout << "Push commando Select" << std::endl;
            queue.push(std::move(command));
        }
    }
}

void ButtonUnitCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(renderer, m_textureID, m_position, m_size);
}

