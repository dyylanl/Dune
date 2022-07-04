#include "../../includes/Model/Game.h"
#include "../../config/MapReader.h"

#define SUCCESS 0
#define ERROR 1

bool Game::contains(const std::string& game_name) {
    //std::lock_guard<std::mutex> lock(mutex);
    return (this->info_games.find(game_name)!= this->info_games.end());
}

std::vector<int> Game::get(const std::string& game_name) {
    std::lock_guard<std::mutex> lock(mutex);
    if (contains(game_name)) {
        std::vector<int> game_info;
        game_info.push_back(info_games[game_name][0]); // current players
        game_info.push_back(info_games[game_name][1]); // req players
        return game_info;
    } else {
        throw Exception("Se desea obtener una partida inexistente.\n");
    }
}

// ---------- METODOS PUBLICOS ------------ //

Game::Game(std::string path_config_game) :
        maps_dto_init(),
        info_games(),
        games(),
        game_config(path_config_game)

{
    std::list<std::string> map_paths = game_config.getAllPaths();
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

uint16_t Game::createGame(Id id_map, const std::string& name_game) {
    std::lock_guard<std::mutex> lock(this->mutex);
    if (contains(name_game)) {
        return ERROR;
    }
    if (maps_dto_init.count(id_map) == 0) {
        return ERROR;
    }
    MapDTO map;
    map.map_id = id_map;
    map.path = maps_dto_init[id_map].path;
    map.max_players = maps_dto_init[id_map].max_players;
    map.name_map = name_game;
    games[name_game] = (new Engine(map));
    this->info_games[name_game] = {0,maps_dto_init[id_map].max_players,(int)id_map}; // currents:0 , max_players: dto.max_players, id_map
    return SUCCESS;
}

uint16_t Game::acceptPlayer(Socket peer, std::string name_player, std::string name_game) {
    std::lock_guard<std::mutex> lock(this->mutex);
    int ret = ERROR;
    if (contains(name_game)) { // si existe una partida con ese nombre entonces entro
        Id map_id1 = (Id)games[name_game]->getMapId();
        ret = games[name_game]->addClient(NewConnection((peer),name_player,name_game,map_id1)); // chequea si la partida no esta completa para unir el nuevo player
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
            std::vector<std::string> info_game = {};
            info_game.push_back(std::to_string(engine->getCurrentPlayers()));
            info_game.push_back(std::to_string(engine->getMaxPlayers()));
            info_game.push_back(game_name);
            list.push_back(info_game);
        }
    }
    return list;
}

Game::~Game() {
    for (const auto& [name, engine] : this->games) {
        delete engine;
    }

}

Id Game::getMapId(std::string name_game) {
    if (contains(name_game)) {
        return games[name_game]->getMapId();
    } else {
        throw Exception("Invalid get map id.\n");
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