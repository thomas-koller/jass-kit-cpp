//
// Created by Thomas Koller on 21.08.20.
//

#include <iostream>
#include "jass/game/GameObservation.hpp"

std::ostream& operator<<(std::ostream& out, const jass::GameObservation& gameObservation) {
    Eigen::IOFormat octaveFmt(Eigen::StreamPrecision, 3, ", ", " ", "", "", "[", "]");

    out << "dealer : " << gameObservation.dealer << std::endl;
    out << "player : " << gameObservation.player << std::endl;
    out << "declared trump player : " << gameObservation.declared_trump_player << std::endl;
    out << "forehand : " << gameObservation.forehand << std::endl;
    out << "hand : " << gameObservation.hand.format(octaveFmt) << std::endl;
    out << "tricks :" << gameObservation.tricks.format(octaveFmt) << std::endl;
    out << "trick winner : " << gameObservation.trick_winner.format(octaveFmt) << std::endl;
    out << "first player : " << gameObservation.trick_first_player.format(octaveFmt) << std::endl;
    out << "trick points : " << gameObservation.trick_points.format(octaveFmt) << std::endl;
    out << "current trick : " << gameObservation.current_trick << std::endl;
    out << "nr cards in trick : " << gameObservation.nr_cards_in_trick << std::endl;
    out << "nr played cards : " << gameObservation.nr_played_cards << std::endl;
    out << "points[0] : " << gameObservation.points[0] << std::endl;
    out << "points[1] : " << gameObservation.points[1] << std::endl;
    return out;
}

jass::GameObservation::GameObservation()
        : dealer(-1),
          player(-1),
          player_view(-1),
          trump(NO_TRUMP),
          declared_trump_player(-1),
          forehand(false),
          current_trick(0),
          nr_cards_in_trick(0),
          nr_played_cards(0),
          points(2) {
    hand = -1;
    tricks = -1;
    trick_winner = -1;
    trick_first_player = -1;
    trick_points = 0;
    points[0] = 0;
    points[1] = 0;
}

jass::GameObservation::GameObservation(const jass::GameObservation &other)
        : dealer(other.dealer),
          player(other.player),
          player_view(other.player_view),
          trump(other.trump),
          declared_trump_player(other.declared_trump_player),
          forehand(other.forehand),
          current_trick(other.current_trick),
          nr_cards_in_trick(other.nr_cards_in_trick),
          nr_played_cards(other.nr_played_cards),
          points(other.points) {
    hand = other.hand;
    tricks = other.tricks;
    trick_winner = other.trick_winner;
    trick_first_player = other.trick_first_player;
    trick_points = other.trick_points;
}

bool jass::GameObservation::operator==(const jass::GameObservation &other) const {
    return
            dealer == other.dealer &&
            player == other.player &&
            player_view == other.player_view &&
            trump == other.trump &&
            declared_trump_player == other.declared_trump_player &&
            forehand == other.forehand &&
            (hand == other.hand).all() &&
            (tricks == other.tricks).all() &&
            (trick_winner == other.trick_winner).all() &&
            (trick_first_player == other.trick_first_player).all() &&
            (trick_points == other.trick_points).all() &&
            current_trick == other.current_trick &&
            nr_cards_in_trick == other.nr_cards_in_trick &&
            nr_played_cards == other.nr_played_cards &&
            points[0] == other.points[0] &&
            points[1] == other.points[1];
}
