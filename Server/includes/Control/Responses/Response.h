#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <string>
#include "../../../../Common/includes/Socket/Socket.h"
#include "../../defs.h"
#include "../../../../Common/includes/Protocol.h"


class Response {
private:
    uint8_t message_type;
    std::string reply;
    Protocol protocol;
public:
    Response(const uint8_t message_type, const std::string& reply);
    Response(const Response& other);
    Response& operator=(const Response& other);
    //Devuelve si se pudo enviar. */
    bool send(const InstanceId sender, const Socket& peer);
    virtual ~Response();
};

#endif  //__REPLY_H__
