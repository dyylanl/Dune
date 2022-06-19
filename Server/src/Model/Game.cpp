#include "../../includes/Model/Game.h"

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

Game::Game(int rate, YAMLReader reader1) :
next_id(FIRST_ID),
map(reader1.getMapPath()),
aStar(map),
units_selected(),
reader(reader1){
    createGame(1,100, "DEFAULT");
    std::cout << this->reader.getMapPath() << std::endl;

}

uint16_t Game::createGame(int house, int req, const std::string& name) {
    std::lock_guard<std::mutex> lock(mutex);
    if (!contains(name)) {
        put(name, 1, req);
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

std::stack<Position> Game::makePath(Unit unit, Position pos_end) {
    return aStar.makePath(unit, pos_end);
}


void Game::selectUnitInPos(int pos_x, int pos_y) {
    Unit* unit = this->map.selectUnit(pos_x, pos_y);
    if (unit != nullptr) {
        units_selected.push_back(unit);
    }
}

void Game::build(char build_type, int pos_x, int pos_y) {
    std::cout << "La funcion de construir no anda todavia" << std::endl;
    //this->map.build(build_type,pos_x,pos_y);
}
