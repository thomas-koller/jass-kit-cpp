//
// Created by Thomas Koller on 06.11.18.
//

#include <iostream>
#include <jass/game/GameState.hpp>
#include "jass/game/const.hpp"
#include "jass/game/RuleSchieber.hpp"


jass::RuleSchieber::RuleSchieber() {
    // initialize look up table for higher/lower trump
    Eigen::Array<int, 9, 9> higher_trump_card;
    higher_trump_card <<
    //  A  K  Q  J 10  9  8  7  6
        0, 0, 0, 1, 0, 1, 0, 0, 0,  // A
        1, 0, 0, 1, 0, 1, 0, 0, 0,  // K
        1, 1, 0, 1, 0, 1, 0, 0, 0,  // Q
        0, 0, 0, 0, 0, 0, 0, 0, 0,  // J
        1, 1, 1, 1, 0, 1, 0, 0, 0,  // 10
        0, 0, 0, 1, 0, 0, 0, 0, 0,  // 9
        1, 1, 1, 1, 1, 1, 0, 0, 0,  // 8
        1, 1, 1, 1, 1, 1, 1, 0, 0,  // 7
        1, 1, 1, 1, 1, 1, 1, 1, 0;  // 6
    higher_trump = 0;
    higher_trump.block<9, 9>(0, 0) = higher_trump_card;
    higher_trump.block<9, 9>(9, 9) = higher_trump_card;
    higher_trump.block<9, 9>(18, 18) = higher_trump_card;
    higher_trump.block<9, 9>(27, 27) = higher_trump_card;

    lower_trump = 0;
    Eigen::Array<int, 9, 9>  lower_trump_card = 1 - higher_trump_card;
    lower_trump.block<9, 9>(0, 0) = lower_trump_card;
    lower_trump.block<9, 9>(9, 9) = lower_trump_card;
    lower_trump.block<9, 9>(18, 18) = lower_trump_card;
    lower_trump.block<9, 9>(27, 27) = lower_trump_card;

    card_values <<
    // DA DK DQ DJ D10 D9 D8 D7 D6 HA HK HQ HJ H10 H9 H8 H7 H6 DA DK DQ DJ D10 D9 D8 D7 D6 CA CK CQ CJ C10 C9 C8 C7  C6
       11, 4, 3,20, 10,14, 0, 0, 0,11, 4, 3, 2, 10, 0, 0, 0, 0,11, 4, 3, 2, 10, 0, 0, 0, 0,11, 4, 3, 2, 10, 0, 0, 0, 0,
       11, 4, 3, 2, 10, 0, 0, 0, 0,11, 4, 3,20, 10,14, 0, 0, 0,11, 4, 3, 2, 10, 0, 0, 0, 0,11, 4, 3, 2, 10, 0, 0, 0, 0,
       11, 4, 3, 2, 10, 0, 0, 0, 0,11, 4, 3, 2, 10, 0, 0, 0, 0,11, 4, 3,20, 10,14, 0, 0, 0,11, 4, 3, 2, 10, 0, 0, 0, 0,
       11, 4, 3, 2, 10, 0, 0, 0, 0,11, 4, 3, 2, 10, 0, 0, 0, 0,11, 4, 3, 2, 10, 0, 0, 0, 0,11, 4, 3,20, 10,14, 0, 0, 0,
       11, 4, 3, 2, 10, 0, 8, 0, 0,11, 4, 3, 2, 10, 0, 8, 0, 0,11, 4, 3, 2, 10, 0, 8, 0, 0,11, 4, 3, 2, 10, 0, 8, 0, 0,
        0, 4, 3, 2, 10, 0, 8, 0,11, 0, 4, 3, 2, 10, 0, 8, 0,11, 0, 4, 3, 2, 10, 0, 8, 0,11, 0, 4, 3, 2, 10, 0, 8, 0,11;
}


