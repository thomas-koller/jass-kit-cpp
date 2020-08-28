//
// Created by Thomas Koller on 26.08.20.
//

#include <jass/game/GameObservation.hpp>
#include <jass/agents/JassAgentRandom.hpp>


jass::JassAgentRandom::JassAgentRandom() :
    rule() {
    std::random_device random_device;
    random_generator.seed(random_device());
}


int jass::JassAgentRandom::actionTrump(const jass::GameObservation &obs) {
    // lock access to random generator
    std::lock_guard<std::mutex> lock(mutex);

    // play forehand half of the time
    if (obs.forehand == -1) {
        if (std::uniform_int_distribution<>{0, 1}(random_generator))
            return PUSH;
    }
    // select trump
    return (std::uniform_int_distribution<>{0, 5}(random_generator));
}

jass::ResultTrumpAction jass::JassAgentRandom::actionTrumpProb(const jass::GameObservation &obs) {
    // same probability for all
    Eigen::Array<float, 7, 1> probability;
    probability.fill(1.0f/7.0f);
    return { probability, Eigen::Array<float, 7, 1>::Zero()};
}

int jass::JassAgentRandom::actionPlayCard(const jass::GameObservation &obs) {
    auto validCards = rule.get_valid_cards_from_obs(obs);
    auto validCardsList = card_set_to_list(validCards);
    int nrValid = (int)validCardsList.size();

    // lock access to random generator
    std::lock_guard<std::mutex> lock(mutex);

    std::uniform_int_distribution<int> uniform_dist(0, nrValid-1);
    int index = uniform_dist(random_generator);
    int action = validCardsList[index];

    return action;
}

jass::ResultPlayCardAction jass::JassAgentRandom::actionPlayCardProb(const jass::GameObservation &obs) {
    auto validCards = rule.get_valid_cards_from_obs(obs);
    int nrValidCards = validCards.sum();

    // same probability for all
    Eigen::Array<float, 36, 1> probability;
    probability = 1.0 / (float)nrValidCards;
    probability = probability * validCards.cast<float>();

    return { probability, Eigen::Array<float, 36, 1>::Zero()};
}

