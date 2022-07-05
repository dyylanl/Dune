#include "../includes/Protocol.h"
#include <iostream>

#define JOIN 1
#define LIST 2
#define CREATE 3

Protocol::Protocol() : was_closed(false) {}

void Protocol::close() {
    this->was_closed = true;
}

Protocol::~Protocol() {
    this->close();
}

bool Protocol::sendName(Socket &socket, std::string name) {
    uint16_t len_name = name.size();
    socket.send(reinterpret_cast<const char *>(&len_name), sizeof(uint8_t));
    int size = socket.send(name.c_str(), name.size());
    int esp = name.size();
    std::cout << "[PROTOCOL]: SE ENVIA NAME: " << name << std::endl;
    if (size < esp) {
        return false;
    }
    return true;
}

std::string Protocol::recvName(Socket &skt) {
    uint16_t name_len = this->recvNameLen(skt);
    std::vector<char> name(name_len+1);
    int bytes_recv = skt.recv(name.data(), name_len);
    name[bytes_recv] = 0;
    std::string game_name = name.data();
    return game_name;
}

uint16_t Protocol::recvNameLen(Socket &skt) {
    uint16_t len = 0;
    skt.recv(reinterpret_cast<char *>(&len), sizeof(uint8_t));
    return len;
}

void Protocol::joinGame(Socket &skt, uint16_t house, const std::string& name) {
    uint16_t command = JOIN;
    uint16_t game_name_len = name.size();
    game_name_len = htons(game_name_len);
    skt.send(reinterpret_cast<const char *>(&command), sizeof(uint8_t));
    skt.send(reinterpret_cast<const char *>(&house), sizeof(uint8_t));
    skt.send(reinterpret_cast<const char *>(&game_name_len), sizeof(uint16_t));
    skt.send(name.c_str(), (name).size());
}

void Protocol::listGames(Socket &skt) {
    uint16_t command = LIST;
    skt.send(reinterpret_cast<const char *>(&command), sizeof(uint8_t));
}

void Protocol::createGame(Socket &skt, uint16_t house,
                          const std::string& name, int req) {
    uint16_t command = CREATE;
    auto req_s = (uint16_t) req;
    uint16_t game_name_len = name.size();
    game_name_len = htons(game_name_len);
    skt.send(reinterpret_cast<const char *>(&command), sizeof(uint8_t));
    skt.send(reinterpret_cast<const char *>(&house), sizeof(uint8_t));
    skt.send(reinterpret_cast<const char *>(&req_s), sizeof(uint8_t));
    skt.send(reinterpret_cast<const char *>(&game_name_len), sizeof(uint16_t));
    skt.send(name.c_str(), (name).size());
}

uint8_t Protocol::recvCommand(Socket &skt) {
    uint8_t command = 0;
    skt.recv(reinterpret_cast<char *>(&command), sizeof(uint8_t));
    return command;
}

uint8_t Protocol::recvOpcode(Socket &socket) {
    uint8_t opcode = 0;
    socket.recv((char*)&opcode, sizeof(uint8_t));
    std::cout << "[PROTOCOL]: Opcode: " << opcode << std::endl;
    return opcode;
}

// devuelve true si pudo enviar todos los bytes sino devuelve false aka esta cerrado
bool Protocol::sendResponse(Socket &skt, int resp) {
    std::cout << "[PROTOCOL]: SE ENVIA RESP: " << resp << std::endl;
    int bytes = skt.send(reinterpret_cast<const char *>(&resp), sizeof(uint8_t));
    if (bytes == sizeof(uint8_t)){
        return true;
    } else {
        return false;
    }
}

uint16_t Protocol::recvHouse(Socket &skt) {
    uint16_t house_r = 0;
    skt.recv(reinterpret_cast<char *>(&house_r), sizeof(uint8_t));
    return house_r;
}

uint16_t Protocol::recvCurrent(Socket &skt) {
    uint16_t current = 0;
    skt.recv(reinterpret_cast<char *>(&current), sizeof(uint8_t));
    return current;
}



uint16_t Protocol::recvReq(Socket &skt) {
    uint16_t req = 0;
    skt.recv(reinterpret_cast<char *>(&req), sizeof(uint8_t));
    return req;
}

uint8_t Protocol::recvResponse(Socket &skt) {
    uint8_t resp = 0;
    skt.recv(reinterpret_cast<char *>(&resp), sizeof(uint8_t));
    return resp;
}

