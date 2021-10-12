//
// Created by Thomas Koller on 11/10/2021.
//

#ifndef JASS_IJASSKIT_HPP
#define JASS_IJASSKIT_HPP

// Interface to access the game simulation and utility functions from python
#include <vector>
#include <jass/game/GameSim.hpp>

// The running game simulations are globally stored within a vector and accessed by id.
extern std::vector<jass::GameSim> gameSim;

// global data structure for passing values
struct CARD_SET_PLAYER {

};

// possible actions on a game simulations (python only supports calling c, so these are mapped
// to functions

extern "C" void initFromCards(int gameSimId, )
#endif //JASS_IJASSKIT_HPP
