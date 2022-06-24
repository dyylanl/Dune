#ifndef __MAP_READER_H__
#define __MAP_READER_H__

#include "YAMLReader.h"
#include "../includes/Model/Buildings/Building.h"

class MapReader : public YAMLReader {
public:
    explicit MapReader(std::string filename);
    unsigned getRows() const;
    unsigned getCols() const;
    std::vector<std::vector<char>> getMap();
    std::vector<Building> getBuildings();
    ~MapReader();

};

#endif	// __MAP_READER_H__