uint8_t Protocol::recvOneByte(Socket &socket) {
    uint8_t resp = 0;
    socket.recv((char*)&resp, sizeof(uint8_t));
    return resp;
}

uint16_t Protocol::recvTwoBytes(Socket &socket) {
    uint16_t resp = 0;
    socket.recv((char*)&resp, sizeof(uint16_t));
    return resp;
}

bool Protocol::sendOneByte(Socket &socket, uint8_t data) {
    int _send = socket.send((char *)&data, sizeof(uint8_t));
    if (_send < int(sizeof(uint8_t))) {
        return false;
    }
    return true;
}


bool Protocol::sendTwoBytes(Socket &socket, uint16_t data) {
    int _send = socket.send((char *)&data, sizeof(uint16_t));
    if (_send < int(sizeof(uint16_t))) {
        return false;
    }
    return true;
}


void Protocol::sendGameList(Socket &skt, const std::vector<std::vector<std::string>>& list) {
    if (list.empty()) {
        uint16_t empt = htons(0);
        skt.send(reinterpret_cast<const char *>(&empt), sizeof(uint16_t));
        return;
    } else {
        uint16_t count = (list.size());
        uint16_t count_s = htons(count);
        skt.send(reinterpret_cast<const char *>(&count_s), sizeof(uint16_t));
        int n = (int)list.size();
        for (int i = 0; i < n; i++) {
            uint16_t current = stoi(list[i][0]);
            uint16_t req = stoi(list[i][1]);
            std::string name = list[i][2];
            skt.send(reinterpret_cast<const char *>(&current), sizeof(uint8_t));
            skt.send(reinterpret_cast<const char *>(&req), sizeof(uint8_t));
            this->sendName(skt,name);
        }
    }
}

std::vector<std::vector<std::string>> Protocol::recvGameList(Socket &skt) {
    std::vector<std::vector<std::string>> list;
    uint16_t count = 0;
    skt.recv(reinterpret_cast<char *>(&count), sizeof(uint16_t));
    count = ntohs(count);
    if (count == 0) {
        return list;
    } else {
        for (int i = 0; i < count; i++) {
            list.push_back({std::to_string(recvCurrent(skt)),std::to_string(recvReq(skt)),recvName(skt)});
        }
        return list;
    }
}

void Protocol::recvCreate(Socket &socket, int &house, int &req, std::string &name) {
    house = recvHouse(socket);
    req = recvReq(socket);
    name = recvName(socket);
}

void Protocol::recvJoin(Socket &socket, std::string &name) {
    recvHouse(socket);
    name = recvName(socket);
}

void Protocol::sendUnit(Socket &socket, int type) {
    uint8_t aux = type;
    socket.send(reinterpret_cast<const char *>(&aux), sizeof(uint8_t));
}

void Protocol::sendUnit(Socket &socket, char type, int pos_x, int pos_y) {
    this->sendOneByte(socket, type);
    this->sendTwoBytes(socket, pos_x);
    this->sendTwoBytes(socket, pos_y);
}

void Protocol::sendPosition(Socket &socket, unsigned int x, unsigned int y) {
    std::cout << "Se envia Posicion: " << x << "," << y << std::endl;
    socket.send(reinterpret_cast<const char *>(&x), sizeof(uint16_t));
    socket.send(reinterpret_cast<const char *>(&y), sizeof(uint16_t));
}

uint16_t Protocol::recvPosition(Socket &socket) {
    uint16_t pos = 0;
    pos = this->recvTwoBytes(socket);
    return ntohs(pos);
}

char Protocol::recvUnitType(Socket &socket) {
    char type = 0;
    socket.recv(reinterpret_cast<char *>(&type), sizeof(uint8_t));
    return type;
}

void Protocol::sendBuild(Socket &socket, int build, int posX, int posY) {
    uint8_t aux = build;
    socket.send(reinterpret_cast<const char *>(&aux), sizeof(uint8_t));
    socket.send(reinterpret_cast<const char *>(&posX), sizeof(uint16_t));
    socket.send(reinterpret_cast<const char *>(&posY), sizeof(uint16_t));
}

void Protocol::sendBuild(Socket &socket, char build, int posX, int posY) {
    this->sendOneByte(socket, build);
    this->sendTwoBytes(socket, posX);
    this->sendTwoBytes(socket, posY);
}


void Protocol::operationRecv(Socket &socket, char &operation) {
    socket.recv(reinterpret_cast<char *>(&operation), sizeof(uint8_t));
}

