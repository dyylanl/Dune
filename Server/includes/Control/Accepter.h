#ifndef __ACCEPTER_H__
#define __ACCEPTER_H__

#include <atomic>
#include <exception>
#include <list>
#include <string>
//-----------------------------------------------------------------------------
#include "../../../Common/includes/Exceptions/ClosedSocketException.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../../../Common/includes/Thread.h"
//-----------------------------------------------------------------------------
#include "ClientLogin.h"
#include "NewConnection.h"
//-----------------------------------------------------------------------------

class Accepter : public Thread {
private:
    Socket socket;
    YAMLReader& reader;
    NonBlockingQueue<NewConnection*>& new_connections;
    std::atomic_bool keep_accepting;
    std::list<ClientLogin*> client_logins;

    void _acceptClient();
    void _joinFinishedLogins();
    void _joinLogins();

public:
    Accepter(const std::string& port, const int max_clients_queued,
             YAMLReader& reader,
             NonBlockingQueue<NewConnection*>& new_connections);
    Accepter(const Accepter&) = delete;
    Accepter& operator=(const Accepter&) = delete;
    Accepter(Accepter&& other) = delete;
    Accepter& operator=(Accepter&& other) = delete;
    void run() override;
    void stop();
    ~Accepter();
};


#endif  // __ACCEPTER_H__
