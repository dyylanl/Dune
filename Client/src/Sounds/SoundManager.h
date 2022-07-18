//
// Created by riclui on 18/07/22.
//

#ifndef DUNE_SOUNDMANAGER_H
#define DUNE_SOUNDMANAGER_H

#include <map>
#include "SDL2pp/Mixer.hh"
#include "SDL2pp/Music.hh"
#include "SDL2pp/Chunk.hh"

#define FREQ 44100
#define CHUNK_SIZE 2048


class SoundManager {
private:
    std::map<std::string, Mix_Music*> m_MusicMap;
    std::map<std::string, Mix_Chunk*> m_EffectMap;
public:
    SoundManager();
    void playMusik(std::string id);
    void loadMusik(std::string id, std::string source);
    void playEffect(std::string id);
    void loadEffect(std::string id, std::string source);
    void clean();
};


#endif //DUNE_SOUNDMANAGER_H
