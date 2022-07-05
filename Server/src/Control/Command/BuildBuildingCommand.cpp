#include "../../../includes/Control/Commands/BuildBuildingCommand.h"



BuildBuildingCommand::BuildBuildingCommand(const InstanceId caller,
                                     const char build_type1,
                                     const uint16_t pos_x1,
                                     const uint16_t pos_y1) :
        Command(caller),
        build_type(build_type1),
        pos_x(pos_x1),
        pos_y(pos_y1) {}

BuildBuildingCommand::~BuildBuildingCommand() = default;

void BuildBuildingCommand::exec(Map &map) {
    map.putBuilding(/*caller,*/build_type,pos_x,pos_y);
}