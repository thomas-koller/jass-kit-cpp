//
// Created by Thomas Koller on 24.08.20.
//

#ifndef JASS_GAMESTATEUTILS_HPP
#define JASS_GAMESTATEUTILS_HPP

#include <vector>
#include "jass/game/GameObservation.hpp"
#include "jass/game/GameState.hpp"

namespace jass {
    std::vector<int> calculatePointsFromTricks(const GameObservation& obs);
    GameObservation observationFromState(const jass::GameState& state, int player);
    GameState stateFromObservation(const jass::GameObservation& obs_in, const CardSetPlayer& hands);
}




#endif //JASS_GAMESTATEUTILS_HPP
