//
// Created by Thomas Koller on 03.11.18.
//

#ifndef JASS_CPLUSPLUS_CONST_H
#define JASS_CPLUSPLUS_CONST_H

#include "types.hpp"

namespace jass {
    // players
    const int NORTH = 0;
    const int EAST = 1;
    const int SOUTH = 2;
    const int WEST = 3;

    // Colors for trump, there is a long and a short constant for each
    const int DIAMONDS = 0;                 // Ecken / Schellen
    const int D = DIAMONDS;
    const int HEARTS = 1;                   // Herz / Rosen
    const int H = HEARTS;
    const int SPADES = 2;                   // Schaufeln / Schilten
    const int S = SPADES;
    const int CLUBS = 3;                    // Kreuz / Eichel
    const int C = CLUBS;
    const int OBE_ABE = 4;
    const int O = OBE_ABE;
    const int UNE_UFE = 5;
    const int U = UNE_UFE;
    const int MAX_TRUMP = 5;                // maximal value of a trump action (for loops)

    // additional action available at trump selection phase, this is encoded as 10 in the Swisslos specification.
    const int PUSH = 10;                    // Schieben
    const int P = PUSH;

    // alternative value for push (used in some ml approaches to be able to 1-hot encode the trump/push action
    // (is translated to PUSH when the action is added to the round)
    const int PUSH_ALT = 6;

    // alternative values for trump for 'full' actions, i.e. both trump and cards are valid actions
    const int TRUMP_FULL_OFFSET = 36;
    const int TRUMP_FULL_D = TRUMP_FULL_OFFSET + DIAMONDS;
    const int TRUMP_FULL_H = TRUMP_FULL_OFFSET + HEARTS;
    const int TRUMP_FULL_S = TRUMP_FULL_OFFSET + SPADES;
    const int TRUMP_FULL_C = TRUMP_FULL_OFFSET + CLUBS;
    const int TRUMP_FULL_O = TRUMP_FULL_OFFSET + OBE_ABE;
    const int TRUMP_FULL_U = TRUMP_FULL_OFFSET + UNE_UFE;
    const int TRUMP_FULL_P = TRUMP_FULL_OFFSET + PUSH_ALT;

    const int ACTION_SET_FULL_SIZE = TRUMP_FULL_P + 1;

    const int NO_TRUMP = -1;                // trump has not been declared yet
    const int NO_CARD = -1;                 // no card

    // cards
    // Diamonds
    const int DA  = 0;
    const int DK  = 1;
    const int DQ  = 2;
    const int DJ  = 3;
    const int D10 = 4;
    const int D9  = 5;
    const int D8  = 6;
    const int D7  = 7;
    const int D6  = 8;

    // Hearts
    const int HA  = 9 ;
    const int HK  = 10;
    const int HQ  = 11;
    const int HJ  = 12;
    const int H10 = 13;
    const int H9  = 14;
    const int H8  = 15;
    const int H7  = 16;
    const int H6  = 17;

    // Spades
    const int SA  = 18;
    const int SK  = 19;
    const int SQ  = 20;
    const int SJ  = 21;
    const int S10 = 22;
    const int S9  = 23;
    const int S8  = 24;
    const int S7  = 25;
    const int S6  = 26;

    // Clubs
    const int CA  = 27;
    const int CK  = 28;
    const int CQ  = 29;
    const int CJ  = 30;
    const int C10 = 31;
    const int C9  = 32;
    const int C8  = 33;
    const int C7  = 34;
    const int C6  = 35;

    // Offset of cards inside color
    const int A_offset = 0;
    const int K_offset = 1;
    const int Q_offset = 2;
    const int J_offset = 3;
    const int Ten_offset = 4;
    const int Nine_offset = 5;
    const int Eight_offset = 6;
    const int Seven_offset = 7;
    const int Six_offset = 8;

    inline int nextPlayer(int player) {
        static int next_player_array[] = {3, 0, 1, 2};
        return next_player_array[player];
    }

    inline int partnerPlayer(int player) {
        static int partner_player_array[] = {2, 3, 0, 1};
        return partner_player_array[player];
    }

    inline int teamOfPlayer(int player) {
        static int team_of_player_array[] = {0, 1, 0, 1};
        return team_of_player_array[player];
    }

    /**
     * Get the color of a card
     * @param card the card
     * @return the color of that card
     */
    inline int colorOfCard(int card) {
        assert(card <= 36);
        static int color_of_card_array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            1, 1, 1, 1, 1, 1, 1, 1, 1,
                                            2, 2, 2, 2, 2, 2, 2, 2, 2,
                                            3, 3, 3, 3, 3, 3, 3, 3, 3};
        return color_of_card_array[card];
    }

    /**
     * Start of cards of given color in
     * @param color
     * @return
     */
    inline int colorOffset(int color){
        static int color_offset_array[] = {0, 9, 18, 27};
        return color_offset_array[color];
    }

    /**
     * Return true if there is a card of a specific color, false otherwise
     * @param hand cards in the hand
     * @param color the color
     * @return true if there is a card of that color
     */
    inline bool isColorInHand(const CardSet &hand, int color){
        int offset = colorOffset(color);
        return (hand.segment(offset, 9) == 1).any();
    }

    /**
     * Return set of cards of that color that are also in the hand.
     * @param hand The hand
     * @param color color
     * @return
     */
    inline CardSet maskColor(const CardSet& hand, int color) {
        CardSet value = CardSet::Zero();
        int offset  = colorOffset(color);
        value.segment(offset, 9) = hand.segment(offset, 9);
        return value;
    }

    /**
     * Create list (vector) of the cards from the set.
     *
     * @param cards a card set
     * @return the list of cards in the set
     */
    inline CardList cardSetToList(const CardSet& cards) {
        CardList list;

        for (int i = 0; i < NR_CARDS; i++) {
            if (cards[i] > 0) {
                list.push_back(i);
            }
        }
        return list;
    }

    /**
     * Create set of cards from a list
     *
     * @param the list of cards
     * @return the set with the cards in the list
     */
    inline CardSet cardListToSet(const CardList& list) {
        CardSet cards = CardSet::Zero();

        for (auto &card: list) {
            cards[card] = 1;
        }
        return cards;
    }

    /**
 * Create list (vector) from set.
 *
 * @param set set with values set to 1
 * @return the list of the indices with values == 1
 */
    inline std::vector<int> setToList(const Eigen::Ref<const Eigen::ArrayXi>& set) {
        std::vector<int> list;

        for (int i = 0; i < set.size(); i++) {
            if (set[i] > 0) {
                list.push_back(i);
            }
        }
        return list;
    }


}
#endif //JASS_CPLUSPLUS_CONST_H
