#ifndef __CONFIGURATION_READER_H__
#define __CONFIGURATION_READER_H__

#include <string>
#include "YAMLReader.h"
#include "../includes/Model/Buildings/Building.h"
#include "../includes/Model/Units/Unit.h"
#include "../includes/defs.h"

class ConfigurationReader : public YAMLReader {
private:
    std::string parseType(const Building::BuildingType buildingType) const;
    std::string parseType(const WeaponType weaponType) const;
    std::string parseType(const Unit::UnitType unitType) const;
public:
    explicit ConfigurationReader(const std::string filename);
    ~ConfigurationReader();

    // map paths
    std::list<std::string> getAllPaths() const;

    int getFPS();
    std::string getPathWithId(Id map_id);

    // game
    unsigned getSpeedFactor() const;
    unsigned getBlockMovement() const;
    unsigned getRangeFactor() const;
    unsigned getTimeFactor() const;
    unsigned getInitialGold() const;
    unsigned getInitialEnergy() const;
    unsigned getInitialMaxEnergy() const;

    // buildings
    unsigned getBuildingConstructionTime() const;
    unsigned getEnergyFor(const Building::BuildingType buildingType) const;
    unsigned getCostFor(const Building::BuildingType buildingType) const;
    unsigned getHitPointsFor(const Building::BuildingType buildingType) const;
    unsigned getWidthFor(const Building::BuildingType buildingType) const;
    unsigned getHeightFor(const Building::BuildingType buildingType) const;
    unsigned getSpiceCapacityFor(const Building::BuildingType buildingType) const;

    // weapons
    unsigned getDamageFor(const WeaponType weaponType) const;
    unsigned getShootingRateFor(const WeaponType weaponType) const;
    unsigned getBonusFor(const WeaponType weaponType) const;

    // units
    unsigned getHitPointsFor(const Unit::UnitType unitType) const;
    unsigned getRangeFor(const Unit::UnitType unitType) const;
    unsigned getSpeedFor(const Unit::UnitType unitType) const;
    unsigned getTrainingTimeFor(const Unit::UnitType unitType) const;
    unsigned getCostFor(const Unit::UnitType unitType) const;
    unsigned getSpiceCapacityFor(const Unit::UnitType unitType) const;
    unsigned getFarmSpeed(const Unit::UnitType unitType) const;
    unsigned getLoadSpeed(const Unit::UnitType unitType) const;
};

#endif	// __CONFIGURATION_READER_H__