char Protocol::typeUnidRecv(Socket &socket) {
    char typeUnid;
    socket.recv(reinterpret_cast<char *>(&typeUnid), sizeof(uint8_t));
    return typeUnid;
}

int Protocol::idUnidRecv(Socket &socket) {
    int id;
    socket.recv(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    return id;
}

void Protocol::sendInitGame(Socket &socket) {
    uint16_t flag_init = 10;
    socket.send((const char*)&flag_init, sizeof(uint16_t));
    std::cout << "[PROTOCOL]: SE ENVIA INIT_GAME: " << flag_init << std::endl;
}

bool Protocol::recvInitGame(Socket &socket) {
    uint16_t flag_recv = 0;
    socket.recv((char*)&flag_recv, sizeof(uint16_t));
    std::cout << "[PROTOCOL]: SE RECV INIT_GAME: " << flag_recv << std::endl;
    uint16_t flag_init = 10;
    if (flag_recv == flag_init) {
        return true;
    }
    return false;
}

void Protocol::sendMap(Socket &socket, std::vector<std::vector<char>>& map) {
    int rows = map.size();
    int cols = map[0].size();
    socket.send(reinterpret_cast<const char *>(&rows), sizeof(uint16_t));
    socket.send(reinterpret_cast<const char *>(&cols), sizeof(uint16_t));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char type = map[i][j];
            socket.send(reinterpret_cast<const char *>(&type), sizeof(uint8_t));}
    }
    std::cout << "[PROTOCOL] Mapa de " << rows << "x" << cols << " enviado." << std::endl;
}



std::vector<std::vector<char>> Protocol::recvMap(Socket &socket) {
    uint16_t rows, cols = 0;
    socket.recv(reinterpret_cast<char *>(&rows), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&cols), sizeof(uint16_t));
    std::vector <std::vector<char>> mapa
            ((uint16_t) rows, std::vector<char>((uint16_t) cols, '.'));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char type;
            socket.recv(reinterpret_cast<char *>(&type), sizeof(uint8_t));
            mapa[i][j] = type;
            //std::cout << "Se recive: " << type << std::endl;
        }
    }
    std::cout << "[PROTOCOL]: SE RECV MAPA " << std::endl;
    return mapa;
}

void Protocol::recvType(Socket &socket, char &type) {
    socket.recv(reinterpret_cast<char *>(&type), sizeof(uint8_t));
}

void Protocol::sendType(Socket &socket, int &actionType) {
    uint8_t aux = actionType;
    socket.send(reinterpret_cast<char *>(&aux), sizeof(uint8_t));
    std::cout << "Se envia Tipo Op: " << (int)aux << std::endl;
}

void Protocol::sendAction(Socket &socket, int &id, int &posX, int &posY) {
    socket.send(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&posX), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&posY), sizeof(uint16_t));
    std::cout << "Se envia: " << id << "," << posX << "," << posY << std::endl;
}

void Protocol::sendId(Socket &socket, int &id) {
    socket.send(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    std::cout << "Se envia: " << id << std::endl;
}

void Protocol::recvCountObject(Socket &socket, int &size) {
    socket.recv(reinterpret_cast<char *>(&size), sizeof(uint16_t));
}

void
Protocol::recvUnit(Socket &socket, int &id, char &player, bool &selectStatus, int &posX, int &posY, int &posActX,
                   int &posActY, int &life, bool &action) {
    socket.recv(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&player), sizeof(uint8_t));
    socket.recv(reinterpret_cast<char *>(&selectStatus), sizeof(uint8_t));
    socket.recv(reinterpret_cast<char *>(&posX), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&posY), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&posActX), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&posActY), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&life), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&action), sizeof(uint8_t));
}

void Protocol::recvBuild(Socket &socket, int &id, char &player, int &posX, int &posY, int &life) {
    socket.recv(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&player), sizeof(uint8_t));
    socket.recv(reinterpret_cast<char *>(&posY), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&posX), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&life), sizeof(uint16_t));
    std::cout << "Se recibe un edificio en la posicion: " << posX << "," << posY << std::endl;

}

void Protocol::sendCountObject(Socket &socket, int &countObject) {
    socket.send(reinterpret_cast<char *>(&countObject), sizeof(uint16_t));
}

