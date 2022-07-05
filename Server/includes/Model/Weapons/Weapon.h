#ifndef __WEAPON_H__
#define __WEAPON_H__

enum class WeaponType {
    ASSAULT_RIFLE,
    CANNON,
    ROCKET_LAUNCHER,
    SMALL_CANNON,
    SOUND_WAVES,
    PLASMA_CANNON
};

class Weapon {
protected:
    const int damage;
    const int frecuency;
    const int bonus;
public:
    Weapon(int damage, int frecuency, int bonus);
    ~Weapon();
    int getFrecuency() const;
    int getDammage() const;
    virtual int getInfantryBonus() const = 0;
    virtual int getVehicleBonus() const = 0;
    virtual int getBuildingBonus() const = 0;
};

#endif  // __WEAPON_H__
