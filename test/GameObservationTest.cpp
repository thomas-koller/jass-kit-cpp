//
// Created by Thomas Koller on 24.08.20.
//

#include <gtest/gtest.h>
#include <jass/game/GameState.hpp>
#include <jass/game/GameObservation.hpp>

#include "jass/game/types.hpp"
#include "jass/game/const.hpp"
#include "jass/game/RuleSchieber.hpp"

using namespace jass;

TEST(GameObservation, copy) {
    GameObservation obs;
    obs.dealer = 2;

    GameObservation obs2 = obs;
    ASSERT_EQ(obs2.dealer, 2);
    // ASSERT_EQ(obs, obs2);
    ASSERT_TRUE(obs == obs2);
}