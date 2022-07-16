//
// Created by riclui on 21/06/22.
//

#include "TrikeCL.h"

TrikeCL::TrikeCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
                 bool action) : Vehicle(TRIKE, position,
                                    SDL2pp::Point(32,25), id, player,
                                    selecStatus, posAction,
                                    life, action, 32, 8) {}
