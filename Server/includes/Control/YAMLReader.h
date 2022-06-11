#ifndef YAML_READER_H__
#define YAML_READER_H__

#include <yaml-cpp/yaml.h>

struct Build{
    std::string type;
    int energy;
    int capacity;
    int cost;
    int x,y;
    int hit_points;
};

class YAMLReader {
public:
    explicit YAMLReader(const std::string& filename);
    std::string getPort() const;
    int getX();
    int getY();
    int getSpeedFactor();
    int getInitialGold();
    int getInitialEnergy();
    void getBuild(const std::string& build_name);
    int getFPS();
    ~YAMLReader() = default;

protected:
    YAML::Node config;
};

#endif  // YAML_READER_H__
