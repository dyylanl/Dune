//
// Created by dypa on 19/06/22.
//

#ifndef DUNE_MOVEUNITCOMMAND_H
#define DUNE_MOVEUNITCOMMAND_H
#include "Command.h"

// Se recibe un click izquierdo por lo tanto intenta mover todas las unidades seleccionadas a la posicion (pos_x,pos_y)
class MoveUnitCommand : public Command {
private:
    const uint16_t pos_x;
    const uint16_t pos_y;

public:
    MoveUnitCommand(const InstanceId caller,
                      const uint16_t pos_x,
                      const uint16_t pos_y);
    ~MoveUnitCommand();

    void exec(Game& game) override;
};
#endif //DUNE_MOVEUNITCOMMAND_H
