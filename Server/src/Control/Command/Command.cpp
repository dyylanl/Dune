#include <vector>
//-----------------------------------------------------------------------------
#include "../../../includes/Control/Commands/Command.h"
//-----------------------------------------------------------------------------
#include "../../../../Common/includes/Exceptions/Exception.h"
#include "../../../../Common/includes/Protocol.h"
#include "../../../includes/Control/Commands/SelectUnitCommand.h"
#include "../../../includes/Control/Commands/MoveUnitCommand.h"
#include "../../../includes/Control/Commands/BuildBuildingCommand.h"
#include "../../../includes/Control/Commands/CreateUnitCommand.h"
//-----------------------------------------------------------------------------


Command::Command(const InstanceId caller) : caller(caller) {}

Command::~Command() {}

const InstanceId Command::getCaller() const {
    return this->caller;
}

Command* CommandFactory::newCommand(InstanceId caller, uint8_t opcode,
                                    Socket& socket) {
    Protocol protocol;
    switch (opcode) {
        case SELECT_UNIT_COMMAND: { //5
            uint16_t pos_x = protocol.recvPosition(socket);
            uint16_t pos_y = protocol.recvPosition(socket);
            return new SelectUnitCommand(caller, pos_x, pos_y);
        }

        case MOVE_UNIT_COMMAND: { // 6
            uint16_t pos_x = protocol.recvPosition(socket);
            uint16_t pos_y = protocol.recvPosition(socket);
            return new MoveUnitCommand(caller, pos_x, pos_y);
        }

        case BUILD_BUILDING_COMMAND: {  // 7
            char building_type = protocol.recvOneByte(socket);
            uint16_t pos_x = protocol.recvPosition(socket);
            uint16_t pos_y = protocol.recvPosition(socket);
            return new BuildBuildingCommand(caller, building_type, pos_x, pos_y);
        }

        case CREATE_UNIT_COMMAND: {  // 8
            char unit_type = protocol.recvOneByte(socket);
            return new CreateUnitCommand(caller, unit_type);
        }

        case 10: {  // esto esta harcodeado para probar ... 
            std::cout << "Se creo el comando 10" << std::endl;
        }

        default: {
            throw UnknownCommandException();
        }
    }
}

const char* UnknownCommandException::what() const noexcept {
    return "Unknown command received.\n";
}