#include "../../includes/Model/Game.h"
#include "../../config/MapReader.h"

#define FIRST_ID 1
#define SUCCESS 0
#define ERROR 1

class Map;

bool Game::contains(const std::string& game_name) {
    //std::lock_guard<std::mutex> lock(mutex);
    return (this->games.find(game_name)!= this->games.end());
}

std::vector<int> Game::get(const std::string& game_name) {
    // El contains ya lockea el mutex, no hace falta lockearlo aqui.
    if (contains(game_name)) {
        std::vector<int> game_info;
        game_info.push_back(games[game_name]->getCurrentPlayers()); // current players
        game_info.push_back(games[game_name]->getReqPlayers()); // req players
        return game_info;
    } else {
        throw Exception("Se desea obtener una partida inexistente.\n");
    }
}

// ---------- METODOS PUBLICOS ------------ //

Game::Game(std::string path_config_game) :
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
    std::lock_guard<std::mutex> lock(mutex);
    if (games.count(name_game) > 0) {
        std::cout << "Se quiere crear una partida que ya existe..." << std::endl;
        return ERROR;
    }
    if (maps_dto_init.count(id_map) == 0) {
        std::cout << "Id de mapa invalido." << std::endl;
        return ERROR;
    }
    MapDTO map;
    map.map_id = id_map;
    map.path = maps_dto_init[id_map].path;
    map.max_players = maps_dto_init[id_map].max_players;
    map.name_map = name_game;
    games[name_game] = (new Engine(map));
    return SUCCESS;
}

uint16_t Game::acceptPlayer(NewConnection* new_player) {
    std::lock_guard<std::mutex> lock(mutex);
    if (games.count(new_player->name_game) > 0) { // si existe una partida con ese nombre entonces entro
        return games[new_player->name_game]->addClient(new_player); // chequea si la partida no esta completa para unir el nuevo player    
    }
    return ERROR;
}

// devuelve algo del tipo {[currents,reqs,len_name,name],...,[---]}
std::vector<std::string> Game::listGames() {
    /*
     * Listar partidas es operacion de lectura.
     * Pueda que mientras se esten recorriendo las
     * partidas otro hilo modifique el map.
     */
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<std::string> list = {};
    if (!this->games.empty()) {
        list.push_back(std::to_string(this->games.size()));
        for (const auto& [game_name, game] : this->games) {
            list.push_back(std::to_string(game->getCurrentPlayers())); // mando players actuales
            list.push_back(std::to_string(game->getReqPlayers())); // mando maximos
            list.push_back(std::to_string((game_name).size())); // mando len del nombre
            list.push_back(game_name); // mando nombre
        }
    }
    return list;
}

/*
std::vector<std::vector<char>>& Game::getMap(std::string name_game) {
    if (contains(name_game)){
        return this->maps_created.at(name_game)->getMap();
    } else {
        std::cout << "[GAME]: la partida " << name_game << " NO existe" << std::endl;
        throw Exception("Acceso invalido a un mapa que no existe.\n");
    }
}*/

Game::~Game() {
    for (const auto& [id, game] : this->games) {
            delete game;
        }
    
}

Id Game::getMapId(std::string name_game) {
    return games[name_game]->getMapId();
}

std::vector<MapDTO> Game::getMapsLoads(){
    std::vector<MapDTO> maps_loads;
    for (const auto& [id_game, map_dto] : this->maps_dto_init) {
        maps_loads.push_back(map_dto);
    }
    return maps_loads;
}



void Game::stop() {
    for (const auto& [name_game, engine] : this->games) {
        std::cout << "FINALIZANDO GAME." << std::endl;
        engine->stop();
        engine->join();
    }
}






// ------------------ ESTO HAY QUE BORRARLO --------------- //
void Game::selectUnitInPos(int pos_x, int pos_y) {
    //this->map.selectUnit(pos_x, pos_y);
    std::cout << "Unidad en la posicion " << pos_x << "," << pos_y << " seleccionada." << std::endl;
}
void Game::build(char build_type, int pos_x, int pos_y) {
    std::cout << "Construyendo " << build_type << "en la posicion " << pos_x << "," << pos_y << std::endl;
    //this->map.build(build_type,pos_x,pos_y);
}
void Game::moveUnitSelecteds(const uint16_t i, const uint16_t i1) {
    std::cout << "Moviendo las unidades seleccionadas" << std::endl;
}
void Game::createUnit(char unit_type) {
    std::cout << "Creando unidades del tipo" << unit_type << std::endl;
}
