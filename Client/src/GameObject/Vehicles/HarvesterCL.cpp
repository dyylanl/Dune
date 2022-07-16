//
// Created by riclui on 21/06/22.
//

#include "HarvesterCL.h"

HarvesterCL::HarvesterCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction,
                         int life,
                         bool action) : Vehicle(HARVESTER, position,
                                                          SDL2pp::Point(52,47), id, player,
                                                          selecStatus, posAction,
                                                          life, action, 34, 8) {}
