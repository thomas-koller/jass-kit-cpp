//
// Created by Thomas Koller on 21.08.20.
//

#ifndef JASS_GAMESTATE_HPP
#define JASS_GAMESTATE_HPP

#include <memory>
#include "jass/game/const.hpp"

namespace jass {
    class GameState;
}

std::ostream& operator<<(std::ostream& out, const jass::GameState& state);

/**
 * Class for the state of the game.
 */
class jass::GameState {

public:

    /// shared pointer to GameState
    typedef std::shared_ptr<GameState> Ptr;

    // we keep the data public (as in the python case) so as not to have a large number of trivial
    // getters and setters that would not be able to enforce data consistency anyway
    // The method assertInvariants can be used to verify that the data is consistent.


    /// dealer of the round
    int dealer;

    /// player for the next action (trump or card)
    int player;

    /// the declared trump color (or obe, une) or -1 if trump has not been declared yet
    int trump;

    /// player who declared trump
    int declared_trump_player;

    /// -1 if not yet known (before trump), 1 if first player declares trump, 0 otherwise
    int forehand;

    /// cards in hands of all players
    CardSetPlayer hands;

    /// all tricks
    CardAllTricks tricks;

    /// player that won the trick
    TrickWinner trick_winner;

    /// first player of a trick (redundant)
    TrickPlayer trick_first_player;

    // points in trick
    TrickPoints trick_points;

    /// current/next trick, after playing the last card of a trick, the current trick is the next one
    int current_trick;
    int nr_cards_in_trick;

    // total number of played cards
    int nr_played_cards;

    // points made by team 0 (players N and S) and team 1 (players E and W)
    std::vector<int> points;

    GameState();
};


#endif //JASS_GAMESTATE_HPP
