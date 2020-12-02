//
// Created by Thomas Koller on 21.08.20.
//

#include "jass/game/GameSim.hpp"

void jass::GameSim::initFromCards(const jass::CardSetPlayer &hands, int dealer) {
    state.dealer = dealer;
    state.player = nextPlayer(dealer);
    state.trump = -1;
    state.forehand = -1;
    state.hands = hands;
    state.tricks.fill(-1);
    state.trick_winner.fill(-1);
    state.trick_points.fill(0);
    state.trick_first_player.fill(-1);
    state.current_trick = 0;
    state.nr_cards_in_trick = 0;
    state.nr_played_cards = 0;
    state.points[0] = 0;
    state.points[1] = 0;
}

void jass::GameSim::performActionTrump(int trump_action) {
    if (state.forehand == -1) {
        // action of the forehand player
        if (trump_action == PUSH) {
            state.forehand = 0;
            state.player = partnerPlayer(state.player);
        } else {
            // player declares trump
            state.forehand = 1;
            state.trump = trump_action;
            state.declared_trump_player = state.player;
            // next action is to play a card
            state.player = nextPlayer(state.dealer);
            state.trick_first_player(0) = state.player;
        }
    } else if (state.forehand == 0) {
        // action of the rearhand player
        state.trump = trump_action;
        state.declared_trump_player = state.player;
        state.player = nextPlayer(state.dealer);
        state.trick_first_player(0) = state.player;
    } else {
        throw std::invalid_argument("Illegal forehand state");
    }
}

void jass::GameSim::performActionPlayCard(int card) {
    // remove card from player
    assert(state.hands(state.player, card) == 1);
    state.hands(state.player, card) = 0;

    // place in trick
    state.tricks(state.current_trick, state.nr_cards_in_trick) = card;
    state.nr_played_cards++;

    if (state.nr_cards_in_trick < 3) {
        if (state.nr_cards_in_trick == 0) {
            // this is usually already set at the end of the last trick, however
            // when data is provided externally, that might not be set
            // TODO: check if still needs to be set in endTrick() or if it should just be here
            state.trick_first_player(state.current_trick) = state.player;
        }
        // trick is not yet finished
        state.nr_cards_in_trick++;
        state.player = nextPlayer(state.player);
    } else {
        // trick is finished
        endTrick();
    }
}

void jass::GameSim::performActionFull(int action) {
    if (action < TRUMP_FULL_OFFSET) {
        performActionPlayCard(action);
    } else {
        int trump_action = action - TRUMP_FULL_OFFSET;
        if (trump_action == PUSH_ALT) {
            trump_action = PUSH;
        }
        performActionTrump(trump_action);
    }
}


void jass::GameSim::endTrick() {
    // update information about the current trick
    int pts = rule->calcPoints(
            state.tricks.row(state.current_trick),
            state.nr_played_cards == 36,
            state.trump);
    state.trick_points[state.current_trick] = pts;

    int winner = rule->calcWinner(
            state.tricks.row(state.current_trick),
            state.trick_first_player[state.current_trick],
            state.trump);

    state.trick_winner[state.current_trick] = winner;

    if (winner == NORTH || winner == SOUTH) {
        state.points[0] += pts;
    } else {
        state.points[1] += pts;
    }

    if (state.current_trick < 8) {
        // not the end of the game
        state.current_trick++;
        state.nr_cards_in_trick = 0;
        state.trick_first_player[state.current_trick] = winner;
        state.player = winner;
    } else {
        // end of round (should be determined by the number of cards), but in order to compute assertions
        // and so, we set the current trick to 9, so that we always have current_trick-1 complete tricks
        state.current_trick = 9;
        state.nr_cards_in_trick = 0;
        state.player = -1;
    }
}

