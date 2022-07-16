//
// Created by riclui on 21/06/22.
//

#include "DeviatorCL.h"

DeviatorCL::DeviatorCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
                       bool action) : Vehicle(DESVIATOR, position,
                                              SDL2pp::Point(34,32), id, player,
                                              selecStatus, posAction,
                                              life, action, 32, 8) {}

