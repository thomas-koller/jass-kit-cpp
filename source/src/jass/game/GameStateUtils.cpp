//
// Created by Thomas Koller on 28.08.20.
//

#include "jass/game/GameStateUtils.hpp"

std::vector<int> jass::calculatePointsFromTricks(const GameObservation& obs) {
    std::vector<int> points(2);
    points[0] = 0;
    points[1] = 0;

    for (int i = 0; i < obs.current_trick; i++) {
        if (obs.trick_winner[i] == 0 || obs.trick_winner[i] == 2) {
            points[0] += obs.trick_points(i);
        } else {
            points[1] += obs.trick_points(i);
        }
    }
    return points;
}


jass::GameObservation jass::observationFromState(const jass::GameState& state, int player) {
    jass::GameObservation obs;

    obs.dealer = state.dealer;
    obs.player = state.player;

    if (player == -1) {
        obs.player_view = state.player;
    } else {
        obs.player_view = player;
    }

    obs.trump = state.trump;
    obs.forehand = state.forehand;
    obs.declared_trump_player = state.declared_trump_player;
    obs.hand = state.hands.row(obs.player_view);

    obs.tricks = state.tricks;
    obs.trick_winner = state.trick_winner;
    obs.trick_points = state.trick_points;
    obs.trick_first_player = state.trick_first_player;
    obs.current_trick = state.current_trick;
    obs.nr_cards_in_trick = state.nr_cards_in_trick;
    obs.nr_played_cards = state.nr_played_cards;
    obs.points = state.points;

    return obs;
}
jass::GameState jass::stateFromObservation(const jass::GameObservation& obs_in, const CardSetPlayer& hands) {
    jass::GameState state;

    state.dealer = obs_in.dealer;
    state.player = obs_in.player;

    state.trump = obs_in.trump;
    state.forehand = obs_in.forehand;
    state.declared_trump_player = obs_in.declared_trump_player;
    state.hands = hands;

    state.tricks = obs_in.tricks;
    state.trick_winner = obs_in.trick_winner;
    state.trick_points = obs_in.trick_points;
    state.trick_first_player = obs_in.trick_first_player;
    state.current_trick = obs_in.current_trick;
    state.nr_cards_in_trick = obs_in.nr_cards_in_trick;
    state.nr_played_cards = obs_in.nr_played_cards;
    state.points = obs_in.points;

    return state;
}
