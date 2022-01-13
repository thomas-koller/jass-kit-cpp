//
// Created by Thomas Koller on 26.08.20.
//

#ifndef JASS_JASSAGENTRANDOM_HPP
#define JASS_JASSAGENTRANDOM_HPP

#include <random>
#include <mutex>

#include "jass/agents/JassAgent.hpp"
#include "jass/game/RuleSchieber.hpp"

namespace jass {
    class JassAgentRandom;
}

class jass::JassAgentRandom: public jass::JassAgent {
private:
    std::mutex mutex;
    std::mt19937 random_generator;
    RuleSchieber rule;

public:
    JassAgentRandom();

    ~JassAgentRandom() override = default;

    int action_trump(const jass::GameObservation &obs) override;

    ResultTrumpAction action_trump_prob(const jass::GameObservation &obs) override;

    int action_play_card(const jass::GameObservation &obs) override;

    ResultPlayCardAction action_play_card_prob(const jass::GameObservation &obs) override;

};


#endif //JASS_JASSAGENTRANDOM_HPP
