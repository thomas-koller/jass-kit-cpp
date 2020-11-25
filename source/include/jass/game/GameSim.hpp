//
// Created by Thomas Koller on 21.08.20.
//

#ifndef JASS_GAMESIM_HPP
#define JASS_GAMESIM_HPP

#include <utility>

#include "jass/game/GameState.hpp"
#include "jass/game/GameRule.hpp"

namespace jass {
    class GameSim;

}
/**
 *  Class for simulating a game. A game consists of selecting trump and playing 36 cards, currently the
 *  trump selection phase is implemented for Schieber. For other versions of the game regarding the order
 *  of actions, the class can be overridden. The actual rules of the game, points scoring, winning tricks
 *  and calculating which cards are allowed to be played are implemented in the rule class.
 */
class jass::GameSim {
private:

    GameRule::Ptr rule;

public:
    typedef std::shared_ptr<GameSim> Ptr;
    /// State of the game. This is public as in python. State might be set from outside anytime as
    /// long as it is valid.
    GameState state;

    explicit GameSim(GameRule::Ptr  rule):
            rule(std::move(rule))
    {}

    GameSim(GameState  state, GameRule::Ptr  rule):
            state(std::move(state)),
            rule(std::move(rule))
    {}

    void initFromCards(const CardSetPlayer& hands, int dealer);

    /**
     * Perform a trump action and set the state accordingly. Actions are selecting a valid trump
     * or passing (push)
     * @param trump_action
     */
    void performActionTrump(int trump_action);

    /**
     * Perform a action to play the given card by the current player. The state is updated accordingly.
     * @param card the card to play
     */
    void performActionPlayCard(int card);

    /**
     * Perform action from the full set of actions, including trump.
     * @param action action to perform
     */
    void performActionFull(int action);

    /**
     * Return true if the game has finished.
     * @return true if the game has finished, false otherwise
     */
    inline bool isDone() const {
        return state.nr_played_cards == 36;
    }


private:
    /**
     * Calculate state at the end of a trick
     */
    void endTrick();

};

#endif //JASS_GAMESIM_HPP
