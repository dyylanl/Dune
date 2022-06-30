//
// Created by dypa on 19/06/22.
//

#ifndef DUNE_CREATEUNITCOMMAND_H
#define DUNE_CREATEUNITCOMMAND_H


#include "Command.h"

// Se recibe la peticion para crear una unidad del tipo unit_type
class CreateUnitCommand : public Command {
private:
    const char unit_type;

public:
    CreateUnitCommand(const InstanceId caller,
                         const char unit_type);

    ~CreateUnitCommand();

    void exec(Map &map) override;
};

#endif //DUNE_CREATEUNITCOMMAND_H
