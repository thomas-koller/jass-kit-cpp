//
// Created by Thomas Koller on 24.08.20.
//

#ifndef JASS_GAMESTATEUTILS_HPP
#define JASS_GAMESTATEUTILS_HPP

#include <vector>
#include "jass/game/GameObservation.hpp"
#include "jass/game/GameState.hpp"

namespace jass {
    std::vector<int> calculate_points_from_tricks(const GameObservation& obs);
    GameObservation observation_from_state(const jass::GameState& state, int player);
}




#endif //JASS_GAMESTATEUTILS_HPP
