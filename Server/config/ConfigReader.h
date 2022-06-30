#ifndef __CONFIGURATION_READER_H__
#define __CONFIGURATION_READER_H__

#include <string>
#include "../../Common/includes/Exceptions/Exception.h"
#include "YAMLReader.h"


class ConfigurationReader : public YAMLReader {
public:
    explicit ConfigurationReader(const std::string filename);
    ~ConfigurationReader();
    
    //map
    int getTotalMaps() const;
    std::list<std::string> getAllPaths() const;
    std::string getMapPath() const;
    int getFPS() const;
    
    
};

#endif	// __CONFIGURATION_READER_H__
