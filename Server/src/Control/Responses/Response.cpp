#include "../../../includes/Control/Responses/Response.h"


Response::Response(const uint8_t message_type, const std::string& reply)
        : message_type(message_type), reply(reply) {}

Response::~Response() {}

Response::Response(const Response& other) {
    this->message_type = other.message_type;
    this->reply = other.reply;
}

Response& Response::operator=(const Response& other) {
    this->message_type = other.message_type;
    this->reply = other.reply;
    return *this;
}

bool Response::send(const InstanceId sender, const Socket& peer) {
    if (!(protocol.sendResponse((Socket &)(peer), message_type))) {
        return false;
    }
    if (!(protocol.sendName((Socket &)peer, reply))) {
        return false;
    }
    return true;
}