jass::CardSet jass::RuleSchieber::getValidCards(const CardSet &hand, const CardTrick &trick, int card_nr, int trump) {
    // play anything on the first move
    if (card_nr == 0) {
        return hand;
    }

    // get the color of the first played card and check if we have that color
    int color_played = colorOfCard(trick(0));
    bool have_color_played = isColorInHand(hand, color_played);

    if (trump == OBE_ABE || trump == UNE_UFE){
        if (have_color_played) {
            // play a card of that color
            return maskColor(hand, color_played);
        } else {
            // play any card
            return hand;
        }
    }

    // trump selected and not obe or une
    CardSet trump_cards = maskColor(hand, trump);

    int nr_trumps_in_hand = trump_cards.sum();
    int nr_cards_in_hand = hand.sum();

    // if we only have one card, play it (optimization ?)
    if (nr_cards_in_hand == 1) {
        return hand;
    }

    // played color is trump
    if (color_played == trump) {
        if (nr_trumps_in_hand == 0){
            // no more trumps, play anything
            return hand;
        }
        if (nr_trumps_in_hand == 1 && hand(colorOffset(trump) + J_offset)) {
            // only trump J, play anything
            return hand;
        }
        // we have more than one trump or one trump that is not J, play any of them
        return trump_cards;
    }

    // played color is not trump

    // check if anybody else (player 1 or player 2) played a trump, and if yes find out how high it was
    int lowest_trump_played = NO_CARD;
    bool trump_played = false;

    if (card_nr > 1) {
        // check player 1
        if (colorOfCard(trick(1)) == trump) {
            trump_played = true;
            lowest_trump_played = trick(1);
        }
        // check player 2 (only if 3 cards played, player 2 is the last player before us then)
        if (card_nr == 3) {
            if (colorOfCard(trick(2)) == trump) {
                if (!trump_played){
                    // only trump from player 2, not from player 1
                    trump_played = true;
                    lowest_trump_played = trick(2);
                } else {
                    // player 1 and 2 played trump, we must compare them to find the lowest

                    // move from player 2 is lower (as its index value is higher)
                    if (lowest_trump_played < trick(2)) {
                        lowest_trump_played = trick(2);
                    }
                }
            }
        }
    }

    // no trump from player 2 or 3
    if (!trump_played) {
        // there was not trump played by anybody
        if (have_color_played) {
            // play the color or trump
            return maskColor(hand, color_played) + trump_cards;
        } else {
            // play anything (including trump)
            return hand;
        }
    }

    // trump from player 2 or 3 played, we must make sure not to play a lower trump if there is an alternative
    if (nr_trumps_in_hand == nr_cards_in_hand) {
        // we have only trump left, so we can give any of them
        return hand;
    } else {
        // find the valid trumps to play

        if (have_color_played){
            // give a color or a higher trump
            Eigen::Array<int, 36, 1> higher = higher_trump.row(lowest_trump_played);
            return maskColor(hand, color_played) + (trump_cards * higher);
        } else {
            // play anything but a lower trump cards
            Eigen::Array<int, 36, 1> lower = lower_trump.row(lowest_trump_played);
            auto not_lower = 1 - (trump_cards * lower);
            return hand * not_lower;
        }
    }
}

int jass::RuleSchieber::calcPoints(const CardTrick &trick, bool is_last_card, int trump) {
    int points =
            card_values(trump, trick(0)) +
            card_values(trump, trick(1)) +
            card_values(trump, trick(2)) +
            card_values(trump, trick(3));
    if (is_last_card) {
        return points + 5;
    } else {
        return points;
    }

}

int jass::RuleSchieber::calcWinner(const CardTrick &trick, int first_player, int trump) {
    int color_played = colorOfCard(trick(0));
    int winner = 0;

    if (trump == UNE_UFE){
        // lowest card of first color wins
        int lowest_card = trick(0);
        for (int i = 1; i < 4; ++i) {
            if (colorOfCard(trick(i)) == color_played && trick(i) > lowest_card) {
                lowest_card = trick(i);
                winner = i;
            }
        }

    } else if (trump == OBE_ABE) {
        // highest card of first color wins
        int highest_card = trick(0);
        for (int i = 1; i < 4; ++i) {
            if (colorOfCard(trick(i)) == color_played && trick(i) < highest_card) {
                highest_card = trick(i);
                winner = i;
            }
        }
    } else if (color_played == trump) {
        // trump mode and first card is trump: highest trump wins
        int highest_card = trick(0);
        for (int i = 1; i < 4; ++i) {
            if (colorOfCard(trick(i)) == trump && (lower_trump(trick(i), highest_card) == 1)) {
                highest_card = trick(i);
                winner = i;
            }
        }
    } else {
        // trump mode, but different color played on first move, so we have to check for higher cards until a trump
        // is played, and then for the highest trump
        int highest_card = trick(0);
        int highest_trump = NO_CARD;
        bool trump_played = false;
        for (int i = 1; i < 4; ++i) {
            if (colorOfCard(trick(i)) == trump) {
                // trump played for that card
                if (trump_played) {
                    // there was a trump before, check if the new one is higher
                    if (lower_trump(trick(i), highest_trump) == 1){
                        winner = i;
                        highest_trump = trick(i);
                    }
                } else {
                    // first trump in trick
                    trump_played = true;
                    highest_trump = trick(i);
                    winner = i;
                }
            } else if (trump_played) {
                // trump played previously, but this is not trump, so that can not be a winner
            } else if (colorOfCard(trick(i)) == color_played) {
                // no trump played in trick, and this card has the correct color
                if (trick(i) < highest_card) {
                    highest_card = trick(i);
                    winner = i;
                }
            }

        }
    }
    // adjust winner by first player
    return (4 + first_player - winner) % 4;
}


