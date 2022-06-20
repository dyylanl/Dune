#include "GameConfig.h"
#include <string>

std::unique_ptr<GameConfiguration> GameConfiguration::instance(nullptr);

GameConfiguration::GameConfiguration(const ConfigurationReader& config) :

        speedFactor(config.getSpeedFactor()),
        blockMovement(config.getBlockMovement()),
        rangeFactor(config.getRangeFactor()),
        timeFactor(config.getTimeFactor()),
        initialGold(config.getInitialGold()),
        initialEnergy(config.getInitialEnergy()),
        initialMaxEnergy(config.getInitialMaxEnergy()),
        buildingConstructionTime(config.getBuildingConstructionTime() * timeFactor),
        constructionYardEnergy(config.getEnergyFor(Building::BuildingType::CONSTRUCTION_YARD)),
        constructionYardCost(config.getCostFor(Building::BuildingType::CONSTRUCTION_YARD)),
        constructionYardHitPoints(config.getHitPointsFor(Building::BuildingType::CONSTRUCTION_YARD)),
        constructionYardWidth(config.getWidthFor(Building::BuildingType::CONSTRUCTION_YARD)),
        constructionYardHeight(config.getHeightFor(Building::BuildingType::CONSTRUCTION_YARD)),
        windTrapEnergy(config.getEnergyFor(Building::BuildingType::WIND_TRAP)),
        windTrapCost(config.getCostFor(Building::BuildingType::WIND_TRAP)),
        windTrapHitPoints(config.getHitPointsFor(Building::BuildingType::WIND_TRAP)),
        windTrapWidth(config.getWidthFor(Building::BuildingType::WIND_TRAP)),
        windTrapHeight(config.getHeightFor(Building::BuildingType::WIND_TRAP)),
        lightFactoryEnergy(config.getEnergyFor(Building::BuildingType::LIGHT_FACTORY)),
        lightFactoryCost(config.getCostFor(Building::BuildingType::LIGHT_FACTORY)),
        lightFactoryHitPoints(config.getHitPointsFor(Building::BuildingType::LIGHT_FACTORY)),
        lightFactoryWidth(config.getWidthFor(Building::BuildingType::LIGHT_FACTORY)),
        lightFactoryHeight(config.getHeightFor(Building::BuildingType::LIGHT_FACTORY)),
        heavyFactoryEnergy(config.getEnergyFor(Building::BuildingType::HEAVY_FACTORY)),
        heavyFactoryCost(config.getCostFor(Building::BuildingType::HEAVY_FACTORY)),
        heavyFactoryHitPoints(config.getHitPointsFor(Building::BuildingType::HEAVY_FACTORY)),
        heavyFactoryWidth(config.getWidthFor(Building::BuildingType::HEAVY_FACTORY)),
        heavyFactoryHeight(config.getHeightFor(Building::BuildingType::HEAVY_FACTORY)),
        spiceRefineryEnergy(config.getEnergyFor(Building::BuildingType::SPICE_REFINERY)),
        spiceRefineryCost(config.getCostFor(Building::BuildingType::SPICE_REFINERY)),
        spiceRefineryHitPoints(config.getHitPointsFor(Building::BuildingType::SPICE_REFINERY)),
        spiceRefinerySpiceCapacity(config.getSpiceCapacityFor(Building::BuildingType::SPICE_REFINERY)),
        spiceRefineryWidth(config.getWidthFor(Building::BuildingType::SPICE_REFINERY)),
        spiceRefineryHeight(config.getHeightFor(Building::BuildingType::SPICE_REFINERY)),
        spiceSiloEnergy(config.getEnergyFor(Building::BuildingType::SPICE_SILO)),
        spiceSiloCost(config.getCostFor(Building::BuildingType::SPICE_SILO)),
        spiceSiloHitPoints(config.getHitPointsFor(Building::BuildingType::SPICE_SILO)),
        spiceSiloSpiceCapacity(config.getSpiceCapacityFor(Building::BuildingType::SPICE_SILO)),
        spiceSiloWidth(config.getWidthFor(Building::BuildingType::SPICE_SILO)),
        spiceSiloHeight(config.getHeightFor(Building::BuildingType::SPICE_SILO)),
        barracksEnergy(config.getEnergyFor(Building::BuildingType::BARRACKS)),
        barracksCost(config.getCostFor(Building::BuildingType::BARRACKS)),
        barracksHitPoints(config.getHitPointsFor(Building::BuildingType::BARRACKS)),
        barracksWidth(config.getWidthFor(Building::BuildingType::BARRACKS)),
        barracksHeight(config.getHeightFor(Building::BuildingType::BARRACKS)),
        assaultRifleDamage(config.getDamageFor(WeaponType::ASSAULT_RIFLE)),
        assaultRifleShootingRate(config.getShootingRateFor(WeaponType::ASSAULT_RIFLE)),
        assaultRifleBonus(config.getBonusFor(WeaponType::ASSAULT_RIFLE)),
        cannonDamage(config.getDamageFor(WeaponType::CANNON)),
        cannonShootingRate(config.getShootingRateFor(WeaponType::CANNON)),
        cannonBonus(config.getBonusFor(WeaponType::CANNON)),
        rocketLauncherDamage(config.getDamageFor(WeaponType::ROCKET_LAUNCHER)),
        rocketLauncherShootingRate(config.getShootingRateFor(WeaponType::ROCKET_LAUNCHER)),
        rocketLauncherBonus(config.getBonusFor(WeaponType::ROCKET_LAUNCHER)),
        smallCannonDamage(config.getDamageFor(WeaponType::SMALL_CANNON)),
        smallCannonShootingRate(config.getShootingRateFor(WeaponType::SMALL_CANNON)),
        smallCannonBonus(config.getBonusFor(WeaponType::SMALL_CANNON)),
        lightInfantryHitPoints(config.getHitPointsFor(Unit::UnitType::LIGHT_INFANTRY)),
        lightInfantryRange(config.getRangeFor(Unit::UnitType::LIGHT_INFANTRY) * rangeFactor),
        lightInfantrySpeed(config.getSpeedFor(Unit::UnitType::LIGHT_INFANTRY)),
        lightInfantryTrainingTime(config.getTrainingTimeFor(Unit::UnitType::LIGHT_INFANTRY) * timeFactor),
        lightInfantryCost(config.getCostFor(Unit::UnitType::LIGHT_INFANTRY)),
        heavyInfantryHitPoints(config.getHitPointsFor(Unit::UnitType::HEAVY_INFANTRY)),
        heavyInfantryRange(config.getRangeFor(Unit::UnitType::HEAVY_INFANTRY) * rangeFactor),
        heavyInfantrySpeed(config.getSpeedFor(Unit::UnitType::HEAVY_INFANTRY)),
        heavyInfantryTrainingTime(config.getTrainingTimeFor(Unit::UnitType::HEAVY_INFANTRY) * timeFactor),
        heavyInfantryCost(config.getCostFor(Unit::UnitType::HEAVY_INFANTRY)),
        harvesterHitPoints(config.getHitPointsFor(Unit::UnitType::HARVESTER)),
        harvesterSpeed(config.getSpeedFor(Unit::UnitType::HARVESTER)),
        harvesterConstructionTime(config.getTrainingTimeFor(Unit::UnitType::HARVESTER) * timeFactor),
        harvesterCost(config.getCostFor(Unit::UnitType::HARVESTER)),
        harvesterSpiceCapacity(config.getSpiceCapacityFor(Unit::UnitType::HARVESTER)),
        harvesterFarmSpeed(config.getFarmSpeed(Unit::UnitType::HARVESTER) * timeFactor),
        harvesterLoadSpeed(config.getLoadSpeed(Unit::UnitType::HARVESTER) * timeFactor),
        trikeHitPoints(config.getHitPointsFor(Unit::UnitType::TRIKE)),
        trikeRange(config.getRangeFor(Unit::UnitType::TRIKE) * rangeFactor),
        trikeSpeed(config.getSpeedFor(Unit::UnitType::TRIKE)),
        trikeConstructionTime(config.getTrainingTimeFor(Unit::UnitType::TRIKE) * timeFactor),
        trikeCost(config.getCostFor(Unit::UnitType::TRIKE)),
        raiderHitPoints(config.getHitPointsFor(Unit::UnitType::RAIDER)),
        raiderRange(config.getRangeFor(Unit::UnitType::RAIDER) * rangeFactor),
        raiderSpeed(config.getSpeedFor(Unit::UnitType::RAIDER)),
        raiderConstructionTime(config.getTrainingTimeFor(Unit::UnitType::RAIDER) * timeFactor),
        raiderCost(config.getCostFor(Unit::UnitType::RAIDER)),
        tankHitPoints(config.getHitPointsFor(Unit::UnitType::TANK)),
        tankRange(config.getRangeFor(Unit::UnitType::TANK) * rangeFactor),
        tankSpeed(config.getSpeedFor(Unit::UnitType::TANK)),
        tankConstructionTime(config.getTrainingTimeFor(Unit::UnitType::TANK) * timeFactor),
        tankCost(config.getCostFor(Unit::UnitType::TANK)) {}

void GameConfiguration::init(const char *string) {
    if (instance == nullptr) {
        ConfigurationReader config(string);
        instance = std::unique_ptr<GameConfiguration>(new GameConfiguration(config));
    }
}

GameConfiguration& GameConfiguration::getConfig() {
    if (instance == nullptr) {
        // TODO: LA RUTA NO PUEDE QUEDAR HARCODEADA, DEBE LEERLA DESDE ARGV[1].
        std::string path = "/home/dypa/Dune/config.yaml";
        ConfigurationReader config(path);
        instance = std::unique_ptr<GameConfiguration>(new GameConfiguration(config));
    }
    return *instance;
}
