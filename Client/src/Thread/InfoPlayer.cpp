//
// Created by riclui on 15/07/22.
//

#include "InfoPlayer.h"

InfoPlayer::InfoPlayer(int gold, int energy) : GameObject(' ', SDL2pp::Point(0, 0), SDL2pp::Point(191, 87)), m_gold(gold), m_energy(energy) {}

void InfoPlayer::processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue, Camera &camera) {}

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
}
