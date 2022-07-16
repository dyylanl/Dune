//
// Created by riclui on 21/06/22.
//

#include "SonicTankCL.h"

SonicTankCL::SonicTankCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction,
                         int life,
                         bool action) : Vehicle(SONIC_TANK, position,
                                            SDL2pp::Point(31,37), id, player,
                                            selecStatus, posAction,
                                            life, action, 30, 10) {}

