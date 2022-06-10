#include "../../includes/Control/YAMLReader.h"

YAMLReader::YAMLReader(const std::string& filename) :
        config(YAML::LoadFile(filename)) {}

std::string YAMLReader::getPort() {
    return this->config["port"].as<std::string>();
}
