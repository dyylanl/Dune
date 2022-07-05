
#include "../../../includes/Control/Commands/CreateUnitCommand.h"

//
// Created by dypa on 19/06/22.
//



CreateUnitCommand::CreateUnitCommand(const InstanceId caller, char unit_type1) :

        Command(caller),
        unit_type(unit_type1){}

CreateUnitCommand::~CreateUnitCommand() = default;

void CreateUnitCommand::exec(Model &model) {
    model.putUnit(caller, unit_type);  // todo: posicion harcodeada para probar
}
