//
// Created by dypa on 19/06/22.
//

#ifndef DUNE_SELECTUNITCOMMAND_H
#define DUNE_SELECTUNITCOMMAND_H
#include "Command.h"

// Se recibe un click derecho por lo tanto intenta seleccionar la unidad en la posicion (pos_x,pos_y)
class SelectUnitCommand : public Command {
private:
    const uint16_t pos_x;
    const uint16_t pos_y;

public:
    SelectUnitCommand(InstanceId caller,
                      uint16_t pos_x,
                   uint16_t pos_y);
    ~SelectUnitCommand() override;

    void exec(Model &model) override;
};
#endif //DUNE_SELECTUNITCOMMAND_H
