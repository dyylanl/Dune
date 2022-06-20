#include "YAMLReader.h"
#include <string>

YAMLReader::YAMLReader(const std::string filename) :
        config(YAML::LoadFile(filename)) {}


/*


std::string YAMLReader::getPort() {
    return this->config["port"].as<std::string>();
}

int YAMLReader::getFPS() {
    return this->config["ticks_per_second"].as<int>();
}
*/
