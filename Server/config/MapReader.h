#ifndef __MAP_READER_H__
#define __MAP_READER_H__

#include "YAMLReader.h"
#include "../includes/Model/Buildings/Building.h"
#include "../includes/defs.h"

class MapReader : public YAMLReader {
private:
    std::string filename;
public:
    explicit MapReader(std::string filename);
    unsigned getRows() const;
    unsigned getCols() const;
    std::vector<std::vector<char>> getMap();
    std::vector<Building> getBuildings();
    unsigned getReqPlayers();
    ~MapReader();

};

#endif	// __MAP_READER_H__
