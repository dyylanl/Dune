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
    std::cout << "Se unio un jugador a la partida " << game_name << std::endl;
}

Game::Game(int rate, ConfigurationReader reader1) :
            next_id(FIRST_ID),
            map(reader1.getMapPath()),
            aStar(map),
            units_selected(),
            game_config(reader1)
{}

uint16_t Game::createGame(int req, const std::string& name) {
    std::lock_guard<std::mutex> lock(mutex);
    if (!contains(name)) {
        put(name, 1, req);
        std::cout << "Se creo la partida " << name << std::endl;
        if (req == 1) {
            std::cout << "Comenzando partida " << name << "..." << std::endl;
        }
        return SUCCESS;
    }
    return ERROR;
}

uint16_t Game::acceptPlayer(const std::string& name) {
    std::lock_guard<std::mutex> lock(mutex);
    if (contains(name)) {
        if ((get(name))[0] < (get(name))[1]) {
            addPlayer(name);
            std::cout << "Se unio un jugador a la partida " << name << std::endl;
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

std::stack<Position> Game::makePath(Unit& unit, Position pos_end) {
    return aStar.makePath(unit, pos_end);
}


void Game::selectUnitInPos(int pos_x, int pos_y) {
    this->map.selectUnit(pos_x, pos_y);
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
