//
// Created by Thomas Koller on 29.10.21.
//

#ifndef JASS_JASSAGENTCHEATING_HPP
#define JASS_JASSAGENTCHEATING_HPP


#include <jass/game/types.hpp>
#include <jass/game/GameState.hpp>

namespace jass {
    class JassAgentCheating;
}

/**
 * Agent to act as a player in the game of jass.
 *
 * Version that uses a game state instead of an observation (cheating)
 */
class jass::JassAgentCheating {
public:
    typedef std::shared_ptr<JassAgentCheating> Ptr;

    JassAgentCheating() = default;

    JassAgentCheating(const JassAgentCheating&) = delete;

    virtual ~JassAgentCheating() = default;

    /**
     * Select and return a trump action.
     *
     * @param state the game state for the player
     * @return the trump action
     */
    virtual int actionTrump(const jass::GameState& state) = 0;

    /**
     * Calculate the probabilities and rewards for the possible trump actions.
     *
     * @param state the game state for the player
     * @return the probabilities and rewards for each trump action
     */
    virtual jass::ResultTrumpAction actionTrumpProb(const jass::GameState& state) = 0;

    /**
     * Select and return the card to play. The card should be a valid card for the given
     * state.
     *
     * @param state the game state for the player
     * @return the card to play
     */
    virtual int actionPlayCard(const jass::GameState& state) = 0;

    /**
     * Calculate the probabilities and rewards for the card actions.
     *
     * @param state the game state for the player
     * @return the probabilities and rewards for each card action
     */
    virtual jass::ResultPlayCardAction actionPlayCardProb(const jass::GameState& state) = 0;
};


#endif //JASS_JASSAGENTCHEATING_HPP
