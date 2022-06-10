//
// Created by riclui on 28/05/22.
//

#include "Player.h"

Player::Player(std::string textureID, TextureManager &manager, SDL2pp::Point position, SDL2pp::Point size)
        : m_Animation(manager, textureID, SDL_FLIP_NONE), corner(position), size(size) ,m_TextureID(textureID), selectStatus(false){}

Player::~Player() {}

void Player::update(EventManager &eventManager, float dt, Socket &skt, int &tam, std::vector<std::vector<int>> &posiciones) {
    //m_Animation.update(dt);
    if(selectStatus && eventManager.mouseButtonDown(RIGHT)){
        uint16_t posX = eventManager.getMouse().GetX()/30;
        uint16_t posY = eventManager.getMouse().GetY()/30;
        skt.send((char*)&posX, sizeof(uint16_t));
        skt.send((char*)&posY, sizeof(uint16_t));

        skt.recv((char*)&tam, sizeof(uint16_t));
        //corner = eventManager.getMouse();
        selectStatus = false;
    }

    if(tam != 0) {
        uint16_t posX1;
        uint16_t posY1;
        skt.recv((char*)&posX1, sizeof(uint16_t));
        skt.recv((char*)&posY1, sizeof(uint16_t));
        corner.SetX(posX1 * 30);
        corner.SetY(posY1 * 30);
        std::cout << corner << std::endl;
        tam = tam -1;
    }
}

void Player::draw(SDL2pp::Renderer &renderer) {
    m_Animation.draw(renderer, corner, size);
}

SDL2pp::Rect Player::getShape() {
    return SDL2pp::Rect(corner, size);
}

void Player::select() {
    selectStatus = true;
}

