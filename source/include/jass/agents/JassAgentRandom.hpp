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

    int actionTrump(const jass::GameObservation &obs) override;

    ResultTrumpAction actionTrumpProb(const jass::GameObservation &obs) override;

    int actionPlayCard(const jass::GameObservation &obs) override;

    ResultPlayCardAction actionPlayCardProb(const jass::GameObservation &obs) override;

public:
};


#endif //JASS_JASSAGENTRANDOM_HPP
