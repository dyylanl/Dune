//
// Created by riclui on 21/06/22.
//

#include "DevastatorCL.h"

DevastatorCL::DevastatorCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction,
                           int life,
                           bool action) : Vehicle(DEVASTATOR, position,
                                              SDL2pp::Point(53,44), id, player,
                                              selecStatus, posAction,
                                              life, action, 32, 8) {}
