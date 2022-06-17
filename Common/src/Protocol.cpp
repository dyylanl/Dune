#include "../includes/Protocol.h"

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

std::string Protocol::recvName(Socket &skt, uint16_t name_len) {
    std::vector<char> name(name_len+1);
    int bytes_recv = skt.recv(name.data(), name_len);
    name[bytes_recv] = 0;
    std::string game_name = name.data();
    return game_name;
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

uint16_t Protocol::recvCommand(Socket &skt) {
    uint16_t command = 0;
    skt.recv(reinterpret_cast<char *>(&command), sizeof(uint8_t));
    return command;
}

void Protocol::sendResponse(Socket &skt, int resp) {
    skt.send(reinterpret_cast<const char *>(&resp), sizeof(uint8_t));
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

uint16_t Protocol::recvNameLen(Socket &skt) {
    uint16_t len = 0;
    skt.recv(reinterpret_cast<char *>(&len), sizeof(uint16_t));
    return ntohs(len);
}

uint16_t Protocol::recvReq(Socket &skt) {
    uint16_t req = 0;
    skt.recv(reinterpret_cast<char *>(&req), sizeof(uint8_t));
    return req;
}

uint16_t Protocol::recvResponse(Socket &skt) {
    uint16_t resp = 0;
    skt.recv(reinterpret_cast<char *>(&resp), sizeof(uint8_t));
    return resp;
}

void Protocol::sendGameList(Socket &skt, const std::vector<std::string>& list) {
    if (list.empty()) {
        uint16_t empt = htons(0);
        skt.send(reinterpret_cast<const char *>(&empt), sizeof(uint16_t));
        return;
    } else {
        uint16_t count = stoi(list[0]);
        uint16_t count_s = htons(count);
        skt.send(reinterpret_cast<const char *>(&count_s), sizeof(uint16_t));
        int n = (int)list.size();
        for (int i = 1; i <= n-3; i = i+4) {
            uint16_t current = stoi(list[i]);
            uint16_t req = stoi(list[i+1]);
            uint16_t game_name_len = stoi(list[i+2]);
            std::string name = list[i+3];
            game_name_len = htons(game_name_len);
            skt.send(reinterpret_cast<const char *>(&current), sizeof(uint8_t));
            skt.send(reinterpret_cast<const char *>(&req), sizeof(uint8_t));
            skt.send(reinterpret_cast<const char *>(&game_name_len), sizeof(uint16_t));
            skt.send(name.c_str(), (name).size());
        }
    }
}

std::vector<std::string> Protocol::recvGameList(Socket &skt) {
    std::vector<std::string> list;
    uint16_t count = 0;
    skt.recv(reinterpret_cast<char *>(&count), sizeof(uint16_t));
    count = ntohs(count);
    if (count == 0) {
        return list;
    } else {
        for (int i = 0; i < count; ++i) {
            list.push_back(std::to_string(recvCurrent(skt)));
            list.push_back(std::to_string(recvReq(skt)));
            int len = recvNameLen(skt);
            list.push_back(recvName(skt, len));
        }
        return list;
    }
}

void Protocol::recvCreate(Socket &socket, int &house, int &req, std::string &name) {
    house = recvHouse(socket);
    req = recvReq(socket);
    int name_len = recvNameLen(socket);
    name = recvName(socket, name_len);
}

void Protocol::recvJoin(Socket &socket, std::string &name) {
    recvHouse(socket);
    int game_name_len = recvNameLen(socket);
    name = recvName(socket, game_name_len);
}

void Protocol::sendUnit(Socket &socket, int &type) {
    uint8_t aux = type;
    socket.send(reinterpret_cast<const char *>(&aux), sizeof(uint8_t));
}

void Protocol::sendPosition(Socket &socket, unsigned int x, unsigned int y) {
    socket.send(reinterpret_cast<const char *>(&x), sizeof(uint16_t));
    socket.send(reinterpret_cast<const char *>(&y), sizeof(uint16_t));
}

std::vector<int> Protocol::recvPosition(Socket &socket) {
    int x,y=0;
    std::vector<int> pos;
    socket.recv(reinterpret_cast<char *>(&x), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&y), sizeof(uint16_t));
    pos.emplace_back(x);
    pos.emplace_back(y);
    return pos;
}

char Protocol::recvUnitType(Socket &socket) {
    char type = 0;
    socket.recv(reinterpret_cast<char *>(&type), sizeof(uint8_t));
    return type;
}

void Protocol::sendBuild(Socket &socket, int &build, int &posX, int &posY) {
    uint8_t aux = build;
    socket.send(reinterpret_cast<const char *>(&aux), sizeof(uint8_t));
    socket.send(reinterpret_cast<const char *>(&posX), sizeof(uint16_t));
    socket.send(reinterpret_cast<const char *>(&posY), sizeof(uint16_t));
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

void Protocol::sendMap(Socket &socket, std::vector<std::vector<char>> map) {
    int rows = map.size();
    int cols = map[0].size();
    std::cout << "rows: " << rows << "\ncols: " << cols << std::endl;
    socket.send(reinterpret_cast<const char *>(&rows), sizeof(uint16_t));
    socket.send(reinterpret_cast<const char *>(&cols), sizeof(uint16_t));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char type = map[i][j];
            socket.send(reinterpret_cast<const char *>(&type), sizeof(uint8_t));
        }
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
        }
    }
    return mapa;
}

void Protocol::sendName(Socket &socket, std::string name) {
    uint16_t len_name = name.size();
    socket.send(reinterpret_cast<const char *>(&len_name), sizeof(uint8_t));
    socket.send(name.c_str(), name.size());

}

void
Protocol::recvUnit(Socket &socket,int &id, std::string &unit, int &player, int &posX, int &posY, int &posActX, int &posActY, int &life,
                   bool &action) {
    int unitType = 0;
    uint8_t act;
    socket.recv(reinterpret_cast<char *>(&id), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&unitType), sizeof(uint8_t));
    if(unitType == 1) {
        unit = "Infantería Ligera";
    }
    if(unitType == 2) {
        unit = "Infantería Pesada";
    }
    if(unitType == 3) {
        unit = "Fremen";
    }
    if(unitType == 4) {
        unit = "Sardaukar";
    }
    if(unitType == 5) {
        unit = "Trike";
    }
    if(unitType == 6) {
        unit = "Tanque Sonico";
    }
    if(unitType == 7) {
        unit = "Raider";
    }
    if(unitType == 8) {
        unit = "Desviador";
    }
    if(unitType == 6) {
        unit = "Tanque";
    }
    if(unitType == 7) {
        unit = "Devastador";
    }
    if(unitType == 8) {
        unit = "Cosechadora";
    }
    socket.recv(reinterpret_cast<char *>(&player), sizeof(uint8_t));
    socket.recv(reinterpret_cast<char *>(&posX), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&posY), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&posActX), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&posActY), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&life), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&act), sizeof(uint8_t));
    if (act == 1) action = true;
    else action = false;
    std::cout << "Se recibe: " << "(" << posX << "," << posY << ")" << std::endl;
}

void Protocol::recvType(Socket &socket, int &type) {
    socket.recv(reinterpret_cast<char *>(&type), sizeof(uint8_t));
}

void Protocol::sendType(Socket &socket, int &actionType) {
    uint8_t aux = actionType;
    socket.send(reinterpret_cast<char *>(&aux), sizeof(uint8_t));
    std::cout << "Se envia: " << (int)aux << std::endl;
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
