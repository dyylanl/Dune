#include "ConfigReader.h"
#include "../../Common/includes/Exceptions/Exception.h"

ConfigurationReader::ConfigurationReader(const std::string filename) :
        YAMLReader(filename) {}

ConfigurationReader::~ConfigurationReader() = default;

unsigned ConfigurationReader::getSpeedFactor() const {
    return this->config["speedFactor"].as<unsigned>();
}

unsigned ConfigurationReader::getBlockMovement() const {
    return this->config["blockMovement"].as<unsigned>();
}

unsigned ConfigurationReader::getRangeFactor() const {
    return this->config["rangeFactor"].as<unsigned>();
}

unsigned ConfigurationReader::getTimeFactor() const {
    return this->config["timeFactor"].as<unsigned>();
}

unsigned ConfigurationReader::getInitialGold() const {
    return this->config["initialGold"].as<unsigned>();
}

unsigned ConfigurationReader::getInitialEnergy() const {
    return this->config["initialEnergy"].as<unsigned>();
}

unsigned ConfigurationReader::getInitialMaxEnergy() const {
    return this->config["initialMaxEnergy"].as<unsigned>();
}

unsigned ConfigurationReader::getBuildingConstructionTime() const {
    return this->config["buildings"]["constructionTime"].as<unsigned>();
}

unsigned ConfigurationReader::getEnergyFor(Building::BuildingType buildingType) const {
    std::string buildingName;
    buildingName = this->parseType(buildingType);
    return this->config["buildings"][buildingName]["energy"].as<unsigned>();
}

unsigned ConfigurationReader::getCostFor(Building::BuildingType buildingType) const {
    std::string buildingName = this->parseType(buildingType);
    return this->config["buildings"][buildingName]["cost"].as<unsigned>();
}

unsigned ConfigurationReader::getHitPointsFor(Building::BuildingType buildingType) const {
    std::string buildingName = this->parseType(buildingType);
    return this->config["buildings"][buildingName]["hitPoints"].as<unsigned>();
}

unsigned ConfigurationReader::getWidthFor(Building::BuildingType buildingType) const {
    std::string buildingName = this->parseType(buildingType);
    return this->config["buildings"][buildingName]["width"].as<unsigned>();
}

unsigned ConfigurationReader::getHeightFor(Building::BuildingType buildingType) const {
    std::string buildingName = this->parseType(buildingType);
    return this->config["buildings"][buildingName]["height"].as<unsigned>();
}

unsigned ConfigurationReader::getSpiceCapacityFor(Building::BuildingType buildingType) const {
    std::string buildingName = this->parseType(buildingType);
    return this->config["buildings"][buildingName]["spiceCapacity"].as<unsigned>();
}

unsigned ConfigurationReader::getDamageFor(const WeaponType weaponType) const {
    std::string weaponName = this->parseType(weaponType);
    return this->config["weaponry"][weaponName]["damage"].as<unsigned>();
}

unsigned ConfigurationReader::getShootingRateFor(const WeaponType weaponType) const {
    std::string weaponName = this->parseType(weaponType);
    return this->config["weaponry"][weaponName]["shootingRate"].as<unsigned>();
}

unsigned ConfigurationReader::getBonusFor(const WeaponType weaponType) const {
    std::string weaponName = this->parseType(weaponType);
    return this->config["weaponry"][weaponName]["bonus"].as<unsigned>();
}

unsigned ConfigurationReader::getHitPointsFor(const Unit::UnitType unitType) const {
    std::string unitName = this->parseType(unitType);
    return this->config["units"][unitName]["hitPoints"].as<unsigned>();
}

unsigned ConfigurationReader::getRangeFor(const Unit::UnitType unitType) const {
    std::string unitName = this->parseType(unitType);
    return this->config["units"][unitName]["range"].as<unsigned>();
}

unsigned ConfigurationReader::getSpeedFor(const Unit::UnitType unitType) const {
    std::string unitName = this->parseType(unitType);
    return this->config["units"][unitName]["speed"].as<unsigned>();
}