void Protocol::enviar(Socket &socket) {
    uint8_t type = 1;
    uint8_t unitType = 2;
    uint16_t id = 0;
    uint8_t player = 1;
    uint8_t selectStatus = 1;
    uint16_t posX = 30;
    uint16_t posY = 30;
    uint16_t posActX = 0;
    uint16_t posActY = 0;
    uint16_t life = 0;
    uint8_t act = 0;
    socket.send(reinterpret_cast<char *>(&type), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&unitType), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&player), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&selectStatus), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&posX), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&posY), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&posActX), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&posActY), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&life), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&act), sizeof(uint8_t));
}

void Protocol::recvObjectType(Socket &socket, char &unitType) {
    socket.recv(reinterpret_cast<char *>(&unitType), sizeof(uint8_t));
}

void
Protocol::recvBotton(Socket &socket, int &id, char &player, int &constructionTime, bool &selectStatus, bool &ready) {
    socket.recv(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&player), sizeof(uint8_t));
    socket.recv(reinterpret_cast<char *>(&constructionTime), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&selectStatus), sizeof(uint8_t));
    socket.recv(reinterpret_cast<char *>(&ready), sizeof(uint8_t));
}

void Protocol::sendCommandSelect(Socket &socket, char &action, int &id) {
    socket.send(reinterpret_cast<char *>(&action), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    std::cout << "action(uint8_t) : " << (int)action << std::endl;
    std::cout << "id(uint16_t) : " << id << std::endl;
}

void Protocol::sendCommandMove(Socket &socket, char &action, int &id, int &posX, int &posY) {
    socket.send(reinterpret_cast<char *>(&action), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&posX), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&posY), sizeof(uint16_t));
    std::cout << "action(uint8_t) : " << (int)action << std::endl;
    std::cout << "id(uint16_t) : " << id << std::endl;
    std::cout << "posX(uint16_t) : " << posX << std::endl;
    std::cout << "posY(uint16_t) : " << posY << std::endl;
}

void Protocol::sendCommandBuildBuilding(Socket &socket, char &action, char &build, int &posX, int &posY) {
    socket.send(reinterpret_cast<char *>(&action), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&build), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&posY), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&posX), sizeof(uint16_t));
    std::cout << "action(uint8_t) : " << (int)action << std::endl;
    std::cout << "build type(uint8_t) : " << build << std::endl;
    std::cout << "posY(uint16_t) : " << posY << std::endl;
    std::cout << "posX(uint16_t) : " << posX << std::endl;
}

std::vector<std::string> Protocol::recvMapsId(Socket &socket) {
    std::vector<std::string> list;
    uint16_t count = 0;
    socket.recv(reinterpret_cast<char *>(&count), sizeof(uint16_t)); // recibo la cantidad de mapas creados
    count = ntohs(count);
    if (count == 0) {
        return list;
    } else {
        for (int i = 0; i < count; ++i) {
            list.push_back(recvName(socket));
        }
        return list;
    }
}

/*
* envio la cantidad de mapas
* 
*/
void Protocol::sendMapsId(Socket &socket, std::vector<std::string> maps_id){
    if (maps_id.empty()) { // si no hay mapas cargados (raro) envio 0
        uint16_t empt = htons(0);
        socket.send(reinterpret_cast<const char *>(&empt), sizeof(uint16_t));
        return;
    } else { // si la lista no esta vacia le envio la info de maps_id
        uint16_t total_id = maps_id.size(); // total de id
        uint16_t count_s = htons(total_id); // casteo host to netw
        socket.send(reinterpret_cast<const char *>(&count_s), sizeof(uint16_t)); // envio la cantidad de id's
        int n = (int)maps_id.size(); // cantidad int de id's
        for (int i = 0; i < n; i++){
            std::string map_id = maps_id[i];
            sendName(socket, map_id); // envio cada nombre de mapa
        }
    }
}



void Protocol::sendMapsCreated(Socket &socket, std::vector<MapDTO> maps) {
    uint16_t total = maps.size();
    uint16_t total_s = htons(total);
    socket.send((const char*)(&total_s), sizeof(uint16_t));
    // comienzo a enviar los mapas
    int total_maps_created = (int)maps.size();
    for (int i = 0; i < total_maps_created; i++) {
        MapDTO map = maps[i];
        socket.send((const char*)&map.rows, sizeof(uint16_t));
        socket.send((const char*)&map.cols, sizeof(uint16_t));
        socket.send((const char*)&map.max_players, sizeof(uint16_t));
    }
    
}

