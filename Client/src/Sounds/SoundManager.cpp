//
// Created by riclui on 18/07/22.
//

#include <iostream>
#include "SoundManager.h"

SoundManager::SoundManager() {
    if(Mix_OpenAudio(FREQ, MIX_DEFAULT_FORMAT, 2, CHUNK_SIZE) < 0)
        std::cerr << Mix_GetError() << std::endl;
    loadMusik("atreides", DATA_PATH "assets/Music/atreides.mp3");
    loadMusik("harkonnen", DATA_PATH "assets/Music/harkonnen.mp3");
    loadMusik("ordos", DATA_PATH "assets/Music/ordos.mp3");
    loadEffect("building", DATA_PATH "assets/Sound/atreides/message/building.mp3");
    loadEffect("unit_created", DATA_PATH "assets/Sound/atreides/message/unit_created.mp3");
    loadEffect("unit_selected", DATA_PATH "assets/Sound/atreides/message/unit_selected.mp3");
    loadEffect("unit_moved", DATA_PATH "assets/Sound/atreides/message/unit_moved.mp3");
}

void SoundManager::playMusik(std::string id) {
    if(Mix_PlayMusic(m_MusicMap[id], -1) == -1)
        std::cerr << Mix_GetError() << ": " << id << std::endl;
}

void SoundManager::loadMusik(std::string id, std::string source) {
    Mix_Music* music = Mix_LoadMUS(source.c_str());
    if(music != nullptr)
        m_MusicMap[id] = music;
    else
        std::cerr << Mix_GetError() << ": " << source << std::endl;
}

void SoundManager::playEffect(std::string id) {
    if(Mix_PlayChannel(-1, m_EffectMap[id], 0) == -1)
        std::cerr << Mix_GetError() << ": " << id << std::endl;
}

void SoundManager::loadEffect(std::string id, std::string source) {
    Mix_Chunk* effect = Mix_LoadWAV(source.c_str());
    if(effect != nullptr)
        m_EffectMap[id] = effect;
    else
        std::cerr << Mix_GetError() << ": " << source << std::endl;
}

void SoundManager::clean() {
    for(std::map<std::string, Mix_Music*>::iterator it = m_MusicMap.begin(); it != m_MusicMap.end(); it++)
        Mix_FreeMusic(it->second);

    for(std::map<std::string, Mix_Chunk*>::iterator it = m_EffectMap.begin(); it != m_EffectMap.end(); it++)
        Mix_FreeChunk(it->second);

    m_MusicMap.clear();
    m_EffectMap.clear();
    std::cout << "sound system cleaned!" << std::endl;
}
