#ifndef __COMMAND_H__
#define __COMMAND_H__
//-----------------------------------------------------------------------------
#include <exception>
//-----------------------------------------------------------------------------
#include "../../../../Common/includes/BlockingQueue.h"
#include "../../../../Common/includes/Protocol.h"
#include "../../../../Common/includes/Socket/Socket.h"
#include "../../../../Server/includes/defs.h"
#include "../../Model/Model.h"
//-----------------------------------------------------------------------------


class Command {
protected:
    const InstanceId caller;

public:
    Command(const InstanceId caller);
    Command(const Command&) = delete;
    Command& operator=(const Command&) = delete;
    Command(Command&& other) = delete;
    Command& operator=(Command&& other) = delete;
    const InstanceId getCaller() const;

    //-------------------------------------------------------------------------

    virtual void exec(Model &model) = 0;

    virtual ~Command();
};

class CommandFactory {
public:
    static Command* newCommand(InstanceId caller, uint8_t opcode,
                               Socket& socket);
};

class UnknownCommandException : public std::exception {
public:
    virtual const char* what() const noexcept;
};

//-----------------------------------------------------------------------------

#endif  // __COMMAND_H__
