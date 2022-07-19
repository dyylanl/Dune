//
// Created by riclui on 15/07/22.
//

#include "InfoPlayer.h"

InfoPlayer::InfoPlayer(int gold, int energy, int status)
: GameObject(' ', SDL2pp::Point(0, 0), SDL2pp::Point(191, 87)),
m_gold(gold),
m_energy(energy),
m_status(status) {}

void InfoPlayer::processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue, Camera &camera,
                              SoundManager &soundManager) {}

void InfoPlayer::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    SDL2pp::SDLTTF ttf;
    SDL2pp::Font font(DATA_PATH "assets/fonts/Dune2k.ttf", 20);
    SDL2pp::Texture text_sprite1(
            renderer,
            font.RenderText_Blended(std::to_string(m_gold), SDL_Color{255, 255, 255, 255})
    );
    renderer.Copy(text_sprite1, SDL2pp::NullOpt, SDL2pp::Rect(1130, 30, text_sprite1.GetWidth(), text_sprite1.GetHeight()));

    SDL2pp::Texture text_sprite2(
            renderer,
            font.RenderText_Blended(std::to_string(m_energy), SDL_Color{255, 255, 255, 255})
    );
    renderer.Copy(text_sprite2, SDL2pp::NullOpt, SDL2pp::Rect(1130, 60, text_sprite2.GetWidth(), text_sprite2.GetHeight()));

    textureManager.draw(renderer, ENERGY, SDL2pp::Point(1110, 30), SDL2pp::Point(20, 20));
    textureManager.draw(renderer, GOLD, SDL2pp::Point(1110, 60), SDL2pp::Point(16, 17));
    if(m_status == 1) {
        textureManager.draw(renderer, VICTORY, SDL2pp::Point(0, 0), SDL2pp::Point(562, 218));
    }
    if(m_status == 2) {
        textureManager.draw(renderer, DEFEAT, SDL2pp::Point(0, 0), SDL2pp::Point(708, 352));
    }
}
