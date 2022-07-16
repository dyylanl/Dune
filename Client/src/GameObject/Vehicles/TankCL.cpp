//
// Created by riclui on 21/06/22.
//

#include "TankCL.h"

TankCL::TankCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
               bool action) : Vehicle(TANK, position,
                                  SDL2pp::Point(33,29), id, player,
                                  selecStatus, posAction,
                                  life, action, 32, 8) {}
