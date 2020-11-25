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
    auto hands = util.dealRandomHand();

    game.initFromCards(hands, 1);
    game.performActionTrump(PUSH);
    game.performActionTrump(DIAMONDS);

    // play game
    while (game.state.nr_played_cards < 35) {
        rule->assertInvariants(game.state);
        // get observations for all the players
        for (int player=0; player < 4; player++) {
            GameObservation obs = observationFromState(game.state, player);
            rule->assertInvariants(obs);
        }

        auto validCards = rule->getValidCardsFromState(game.state);

        auto validCardsList = cardSetToList(validCards);
        int nrValid = (int)validCardsList.size();

        std::uniform_int_distribution<int> uniform_dist(0, nrValid-1);
        int index = uniform_dist(random_generator);
        int action = validCardsList[index];

        game.performActionPlayCard(action);
        rule->assertInvariants(game.state);
    }
}

TEST(GameSimTest, action_full) {
    std::random_device randomDevice;
    std::mt19937 random_generator(randomDevice());

    auto rule = std::make_shared<RuleSchieber>();
    GameSim game(rule);

    // deal random hands
    GameUtils util;
    auto hands = util.dealRandomHand();

    game.initFromCards(hands, 1);

    while (!game.isDone()) {
        rule->assertInvariants(game.state);
        auto valid_actions = rule->getFullValidActionsFromState(game.state);
        auto valid_action_list = setToList(valid_actions);
        int nrValid = (int)valid_action_list.size();
        std::uniform_int_distribution<int> uniform_dist(0, nrValid-1);
        int index = uniform_dist(random_generator);
        int action = valid_action_list[index];
        std::cout << action << std::endl;
        game.performActionFull(action);
    }
}