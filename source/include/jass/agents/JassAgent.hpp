//
// Created by Thomas Koller on 26.08.20.
//

#ifndef JASS_JASSAGENT_HPP
#define JASS_JASSAGENT_HPP


#include <jass/game/types.hpp>
#include <jass/game/GameObservation.hpp>

namespace jass {
    class JassAgent;
}

/**
 * Agent to act as a player in the game of jass.
 */
class jass::JassAgent {
public:
    JassAgent() = default;

    JassAgent(const JassAgent&) = delete;

    virtual ~JassAgent() = default;

    /**
     * Select and return a trump action.
     *
     * @param obs the game observation for the player
     * @return the trump action
     */
    virtual int actionTrump(const jass::GameObservation& obs) = 0;

    /**
     * Calculate the probabilities and rewards for the possible trump actions.
     *
     * @param obs the game observation for the player
     * @return the probabilities and rewards for each trump action
     */
    virtual jass::ResultTrumpAction actionTrumpProb(const jass::GameObservation& obs) = 0;

    /**
     * Select and return the card to play. The card should be a valid card for the given
     * observation.
     *
     * @param obs the game observation for the player
     * @return the card to play
     */
    virtual int actionPlayCard(const jass::GameObservation& obs) = 0;

    /**
     * Calculate the probabilities and rewards for the card actions.
     *
     * @param obs the game observation for the player
     * @return the probabilities and rewards for each card action
     */
    virtual jass::ResultPlayCardAction actionPlayCardProb(const jass::GameObservation& obs) = 0;
};


#endif //JASS_JASSAGENT_HPP
