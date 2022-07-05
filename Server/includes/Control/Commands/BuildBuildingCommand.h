//
// Created by dypa on 19/06/22.
//



#ifndef DUNE_BUILDBUILDINGCOMMAND_H
#define DUNE_BUILDBUILDINGCOMMAND_H
#include "Command.h"

// Se recibe la peticion para crear una edificacion del tipo build_type en la posicion (pos_x,pos_y)

class BuildBuildingCommand : public Command {
private:
    const char build_type;
    const uint16_t pos_x;
    const uint16_t pos_y;

public:
    BuildBuildingCommand(const InstanceId caller,
                    const char build_type,
                    const uint16_t pos_x,
                    const uint16_t pos_y);
    ~BuildBuildingCommand();

    void exec(Model &model) override;
};

#endif //DUNE_BUILDBUILDINGCOMMAND_H
