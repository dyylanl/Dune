//
// Created by riclui on 30/05/22.
//

#ifndef DUNE_ENGINE_H
#define DUNE_ENGINE_H

#include <vector>
#include "SDL2pp/SDL2pp.hh"
#include "../Graphics/TextureManager.h"
#include "../Camera/Camera.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "../../../Common/includes/Protocol.h"
#include "../../../Common/includes/BlockingQueue.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../Action/CommandCL.h"
#include "../GameObject/Button/ButtonBuild/ButtonWidtrapCL.h"
#include "../../../Common/src/Queue/NBQueue.h"
#include "../../../Common/src/Queue/BQueue.h"

class Engine {
private:
    std::vector<std::vector<char>> m_mapa;
    std::vector<std::unique_ptr<GameObject>> m_objects;
    std::vector<std::unique_ptr<ButtonCL>> m_menu;
    TextureManager &m_TextureManager;
    bool m_Running;
    NBQueue<std::vector<std::unique_ptr<GameObject>>> &m_queueNb;
    BQueue<std::unique_ptr<CommandCL>> &m_queueB;
public:
    Engine(std::vector<std::vector<char>>& mapa, std::vector<std::unique_ptr<ButtonCL>> &menu, TextureManager &manager, NBQueue<std::vector<std::unique_ptr<GameObject>>> &queue_nb, BQueue<std::unique_ptr<CommandCL>> &queueB);

    bool IsRunning();

    void Events();

    void Update();

    void Render(SDL2pp::Renderer &m_Renderer);
};


#endif //DUNE_ENGINE_H
