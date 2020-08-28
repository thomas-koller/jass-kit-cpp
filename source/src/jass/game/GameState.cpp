//
// Created by Thomas Koller on 21.08.20.
//

#include "jass/game/GameState.hpp"

std::ostream& operator<<(std::ostream& out, const jass::GameState& state) {
    Eigen::IOFormat octaveFmt(Eigen::StreamPrecision, 3, ", ", " ", "", "", "[", "]");

    out << "dealer : " << state.dealer << std::endl;
    out << "player : " << state.player << std::endl;
    out << "declared trump player : " << state.declared_trump_player << std::endl;
    out << "forehand : " << state.forehand << std::endl;
    out << "hands : " << state.hands.format(octaveFmt) << std::endl;
    out << "tricks :" << state.tricks.format(octaveFmt) << std::endl;
    out << "trick winner : " << state.trick_winner.format(octaveFmt) << std::endl;
    out << "first player : " << state.trick_first_player.format(octaveFmt) << std::endl;
    out << "trick points : " << state.trick_points.format(octaveFmt) << std::endl;
    out << "current trick : " << state.current_trick << std::endl;
    out << "nr cards in trick : " << state.nr_cards_in_trick << std::endl;
    out << "nr played cards : " << state.nr_played_cards << std::endl;
    out << "points[0] : " << state.points[0] << std::endl;
    out << "points[1] : " << state.points[1] << std::endl;
    return out;
}

jass::GameState::GameState()
        :
        dealer(-1),
        player(-1),
        trump(NO_TRUMP),
        declared_trump_player(-1),
        forehand(-1),
        current_trick(0),
        nr_cards_in_trick(0),
        nr_played_cards(0),
        points(2){
    hands = -1;
    tricks = -1;
    trick_winner = -1;
    trick_first_player = -1;
    trick_points = 0;
    points[0] = 0;
    points[1] = 0;
}
