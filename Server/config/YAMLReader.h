#ifndef __YAML_READER_H__
#define __YAML_READER_H__

#include <yaml-cpp/yaml.h>
#include <string>

class YAMLReader {
public:
    explicit YAMLReader(const std::string filename);

    virtual ~YAMLReader() = default;

protected:
    YAML::Node config;
};

#endif  // __YAML_READER_H__
