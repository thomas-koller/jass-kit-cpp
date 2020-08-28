//
// Created by Thomas Koller on 24.08.20.
//

#include <random>
#include <gtest/gtest.h>
#include <jass/game/GameSim.hpp>
#include <jass/game/GameUtils.hpp>
#include <jass/game/GameStateUtils.hpp>

#include "jass/game/types.hpp"
#include "jass/game/const.hpp"
#include "jass/game/RuleSchieber.hpp"

using namespace jass;

TEST(GameSimTest, play_game) {
    std::random_device randomDevice;
    std::mt19937 random_generator(randomDevice());

    auto rule = std::make_shared<RuleSchieber>();
    GameSim game(rule);

    // deal random hands
    GameUtils util;
    auto hands = util.deal_random_hand();

    game.init_from_cards(hands, 1);
    game.perform_action_trump(PUSH);
    game.perform_action_trump(DIAMONDS);

    // play game
    while (game.state.nr_played_cards < 35) {
        rule->assert_invariants(game.state);
        // get observations for all the players
        for (int player=0; player < 4; player++) {
            GameObservation obs = observation_from_state(game.state, player);
            rule->assert_invariants(obs);
        }

        auto validCards = rule->get_valid_cards_from_state(game.state);

        auto validCardsList = card_set_to_list(validCards);
        int nrValid = (int)validCardsList.size();

        std::uniform_int_distribution<int> uniform_dist(0, nrValid-1);
        int index = uniform_dist(random_generator);
        int action = validCardsList[index];

        game.perform_action_play_card(action);
        rule->assert_invariants(game.state);
    }

}