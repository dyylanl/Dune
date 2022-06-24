#ifndef __GAME_CONFIGURATION_H__
#define __GAME_CONFIGURATION_H__

#include <string>
#include <memory>

class ConfigurationReader;

class GameConfiguration {
private:
    static std::unique_ptr<GameConfiguration> instance;

public:
    ~GameConfiguration() = default;
    static void init(const char *string);
    static GameConfiguration& getConfig();

    //game
    const int speedFactor;
    const int blockMovement;
    const int rangeFactor;
    const int timeFactor;
    const int initialGold;
    const int initialEnergy;
    const int initialMaxEnergy;
    //building
    const int buildingConstructionTime;
    const int constructionCenterEnergy;
    const int constructionCenterCost;
    const int constructionCenterHitPoints;
    const int constructionCenterWidth;
    const int constructionCenterHeight;
    const int windTrapEnergy;
    const int windTrapCost;
    const int windTrapHitPoints;
    const int windTrapWidth;
    const int windTrapHeight;
    const int lightFactoryEnergy;
    const int lightFactoryCost;
    const int lightFactoryHitPoints;
    const int lightFactoryWidth;
    const int lightFactoryHeight;
    const int heavyFactoryEnergy;
    const int heavyFactoryCost;
    const int heavyFactoryHitPoints;
    const int heavyFactoryWidth;
    const int heavyFactoryHeight;
    const int spiceRefineryEnergy;
    const int spiceRefineryCost;
    const int spiceRefineryHitPoints;
    const int spiceRefinerySpiceCapacity;
    const int spiceRefineryWidth;
    const int spiceRefineryHeight;
    const int spiceSiloEnergy;
    const int spiceSiloCost;
    const int spiceSiloHitPoints;
    const int spiceSiloSpiceCapacity;
    const int spiceSiloWidth;
    const int spiceSiloHeight;
    const int barracksEnergy;
    const int barracksCost;
    const int barracksHitPoints;
    const int barracksWidth;
    const int barracksHeight;
    //weapons
    const int assaultRifleDamage;
    const int assaultRifleShootingRate;
    const int assaultRifleBonus;
    const int cannonDamage;
    const int cannonShootingRate;
    const int cannonBonus;
    const int rocketLauncherDamage;
    const int rocketLauncherShootingRate;
    const int rocketLauncherBonus;
    const int smallCannonDamage;
    const int smallCannonShootingRate;
    const int smallCannonBonus;
    //units
    const int lightInfantryHitPoints;
    const int lightInfantryRange;
    const int lightInfantrySpeed;
    const int lightInfantryTrainingTime;
    const int lightInfantryCost;
    const int heavyInfantryHitPoints;
    const int heavyInfantryRange;
    const int heavyInfantrySpeed;
    const int heavyInfantryTrainingTime;
    const int heavyInfantryCost;
    const int harvesterHitPoints;
    const int harvesterSpeed;
    const int harvesterConstructionTime;
    const int harvesterCost;
    const int harvesterSpiceCapacity;
    const int harvesterFarmSpeed;
    const int harvesterLoadSpeed;
    const int trikeHitPoints;
    const int trikeRange;
    const int trikeSpeed;
    const int trikeConstructionTime;
    const int trikeCost;
    const int raiderHitPoints;
    const int raiderRange;
    const int raiderSpeed;
    const int raiderConstructionTime;
    const int raiderCost;
    const int tankHitPoints;
    const int tankRange;
    const int tankSpeed;
    const int tankConstructionTime;
    const int tankCost;

    explicit GameConfiguration(const ConfigurationReader& config);
};

#endif	// __GAME_CONFIGURATION_H__
