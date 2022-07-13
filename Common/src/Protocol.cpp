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


uint8_t Protocol::recvCommand(Socket &skt) {
    return recvOneByte(skt);
}

// devuelve true si pudo enviar todos los bytes sino devuelve false aka esta cerrado
bool Protocol::sendResponse(Socket &skt, int resp) {
    int bytes = skt.send(reinterpret_cast<const char *>(&resp), sizeof(uint8_t));
    if (bytes == sizeof(uint8_t)){
        return true;
    } else {
        return false;
    }
}

uint8_t Protocol::recvHouse(Socket &skt) {
    return recvOneByte(skt);
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
    return ntohs(resp);
}

bool Protocol::sendOneByte(Socket &socket, uint8_t data) {
    int _send = socket.send((char *)&data, sizeof(uint8_t));
    if (_send < int(sizeof(uint8_t))) {
        return false;
    }
    return true;
}


bool Protocol::sendTwoBytes(Socket &socket, uint16_t data) {
    uint16_t data_send = htons(data);
    int bytes_send = socket.send((char *)&data_send, sizeof(uint16_t));
    if (bytes_send < int(sizeof(uint16_t))) {
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

/*
void Protocol::sendUnit(Socket &socket, char type, int pos_x, int pos_y) {
    this->sendOneByte(socket, type);
    this->sendTwoBytes(socket, pos_x);
    this->sendTwoBytes(socket, pos_y);
}
*/

uint16_t Protocol::recvPosition(Socket &socket) {
    return this->recvTwoBytes(socket);
}

#define OBJECT_BUILDING 1
#define INIT_GAME 10

void Protocol::sendInitGame(Socket &socket) {
    this->sendTwoBytes(socket,INIT_GAME);
}

bool Protocol::recvInitGame(Socket &socket) {
    uint16_t flag_recv = 0;
    socket.recv((char*)&flag_recv, sizeof(uint16_t));
    flag_recv = ntohs(flag_recv);
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
    return mapa;
}



void Protocol::sendUnit(Socket &socket, UnitDTO unit) {
    //uint16_t cantObj = 1; //Cant de Objetos
    uint8_t type = 0;  //Tipo De Objeto
    //this->sendTwoBytes(socket, cantObj);
    this->sendOneByte(socket, type);
    this->sendOneByte(socket, unit.type);
    this->sendTwoBytes(socket, unit.unit_id);
    this->sendOneByte(socket, unit.player_id);
    this->sendOneByte(socket, unit.selected);
    this->sendTwoBytes(socket, unit.pos_x);
    this->sendTwoBytes(socket, unit.pos_y);
    this->sendTwoBytes(socket, unit.pos_x);
    this->sendTwoBytes(socket, unit.pos_y);
    this->sendTwoBytes(socket, unit.life);
    this->sendOneByte(socket, true);
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

void Protocol::sendBuild(Socket &socket, BuildingDTO build) {
    //uint16_t total = 1; // esto es porque el cliente lo necesita asi \_(X*X)_/
    //this->sendTwoBytes(socket,total);
    this->sendOneByte(socket,OBJECT_BUILDING);
    this->sendOneByte(socket, build.type);
    this->sendTwoBytes(socket, build.build_id);
    this->sendOneByte(socket, build.player_id); // player id
    this->sendTwoBytes(socket, build.pos_x*BLOCK_HEIGHT);
    this->sendTwoBytes(socket, build.pos_y*BLOCK_WIDTH);
    this->sendTwoBytes(socket, build.life);
}

void Protocol::recvBuild(Socket &socket, int &id, char &player, int &posX, int &posY, int &life) {
    socket.recv(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&player), sizeof(uint8_t));
    socket.recv(reinterpret_cast<char *>(&posY), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&posX), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&life), sizeof(uint16_t));
    id = ntohs(id);
    posY = ntohs(posY);
    posX = ntohs(posX);
    life = ntohs(life);

}

void Protocol::sendCountObject(Socket &socket, int &countObject) {
    socket.send(reinterpret_cast<char *>(&countObject), sizeof(uint16_t));
}


void Protocol::recvObjectType(Socket &socket, char &unitType) {
    socket.recv(reinterpret_cast<char *>(&unitType), sizeof(uint8_t));
}

void Protocol::sendCommandSelect(Socket &socket, char &action, int &id) {
    socket.send(reinterpret_cast<char *>(&action), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&id), sizeof(uint16_t));
}

void Protocol::sendCommandMove(Socket &socket, char &action, int &id, int &posX, int &posY) {
    socket.send(reinterpret_cast<char *>(&action), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&posX), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&posY), sizeof(uint16_t));
}

void Protocol::sendCommandBuildBuilding(Socket &socket, char &action, char &build, int &posX, int &posY) {
    socket.send(reinterpret_cast<char *>(&action), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&build), sizeof(uint8_t));
    posY = htons(posY);
    posX = htons(posX);
    socket.send(reinterpret_cast<char *>(&posY), sizeof(uint16_t));
    socket.send(reinterpret_cast<char *>(&posX), sizeof(uint16_t));
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
    connect = htons(connect);
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

void Protocol::sendCommandCreateUnit(Socket &socket, char &action, char &unitType) {
    socket.send(reinterpret_cast<char *>(&action), sizeof(uint8_t));
    socket.send(reinterpret_cast<char *>(&unitType), sizeof(uint8_t));
}

uint16_t Protocol::recvCountObject(Socket &socket) {
    return recvTwoBytes(socket);
}

uint8_t Protocol::recvType(Socket &socket) {
    return recvOneByte(socket);
}