std::vector<std::vector<std::string>> Protocol::recvMapsCreated(Socket &socket) {
    std::vector<std::vector<std::string>> maps;
    uint16_t total = 0;
    socket.recv((char*)&total, sizeof(uint16_t));
    uint16_t n = ntohs(total);
    for (int i = 0; i < n; i++){
        uint16_t rows,cols,max_players = 0;
        socket.recv((char*)&rows,sizeof(uint16_t));
        socket.recv((char*)&cols,sizeof(uint16_t));
        socket.recv((char*)&max_players,sizeof(uint16_t));
        std::vector<std::string> map_dto = {std::to_string(rows),std::to_string(cols),std::to_string(max_players)};
        maps.push_back(map_dto);
    }
    std::cout << "[PROTOCOL]: SE RECV MAPA" << std::endl;
    return maps;
}

#define ESTABLISH_CONNECTION 9
#define BAD_CONNECTION 1
#define BAD_JOIN 1

void Protocol::sendEstablishConnection(Socket &socket) {
    this->sendTwoBytes(socket,ESTABLISH_CONNECTION);
}

bool Protocol::recvEstablishConnection(Socket &socket) {
    uint16_t connect = 0;
    socket.recv((char*)&connect, sizeof(uint16_t));
    std::cout << "[PROTOCOL]: SE RECV ESTAB_CONNECT: " << connect << std::endl;
    if (connect == ESTABLISH_CONNECTION) {
        return true;
    }
    return false;
}

void Protocol::sendCreateGameInvalid(Socket &socket) {
    this->sendTwoBytes(socket,BAD_CONNECTION);
}

void Protocol::sendAcceptPlayerInvalid(Socket &socket) {
    this->sendTwoBytes(socket,BAD_JOIN);
}

void Protocol::sendBuildings(Socket &socket, std::vector<BuildingDTO> buildings) {
    uint16_t total = buildings.size();
    socket.send((const char*)&total, sizeof(uint16_t));
    for (int i = 0; i < total; i++) {
        char type = 1;
        char build_type = buildings[i].type;
        uint16_t id = buildings[i].build_id;
        uint8_t player = buildings[i].build_id;
        uint16_t pos_x = (buildings[i].pos_x);
        uint16_t pos_y = (buildings[i].pos_y);
        uint16_t life = buildings[i].life;
        std::cout << "[PROTOCOL]: Enviando edificio: " << build_type << " en la pos: " << pos_x << "," << pos_y << " con vida " << life << std::endl;
        socket.send((const char *)&type, sizeof(uint8_t));
        socket.send((const char *)&build_type, sizeof(uint8_t));
        socket.send((const char *)&id, sizeof(uint16_t));
        socket.send((const char *)&player, sizeof(uint8_t));
        socket.send((const char *)&pos_x, sizeof(uint16_t));
        socket.send((const char *)&pos_y, sizeof(uint16_t));
        socket.send((const char *)&life, sizeof(uint16_t));
    }
}

void Protocol::sendUnits(Socket &socket, std::vector<UnitDTO> units) {
    uint16_t total = units.size(); // 2by 
    socket.send((const char*)&total, sizeof(uint16_t));
    for (int i = 0; i < total; i++) {
        auto unit = units[i];
        int player_id = unit.unit_id; // 2 by
        char unit_type = unit.type; // 8 bit
        int pos_x = unit.pos_x; // 2 by
        int pos_y = unit.pos_y; // 2 by
        int life = unit.life; // 2 by
        uint8_t unit_code = 0;
        sendOneByte(socket,unit_code);
        sendOneByte(socket,unit_type);
        sendTwoBytes(socket,player_id);
        sendOneByte(socket,player_id);
        sendOneByte(socket,player_id);
        sendTwoBytes(socket,pos_x);
        sendTwoBytes(socket,pos_y);
        sendTwoBytes(socket,pos_x);
        sendTwoBytes(socket,pos_y);
        sendTwoBytes(socket,life);
        sendOneByte(socket,unit_code);
    }
}


void Protocol::sendCommandCreateUnit(Socket &socket, char &action, char &unitType) {
    socket.send(reinterpret_cast<char *>(&action), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&unitType), sizeof(uint8_t));
    std::cout << "action(uint8_t) : " << (int)action << std::endl;
    std::cout << "unit type(uint8_t) : " << unitType << std::endl;
}
/*
std::vector<BuildingDTO> Protocol::recvInitBuildings(Socket &socket) {
    uint16_t total = 0;
    socket.recv((char*)&total, sizeof(uint16_t));
}*/