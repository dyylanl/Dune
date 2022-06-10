#ifndef YAML_READER_H__
#define YAML_READER_H__

#include <yaml-cpp/yaml.h>

class YAMLReader {
public:
    explicit YAMLReader(const std::string& filename);
    std::string getPort() const;
    ~YAMLReader() = default;

protected:
    YAML::Node config;
};

#endif  // YAML_READER_H__