unsigned ConfigurationReader::getTrainingTimeFor(const Unit::UnitType unitType) const {
    std::string unitName = this->parseType(unitType);
    return this->config["units"][unitName]["trainingTime"].as<unsigned>();
}

unsigned ConfigurationReader::getCostFor(const Unit::UnitType unitType) const {
    std::string unitName = this->parseType(unitType);
    return this->config["units"][unitName]["cost"].as<unsigned>();
}

unsigned ConfigurationReader::getSpiceCapacityFor(const Unit::UnitType unitType) const {
    std::string unitName = this->parseType(unitType);
    return this->config["units"][unitName]["spiceCapacity"].as<unsigned>();
}

unsigned ConfigurationReader::getFarmSpeed(const Unit::UnitType unitType) const {
    std::string unitName = this->parseType(unitType);
    return this->config["units"][unitName]["farmSpeed"].as<unsigned>();
}

unsigned ConfigurationReader::getLoadSpeed(const Unit::UnitType unitType) const {
    std::string unitName = this->parseType(unitType);
    return this->config["units"][unitName]["loadSpeed"].as<unsigned>();
}

std::string ConfigurationReader::parseType(const Building::BuildingType buildingType) const {
    std::string buildingName;
    switch (buildingType) {
        case Building::BuildingType::BARRACKS:
            buildingName = "barracks";
            break;
        case Building::BuildingType::CONSTRUCTION_CENTER:
            buildingName = "constructionCenter";
            break;
        case Building::BuildingType::HEAVY_FACTORY:
            buildingName = "heavyFactory";
            break;
        case Building::BuildingType::LIGHT_FACTORY:
            buildingName = "lightFactory";
            break;
        case Building::BuildingType::REFINERY:
            buildingName = "refinery";
            break;
        case Building::BuildingType::SILO:
            buildingName = "silo";
            break;
        case Building::BuildingType::WIND_TRAP:
            buildingName = "windTrap";
            break;
        case Building::BuildingType::PALACE:
            buildingName = "palace";
            break;
        default:
            throw Exception("Tipo de edificio no reconocido");
    }
    return buildingName;
}

std::string ConfigurationReader::parseType(const WeaponType weaponType) const {
    std::string weaponName;
    switch (weaponType) {
        case WeaponType::ASSAULT_RIFLE:
            weaponName = "assaultRifle";
            break;
        case WeaponType::CANNON:
            weaponName = "cannon";
            break;
        case WeaponType::ROCKET_LAUNCHER:
            weaponName = "rocketLauncher";
            break;
        case WeaponType::SMALL_CANNON:
            weaponName = "smallCannon";
            break;
        default:
            throw Exception("Tipo de arma no reconocida");
    }
    return weaponName;
}

std::string ConfigurationReader::parseType(const Unit::UnitType unitType) const {
    std::string unitName;
    switch (unitType) {
        case Unit::UnitType::HARVESTER:
            unitName = "harvester";
            break;
        case Unit::UnitType::LIGHT_INFANTRY:
            unitName = "lightInfantry";
            break;
        case Unit::UnitType::HEAVY_INFANTRY:
            unitName = "heavyInfantry";
            break;
        case Unit::UnitType::RAIDER:
            unitName = "raider";
            break;
        case Unit::UnitType::TANK:
            unitName = "tank";
            break;
        case Unit::UnitType::TRIKE:
            unitName = "trike";
            break;
        default:
            throw Exception("Tipo de unidad no reconocida");
    }
    return unitName;
}

std::list<std::string> ConfigurationReader::getAllPaths() const {
    std::list<std::string> paths;
    int total = this->config["total_maps"].as<int>();
    for (int i = 0; i < total; ++i) {
        std::string map_path = this->config["maps"][i].as<std::string>();
        paths.push_back(map_path);
    }
    return paths;
}

int ConfigurationReader::getFPS() {
    return this->config["ticks_per_sec"].as<int>();
}
