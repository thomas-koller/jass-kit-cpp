//
// Created by Thomas Koller on 02.11.18.
//

#ifndef JASS_CPLUSPLUS_RULE_H
#define JASS_CPLUSPLUS_RULE_H

#include <memory>
#include "jass/game/types.hpp"
#include "jass/game/GameObservation.hpp"
#include "jass/game/GameState.hpp"

namespace jass {
    class GameRule;
}

class jass::GameRule {
    /**
    Class for implementing rules of the jass game. The class includes rules that depend not on the process (like
    how trump is determined), but only upon cards. Currently this includes to determine the valid cards to play
    in a trick, to determine the winner of a trick and the points of a trick.

    This in an abstract base class that defines the interface.
    */
public:
    typedef std::shared_ptr<GameRule> Ptr;

    /**
     * Get the valid cards that can be played on the trick.
     *
     * @param hand the cards of the player
     * @param trick the current played trick
     * @param card_nr the card nr to play in the trick (0 for first card)
     * @param trump the declared trump color
     * @return the set of valid cards to play
     */
    virtual CardSet get_valid_cards(const CardSet& hand, const CardTrick& trick, int card_nr, int trump) = 0;

    CardSet get_valid_cards_from_state(const GameState& state) {
        return get_valid_cards(
                state.hands.row(state.player),
                state.tricks.row(state.current_trick),
                state.nr_cards_in_trick,
                state.trump);
    }

    CardSet get_valid_cards_from_obs(const GameObservation& obs) {
        return get_valid_cards(
                obs.hand,
                obs.tricks.row(obs.current_trick),
                obs.nr_cards_in_trick,
                obs.trump);
    }

    /**
     * Calculate the points from the cards in the trick
     * @param trick the complete trick
     * @param is_last_card true if this was the last card of the round
     * @param trump the declared trump
     * @return the number of points made
     */
    virtual int calc_points(const CardTrick& trick, bool is_last_card, int trump) = 0;

    /**
     * Calculate the winner of the complete trick
     * @param trick the complete trick
     * @param first_player the first player of the trick
     * @param trump the declared trump
     * @return the winner of the trick
     */
    virtual int calc_winner(const CardTrick& trick, int first_player, int trump) = 0;

    /**
     * Calculate valid actions from state including trump.
     *
     * @param state state of the game
     * @return valid actions
     */
    inline ActionFullSet get_full_valid_actions_from_state(const GameState &state) {
        ActionFullSet action = ActionFullSet::Zero();
        if (state.trump == -1) {
            // get trump action
            if (state.forehand == -1) {
                // all trump are possible including Push
                action.segment<7>(TRUMP_FULL_OFFSET) = 1;
            } else {
                // Push is not available
                action.segment<6>(TRUMP_FULL_OFFSET) = 1;
            }
        } else {
            // valid cards
            auto cards = get_valid_cards(
                    state.hands.row(state.player),
                    state.tricks.row(state.current_trick),
                    state.nr_cards_in_trick,
                    state.trump);
            action.segment<36>(0) = cards;
        }
#ifndef NDEBUG
        if (action.sum() == 0) {
            std::cerr << "No valid actions in getFullValidActionsFromState" << std::endl;
        }
#endif
        return action;
    }

    /**
     * Calculate valid actions from obs including trump.
     *
     * @param obs game observation
     * @return set of valid actions
     */
    inline ActionFullSet get_full_valid_actions_from_obs(const GameObservation &obs) {
        ActionFullSet action = ActionFullSet::Zero();
        if (obs.trump == -1) {
            // get trump action
            if (obs.forehand == -1) {
                // all trump are possible including Push
                action.segment<7>(TRUMP_FULL_OFFSET) = 1;
            } else {
                // Push is not available
                action.segment<6>(TRUMP_FULL_OFFSET) = 1;
            }
        } else {
            // valid cards
            action.segment<36>(0) = get_valid_cards(
                    obs.hand,
                    obs.tricks.row(obs.current_trick),
                    obs.nr_cards_in_trick,
                    obs.trump);
        }
        return action;
    }


    /// check invariants for this rule and state
    virtual void assert_invariants(const GameState &state) const = 0;

    /// check invariants for this rule and obs
    virtual void assert_invariants(const GameObservation &obs) const = 0;

};

#endif //JASS_CPLUSPLUS_RULE_H
