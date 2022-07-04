#ifndef __GAME_CONFIGURATION_H__
#define __GAME_CONFIGURATION_H__

#include <string>
#include <memory>
#include "ConfigReader.h"

class GameConfiguration {
private:
    static std::unique_ptr<GameConfiguration> instance;

    explicit GameConfiguration(const ConfigurationReader& config);

public:
    ~GameConfiguration() = default;

    static void init(const char *string);

    static GameConfiguration& getConfig();

    const int speedFactor;	// El speed factor debe ser multiplo de 84
    const int blockMovement;
    const int rangeFactor;
    const int timeFactor;
    const int initialGold;
    const int initialEnergy;
    const int initialMaxEnergy;
// Building Stats
    // Tiempo de costruccion de edificios
    const int buildingConstructionTime;
    // Centro de Construcción
    const int constructionCenterEnergy;
    const int constructionCenterCost;
    const int constructionCenterHitPoints;
    const int constructionCenterWidth;
    const int constructionCenterHeight;
    // Trampas de Aire
    const int windTrapEnergy;
    const int windTrapCost;
    const int windTrapHitPoints;
    const int windTrapWidth;
    const int windTrapHeight;
    // Fabrica Ligera
    const int lightFactoryEnergy;
    const int lightFactoryCost;
    const int lightFactoryHitPoints;
    const int lightFactoryWidth;
    const int lightFactoryHeight;
    // Fabrica Pesada
    const int heavyFactoryEnergy;
    const int heavyFactoryCost;
    const int heavyFactoryHitPoints;
    const int heavyFactoryWidth;
    const int heavyFactoryHeight;
    // Refinera
    const int spiceRefineryEnergy;
    const int spiceRefineryCost;
    const int spiceRefineryHitPoints;		// enunciado no dice
    const int spiceRefinerySpiceCapacity;
    const int spiceRefineryWidth;		// enunciado no dice
    const int spiceRefineryHeight;		// enunciado no dice
    // Silo
    const int spiceSiloEnergy;
    const int spiceSiloCost;
    const int spiceSiloHitPoints;
    const int spiceSiloSpiceCapacity;
    const int spiceSiloWidth;
    const int spiceSiloHeight;
    // Cuartel
    const int barracksEnergy;
    const int barracksCost;
    const int barracksHitPoints;
    const int barracksWidth;
    const int barracksHeight;
// Arms -> frecuencias de disparo por segundo
    // Rifles de asalto
    const int assaultRifleDamage;
    const int assaultRifleShootingRate;
    const int assaultRifleBonus;	// a infanteria
    // Cañon
    const int cannonDamage;
    const int cannonShootingRate;
    const int cannonBonus;
    // Lanzamisiles
    const int rocketLauncherDamage;
    const int rocketLauncherShootingRate;
    const int rocketLauncherBonus;
    // Cañon 22mm
    const int smallCannonDamage;
    const int smallCannonShootingRate;
    const int smallCannonBonus;		// vehiculos y edificios
// Infantry Stats
    // Infanteria Ligera
    const int lightInfantryHitPoints;
    const int lightInfantryRange;
    const int lightInfantrySpeed;
    const int lightInfantryTrainingTime;
    const int lightInfantryCost;
    // Infanteria Pesada
    const int heavyInfantryHitPoints;
    const int heavyInfantryRange;
    const int heavyInfantrySpeed;
    const int heavyInfantryTrainingTime;
    const int heavyInfantryCost;
// Vehicles
    // Cosechadora
    const int harvesterHitPoints;
    const int harvesterSpeed;
    const int harvesterConstructionTime;
    const int harvesterCost;
    const int harvesterSpiceCapacity;
    const int harvesterFarmSpeed;
    const int harvesterLoadSpeed;
    // Trike
    const int trikeHitPoints;
    const int trikeRange;
    const int trikeSpeed;
    const int trikeConstructionTime;
    const int trikeCost;
    // Raider
    const int raiderHitPoints;
    const int raiderRange;
    const int raiderSpeed;
    const int raiderConstructionTime;
    const int raiderCost;
    // Tanque
    const int tankHitPoints;
    const int tankRange;
    const int tankSpeed;
    const int tankConstructionTime;
    const int tankCost;
};

#endif	// __GAME_CONFIGURATION_H__
