#include "../../includes/Model/Game.h"
#include "../../config/MapReader.h"

#define SUCCESS 0
#define ERROR 1

bool Game::contains(const std::string& game_name) {
    //std::lock_guard<std::mutex> lock(mutex);
    return (this->games.find(game_name)!= this->games.end());
}

std::vector<int> Game::get(const std::string& game_name) {
    std::lock_guard<std::mutex> lock(mutex);
    if (contains(game_name)) {
        std::vector<int> info;
        info.push_back(games[game_name]->getCurrentPlayers()); // current players
        info.push_back(games[game_name]->getMaxPlayers()); // req players
        return info;
    } else {
        throw Exception("Se desea obtener una partida inexistente.\n");
    }
}

// ---------- METODOS PUBLICOS ------------ //

Game::Game(std::string path_config_game) :
        maps_dto_init(),
        games(),
        config(path_config_game)

{
    std::list<std::string> map_paths = config.getAllPaths();
    int map_id = 1;
    for (auto path : map_paths) {
        MapReader mapReader(path);
        MapDTO mapDto;
        mapDto.path = path;
        mapDto.map_id = map_id;
        mapDto.rows = (int)mapReader.getRows();
        mapDto.cols = (int)mapReader.getCols();
        mapDto.max_players = (int)mapReader.getReqPlayers();
        mapDto.map = mapReader.getMap();
        this->maps_dto_init[map_id] = mapDto;
        map_id++;
    }
}

uint16_t Game::createGameAndAcceptPlayer(Id id_map, const std::string& name_game, Socket peer, std::string name_player) {
    std::lock_guard<std::mutex> lock(this->mutex);
    int ret = ERROR;
    if (contains(name_game)) {
        return ret;
    }
    if (maps_dto_init.count(id_map) == 0) {
        return ret;
    }
    games[name_game] = new Engine(config,maps_dto_init[id_map].path, maps_dto_init[id_map].max_players);
    ret = games[name_game]->addClient(NewConnection((peer),name_player,name_game)); // chequea si la partida no esta completa para unir el nuevo player
    return ret;
}

uint16_t Game::acceptPlayer(Socket peer, std::string name_player, std::string name_game) {
    std::lock_guard<std::mutex> lock(this->mutex);
    int ret = ERROR;
    if (contains(name_game)) { // si existe una partida con ese nombre entonces entro
        ret = games[name_game]->addClient(NewConnection((peer),name_player,name_game)); // chequea si la partida no esta completa para unir el nuevo player
    }
    return ret;
}

// devuelve algo del tipo {[currents,reqs,name],...,[---]}
std::vector<std::vector<std::string>> Game::listGames() {
    /*
     * Listar partidas es operacion de lectura.
     * Pueda que mientras se esten recorriendo las
     * partidas otro hilo modifique el map.
     */
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<std::vector<std::string>> list = {};
    if (!this->games.empty()) {
        for (const auto& [game_name, engine] : this->games) {
            if (engine->getCurrentPlayers() != 0) {
                std::vector<std::string> info = {};
                info.push_back(std::to_string(engine->getCurrentPlayers()));
                info.push_back(std::to_string(engine->getMaxPlayers()));
                info.push_back(game_name);
                list.push_back(info);
            }
        }
    }
    return list;
}

Game::~Game() {
    for (const auto& [name, engine] : this->games) {
        engine->stop();
        delete engine;
    }

}

std::vector<MapDTO> Game::getMapsLoads(){
    // no hay rc dado que solo se carga una vez sola cuando inicia el game
    std::vector<MapDTO> maps_loads;
    for (const auto& [id_game, map_dto] : this->maps_dto_init) {
        maps_loads.push_back(map_dto);
    }
    return maps_loads;
}

std::vector<std::vector<InstanceId>> Game::getAllPlayers() {
    std::unique_lock<std::mutex> lock(mutex);
    std::vector<std::vector<InstanceId>> all_players;
    for (const auto& [game_name, engine] : this->games) {
        std::vector<InstanceId> players = engine->getAllPlayers();
        all_players.push_back(players);
    }
    return all_players;
}

bool Game::acceptNewPlayer(std::string name_game) {
    std::unique_lock<std::mutex> lock(mutex);
    int currents = games[name_game]->getCurrentPlayers();
    int req = games[name_game]->getMaxPlayers();
    if (!(currents < req)) {
        return false;
    }
    if (games[name_game]->isStarted()) {
        return false;
    }
    return true;
}

void Game::stop() {
    for (const auto& [name_game, engine] : this->games) {
        engine->stop();
        engine->join();
    }
}