#include "../../includes/Model/Game.h"
#include "../../config/MapReader.h"

#define FIRST_ID 1
#define SUCCESS 0
#define ERROR 1

class Map;

bool Game::contains(const std::string& game_name) {
    //std::lock_guard<std::mutex> lock(mutex);
    return (this->info_games.find(game_name)!= this->info_games.end());
}

std::vector<int> Game::get(const std::string& game_name) {
    // El contains ya lockea el mutex, no hace falta lockearlo aqui.
    if (contains(game_name)) {
        std::vector<int> game_info;
        game_info.push_back(info_games[game_name][0]); // current players
        game_info.push_back(info_games[game_name][1]); // req players
        return game_info;
    } else {
        throw Exception("Se desea obtener una partida inexistente.\n");
    }
}

void Game::put(const std::string& game_name, int current, int req) {
    //std::lock_guard<std::mutex> lock(mutex);
    std::vector<int> vec = {current, req};
    this->info_games[game_name] = vec;
}

void Game::addPlayer(const std::string& game_name) {
    if (contains(game_name)) {
        put(game_name, (get(game_name)[0]+1), get(game_name)[1]);
    }
}

// ---------- METODOS PUBLICOS ------------ //

Game::Game(int rate, ConfigurationReader reader1) :
            /*maps_created(),*/
            next_id(FIRST_ID),
            game_config(reader1)
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
        std::cout << "Mapa en: " << path << " cargado." << std::endl;
    }
}

uint16_t Game::createGame(Id id_map, const std::string& name_game) {
    std::lock_guard<std::mutex> lock(mutex);
    if (info_games.count(name_game) > 0) {
        std::cout << "Se quiere crear una partida que ya existe..." << std::endl;
    } else {
        // agrego el nuevo mapa...
        int req = maps_dto_init[id_map].max_players; // obtengo jugadores requeridos para ese mapa...
        info_games[name_game] = {0,req}; // le seteo el valor inicial
        return SUCCESS;
    }
    return ERROR;
}

uint16_t Game::acceptPlayer(NewConnection* new_player) {
    std::lock_guard<std::mutex> lock(mutex);
    if (contains(new_player->name_game)) { // pregunto si esa partida existe
        if ((get(new_player->name_game))[0] < (get(new_player->name_game))[1]) { // pregunto si la cantidad de usuarios actuales es menor a la requeridas
            addPlayer(new_player->name_game); // actualizo la info_Games
            //this->maps_created[new_player->name_game]->addPlayer(new_player); // agrego el jugador al mapa que eligio
            return SUCCESS;
        }
    }
    return ERROR;
}


std::vector<std::string> Game::listGames() {
    /*
     * Listar partidas es operacion de lectura.
     * Pueda que mientras se esten recorriendo las
     * partidas otro hilo modifique el map.
     */
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<std::string> list = {};
    if (!this->info_games.empty()) {
        list.push_back(std::to_string(this->info_games.size()));
        for (const auto& [game_name, info] : this->info_games) {
            list.push_back(std::to_string(info[0])); // mando players actuales
            list.push_back(std::to_string(info[1])); // mando maximos
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

Game::~Game() {}



std::vector<MapDTO> Game::getMapsLoads(){
    std::vector<MapDTO> maps_loads;
    for (const auto& [id_game, map_dto] : this->maps_dto_init) {
        maps_loads.push_back(map_dto);
    }
    return maps_loads;
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
