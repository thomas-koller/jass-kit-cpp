//
// Created by Thomas Koller on 21.08.20.
//

#ifndef JASS_GAMEOBSERVATION_HPP
#define JASS_GAMEOBSERVATION_HPP

#include <memory>
#include <iostream>
#include "jass/game/types.hpp"
#include "jass/game/const.hpp"

namespace jass {
    class GameObservation;
}

std::ostream& operator<<(std::ostream& out, const jass::GameObservation& gameObservation);

/**
 * Observation of the state of the game from a player's view. It contains all the information
 * about the game that the player can observe at a specific time in the game.
 *
 * This information is
 *      - the dealer
 *      - the player that declared trump,
 *      - the trump chosen
 *      - trump was declared forehand or not (derived information)
 *      - the tricks that have been played so far
 *      - the winner and the first player (derived) of each trick
 *      - the number of points that have been made by the current jass_players team in this round
 *      - the number of points that have been made by the opponent team in this round
 *      - the number of cards played in the current trick
 *      - the cards played in the current trick
 *      - the current player
 *      - the player whose view this observation is
 *      - the hand of the player
 *
 *  Similar to the class GameState, GameObservation captures
 *  the information at different stages of the game, like:
 *      - Player can choose to select a trump or push the right to make trump to his partner
 *      - Player needs to select trump after his partner pushed
 *      - Player needs to play a card.
 *
 *  The class only contains the information, but no methods for changing. It will usually be
 *  created using the game simulation or from some external interface (log file) providing
 *  the information.
 */
class jass::GameObservation {
public:
    /// shared Pointer to GameObservation
    typedef std::shared_ptr<GameObservation> Ptr;
    // we keep the data public (as in the python case) so as not to have a large number of trivial
    // getters and setters that would not be able to enforce data consistency anyway
    // The method assert_invariants can be used to verify that the data is consistent.

    /// dealer of the round
    int dealer;

    /// player for the next action (trump or card)
    int player;

    /// player whose view and hand this observation belongs to
    int player_view;

    /// the declared trump color (or obe, une) or -1 if trump has not been declared yet
    int trump;

    /// player who declared trump
    int declared_trump_player;

    /// -1 if not yet known, 1 if first player declared trump, 0 otherwise
    int forehand;

    /// cards in hands of the current player
    CardSet hand;

    /// all tricks
    CardAllTricks tricks;

    /// player that won the trick
    TrickWinner trick_winner;

    /// first player of a trick (redundant)

    TrickPlayer trick_first_player;

    // points in trick
    TrickPoints trick_points;

    /// current/next trick, after playing the last card of a trick, the current trick is
    /// the next one
    int current_trick;
    int nr_cards_in_trick;

    // total number of played cards
    int nr_played_cards;

    // points made by team 0 (players N and S) and team 1 (players E and W)
    std::vector<int> points;

    /**
     * Create the observation.
     */
    explicit GameObservation();

    /**
     * Copy constructor.
     * @param other round to copy from
     */
    GameObservation(const GameObservation &other);

    bool operator==(const GameObservation& other) const;

    bool operator!=(const GameObservation& other) const {
        return !operator==(other);
    }

    bool is_finished() const {
        return nr_played_cards == 36;
    }

    int points_own() const {
        if (player == 0 || player == 2) {
            return points[0];
        } else {
            return points[1];
        }
    }

    int points_opponent() const {
        if (player == 0 || player == 2) {
            return points[1];
        } else {
            return points[0];
        }
    }

};

#endif //JASS_GAMEOBSERVATION_HPP
