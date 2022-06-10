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

void Protocol::sendUnit(Socket &socket, char type) {
    socket.send(reinterpret_cast<const char *>(&type), sizeof(uint8_t));
}

void Protocol::sendPosition(Socket &socket, unsigned int x, unsigned int y) {
    socket.send(reinterpret_cast<const char *>(&x), sizeof(uint16_t));
    socket.send(reinterpret_cast<const char *>(&y), sizeof(uint16_t));
}

std::vector<int> Protocol::recvPosition(Socket &socket) {
    int x,y=0;
    std::vector<int> position;
    socket.recv(reinterpret_cast<char *>(&x), sizeof(uint16_t));
    socket.recv(reinterpret_cast<char *>(&y), sizeof(uint16_t));
    position.push_back((int)x);
    position.push_back((int)y);
    return position;
}

char Protocol::recvUnitType(Socket &socket) {
    char type = 0;
    socket.recv(reinterpret_cast<char *>(&type), sizeof(uint8_t));
    return type;
}
