
#include "../../../includes/Control/Commands/MoveUnitCommand.h"

//
// Created by dypa on 19/06/22.
//



MoveUnitCommand::MoveUnitCommand(const InstanceId caller,
                                     const uint16_t pos_x,
                                     const uint16_t pos_y) :

        Command(caller),
        pos_x(pos_x),
        pos_y(pos_y) {}

MoveUnitCommand::~MoveUnitCommand() = default;

void MoveUnitCommand::exec(Map &map) {
    std::cout << "Moviendo unidad a: " << pos_x << "," << pos_y << std::endl;
}
