#ifndef __MAP_READER_H__
#define __MAP_READER_H__

#include "YAMLReader.h"
#include "../includes/defs.h"
#include "../includes/Model/DTOs/BuildingDTO.h"
#include "../includes/Model/Buildings/ConstructionCenter.h"

class MapReader : public YAMLReader {
public:
    explicit MapReader(std::string filename);
    unsigned getRows() const;
    unsigned getCols() const;
    std::vector<std::vector<char>> getMap();
    std::vector<BuildingDTO> getBuildings();
    ConstructionCenter* getConstructionCenterFor(InstanceId id);
    unsigned getReqPlayers();
    int getTotalBuildings();
    ~MapReader();

};

#endif	// __MAP_READER_H__