void jass::RuleSchieber::assertInvariants(const GameState& state) const {
    // only do something if debug is enabled, as asserts won't be tested otherwise anyway
#ifndef NDEBUG
    // std::cout << state;
#endif
    // trump, dealer and first player of first trick
    if (state.trump != -1){
        assert(state.dealer >= 0 && state.dealer <= 3);
        assert(state.trump >= 0 && state.trump <=5);
        if (state.forehand == 1) {
            assert(state.declared_trump_player == nextPlayer(state.dealer));
        } else if (state.forehand == 0) {
            assert(state.declared_trump_player == partnerPlayer(nextPlayer(state.dealer)));
        }
        assert(state.trick_first_player[0] == nextPlayer(state.dealer));


        if (state.current_trick > 0) {
            for (int t = 1; t < state.current_trick; t++) {
                assert(state.trick_first_player[t] == state.trick_winner[t-1]);
            }
        }

        assert(state.nr_played_cards == 4*state.current_trick + state.nr_cards_in_trick);

        // number of cards
        int nr_cards_in_hands = state.hands.sum();
        assert(nr_cards_in_hands + state.nr_played_cards == 36);

        // number of points
        int p[2];
        p[0] = p[1] = 0;
        for (int t = 0; t < state.current_trick; t++) {
            if (state.trick_winner[t] == 0 or state.trick_winner[t] == 2){
                p[0] += state.trick_points(t);
            } else {
                p[1] += state.trick_points(t);
            }
        }
        // missing number of points
        //int missing_points = 0;
        // add points in current trick
        //for (auto card = 0; card < nr_cards_in_trick; card++) {
        //    missing_points += rule->card_values(trump, tricks(current_trick, card))
        //}

        assert(state.points[0] == p[0]);
        assert(state.points[1] == p[1]);

        if (state.nr_played_cards == 36) {
            assert(state.player == -1);
        }
    }
}

void jass::RuleSchieber::assertInvariants(const GameObservation& obs) const{
#ifndef NDEBUG
    //std::cout << obs;
#endif
    // trump, dealer and first player of first trick
    if (obs.trump != -1) {
        assert(obs.dealer >= 0 && obs.dealer <= 3);
        assert(obs.trump >= 0 && obs.trump <= 5);
        if (obs.forehand == 1) {
            assert(obs.declared_trump_player == nextPlayer(obs.dealer));
        } else if (obs.forehand == 0) {
            assert(obs.declared_trump_player == partnerPlayer(nextPlayer(obs.dealer)));
        }
        // first player is only set after the first card of a trick
        // has been played
        if (obs.nr_played_cards > 0) {
            assert(obs.trick_first_player[0] == nextPlayer(obs.dealer));
        }

        if (obs.current_trick > 0) {
            for (int t = 1; t < obs.current_trick; t++) {
                assert(obs.trick_first_player[t] == obs.trick_winner[t - 1]);
                assert(obs.trick_first_player[t] != -1);
            }
            if (obs.nr_cards_in_trick > 0) {
                assert(obs.trick_first_player[obs.current_trick] != -1);
            }
        }
        assert(obs.nr_played_cards == 4 * obs.current_trick + obs.nr_cards_in_trick);

        // number of cards
        int nr_cards_in_hands = obs.hand.sum();
        if (obs.player == obs.player_view) {
            assert(nr_cards_in_hands == 9 - obs.current_trick);
        }

        // number of points, changed to sum over all tricks, so that other elements have to be set to 0
        int p[2];
        p[0] = p[1] = 0;
        for (int t = 0; t < 9; t++) {
            if (obs.trick_winner[t] == 0 or obs.trick_winner[t] == 2) {
                p[0] += obs.trick_points(t);
            } else {
                p[1] += obs.trick_points(t);
            }
        }

        assert(obs.points[0] == p[0]);
        assert(obs.points[1] == p[1]);
#ifndef NDEBUG
        // std::cout << "Assertion ok" << std::endl;
#endif
    }
}


