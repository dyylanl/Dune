#ifndef __MAP_READER_H__
#define __MAP_READER_H__

#include "YAMLReader.h"

class MapReader : public YAMLReader {
public:
    explicit MapReader(std::string filename);
    unsigned getRows() const;
    unsigned getCols() const;
    std::vector<std::vector<char>> getMap();
    ~MapReader();

};

#endif	// __MAP_READER_H__
