
#include "../../../includes/Control/Commands/CreateUnitCommand.h"

//
// Created by dypa on 19/06/22.
//



CreateUnitCommand::CreateUnitCommand(const InstanceId caller, char unit_type1) :

        Command(caller),
        unit_type(unit_type1){}

CreateUnitCommand::~CreateUnitCommand() = default;

void CreateUnitCommand::exec(Map &map) {
    map.putUnit(caller,unit_type,5,5);  // todo: posicion harcodeada para probar
    std::cout << "Creando unidad del tipo: " << unit_type <<std::endl;
}
