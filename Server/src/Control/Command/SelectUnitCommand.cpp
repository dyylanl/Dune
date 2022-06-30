#include "../../../includes/Control/Commands/SelectUnitCommand.h"

//
// Created by dypa on 19/06/22.
//

SelectUnitCommand::SelectUnitCommand(const InstanceId caller,
                                     const uint16_t pos_x,
                                     const uint16_t pos_y) :

        Command(caller),
        pos_x(pos_x),
        pos_y(pos_y) {}

SelectUnitCommand::~SelectUnitCommand() = default;

void SelectUnitCommand::exec() {
    std::cout << "Seleccionando unidad en: " << pos_x << pos_y << std::endl;
}
