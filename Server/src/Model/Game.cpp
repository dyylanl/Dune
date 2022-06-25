#include "../../includes/Model/Game.h"
#include "../../includes/Model/Player.h"

#define FIRST_ID 1
#define SUCCESS 0
#define ERROR 1

bool Game::contains(const std::string& game_name) {
    //std::lock_guard<std::mutex> lock(mutex);
    return (this->games.find(game_name)!= this->games.end());
}

std::vector<int> Game::get(const std::string& game_name) {
    // El contains ya lockea el mutex, no hace falta lockearlo aqui.
    if (contains(game_name)) {
        return this->games[game_name];
    }
    return {-1, -1};
}

void Game::put(const std::string& game_name, int current, int req) {
    //std::lock_guard<std::mutex> lock(mutex);
    std::vector<int> vec = {current, req};
    this->games[game_name] = vec;
}

void Game::addPlayer(const std::string& game_name) {
    if (contains(game_name)) {
        put(game_name, (get(game_name)[0]+1), get(game_name)[1]);
    }
}

// ---------- METODOS PUBLICOS ------------ //

Game::Game(int rate, ConfigurationReader reader1) :
            maps_init(),
            maps_created(),
            games(),
            players(),
            /*map(reader1.getMapPath()),*/
            /*aStar(map),*/
            next_id(FIRST_ID),
            game_config(reader1)
{
    std::list<std::string> map_paths = game_config.getAllPaths();
    int map_id = 1;
    for (auto path : map_paths) {
        this->maps_init[map_id] = new Map(path);
        map_id++;
    }
}

uint16_t Game::createGame(Id id_map, const std::string& name_game) {
    std::lock_guard<std::mutex> lock(mutex);
    if (!contains(name_game)) {
        int req = maps_init[id_map]->getReqPlayers();
        put(name_game, 1, req);
        this->maps_created[name_game] = maps_init[id_map];
        if (req == 1) {
            std::cout << "Iniciando partida " << name_game << "..." << std::endl;
            return SUCCESS;
        }
        std::cout << "Se creo la partida " << name_game << " de " << req << " jugadores."<< std::endl;
        return SUCCESS;
    }
    return ERROR;
}

uint16_t Game::acceptPlayer(const std::string& name) {
    std::lock_guard<std::mutex> lock(mutex);
    if (contains(name)) {
        if ((get(name))[0] < (get(name))[1]) {
            addPlayer(name);
            if (get(name)[0] == get(name)[1]) {
                std::cout << "Comenzando partida " << name << "..." << std::endl;
            }
            return SUCCESS;
        }
    }
    return ERROR;
}

/*
  // La salida estandar no es thread safe, se pueden dar varios comienzos a la vez - Dylan.
void Game::printStartGame(const std::string& name) {
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Comenzando partida " << name << "..." << std::endl;
}
*/

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
        for (const auto& [game_name, values] : this->games) {
            list.push_back(std::to_string(values[0]));
            list.push_back(std::to_string(values[1]));
            list.push_back(std::to_string((game_name).size()));
            list.push_back(game_name);
        }
    }
    return list;
}

InstanceId Game::newConnection(NewConnection *connection) {
    this->next_id++;
    return this->next_id;
}
// todo: uf
std::stack<Position> Game::makePath(Unit& unit, Position pos_end) {
    /*AStar aStar(this->maps_init[unit.getPlayer().getId()]);
    return aStar.makePath(unit, pos_end);*/
    std::stack<Position> pos;
    pos.push(Position(5,5));
    return pos;
}


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

std::vector<std::vector<char>>& Game::getMap(std::string name_game) {
    if (contains(name_game)){
        return this->maps_created.at(name_game)->getMap();
    } else {
        std::cout << "[GAME]: la partida " << name_game << " NO existe" << std::endl;
        throw Exception("Acceso invalido a un mapa que no existe.\n");
    }
}

Game::~Game() {
}

std::vector<std::string> Game::getMaps() {
    std::vector<std::string> maps;
    int total = maps_init.size();
    for (int i=1; i<=total; i++) {
        std::string key_ = std::to_string(i);
        maps.push_back(key_);
    }
    return maps;
}
