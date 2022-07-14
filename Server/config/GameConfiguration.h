#ifndef __GAME_CONFIGURATION_H__
#define __GAME_CONFIGURATION_H__

#include <string>
#include <memory>
#include "ConfigReader.h"

class GameConfiguration {
private:
    static std::shared_ptr<GameConfiguration> instance;

    explicit GameConfiguration(const ConfigurationReader& config);

public:
    ~GameConfiguration() = default;

    static void init(const char *string);

    static GameConfiguration& getConfig();

    const int speedFactor;
    const int blockMovement;
    const int rangeFactor;
    const int timeFactor;
    const int initialGold;
    const int initialEnergy;
    const int initialMaxEnergy;
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
    const int refineryEnergy;
    const int refineryCost;
    const int refineryHitPoints;
    const int refinerySpiceCapacity;
    const int refineryWidth;
    const int refineryHeight;
    const int siloEnergy;
    const int siloCost;
    const int siloHitPoints;
    const int siloSpiceCapacity;
    const int siloWidth;
    const int siloHeight;

    const int barracksEnergy;
    const int barracksCost;
    const int barracksHitPoints;
    const int barracksWidth;
    const int barracksHeight;

    const int palaceEnergy;
    const int palaceCost;
    const int palaceHitPoints;
    const int palaceWidth;
    const int palaceHeight;

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
};

#endif	// __GAME_CONFIGURATION_H__
