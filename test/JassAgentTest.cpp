//
// Created by Thomas Koller on 27.08.20.
//

#include <random>
#include <gtest/gtest.h>
#include <jass/game/GameSim.hpp>
#include <jass/game/GameUtils.hpp>
#include <jass/game/GameStateUtils.hpp>
#include <jass/agents/JassAgentRandom.hpp>

#include "jass/game/types.hpp"
#include "jass/game/const.hpp"
#include "jass/game/RuleSchieber.hpp"

using namespace jass;

TEST(JassAgentTest, play_game) {
    // play a random game using the agent
    JassAgentRandom agent;

    std::random_device randomDevice;
    std::mt19937 random_generator(randomDevice());

    auto rule = std::make_shared<RuleSchieber>();
    GameSim game(rule);

    // deal random hands
    GameUtils util;
    auto hands = util.deal_random_hand();

    game.init_from_cards(hands, 1);

    int action = agent.actionTrump(observation_from_state(game.state, -1));
    game.perform_action_trump(action);

    if (action == PUSH) {
        action = agent.actionTrump(observation_from_state(game.state, -1));
        game.perform_action_trump(action);
    }

    // play game
    while (game.state.nr_played_cards < 36) {
        rule->assert_invariants(game.state);
        action = agent.actionPlayCard(observation_from_state(game.state, -1));
        game.perform_action_play_card(action);
    }
}