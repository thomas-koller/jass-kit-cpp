//
// Created by Thomas Koller on 24.08.20.
//

#include <random>
#include "jass/game/types.hpp"

#ifndef JASS_GAMEUTILS_HPP
#define JASS_GAMEUTILS_HPP

#endif //JASS_GAMEUTILS_HPP

namespace jass {
    class GameUtils;
}

/**
 * Class for various game utils. The class maintains a random number generator.
 */
class jass::GameUtils {
private:
    std::mt19937 random_generator;

public:
    GameUtils():
    random_generator(std::random_device()())
    {}

    CardSetPlayer deal_random_hand(){
        // create a vector of values from 0 to 35 and shuffle them
        // (cannot be done in Eigen, as there are no iterators)
        std::vector<int> values(36);
        std::iota(values.begin(), values.end(), 0);
        std::shuffle(values.begin(), values.end(), this->random_generator);

        // distribute cards to players
        CardSetPlayer hands = CardSetPlayer::Zero();
        int card_nr = 0;
        for (int player = 0; player < 4; player++){
            for (int player_card = 0; player_card < 9; player_card++) {
                hands(player, values[card_nr]) = 1;
                card_nr++;
            }
        }
        return hands;
    }

    static CardSetPlayer deal_hands(const CardList &north,
                                   const CardList &east,
                                   const CardList &south,
                                   const CardList &west) {
        CardSetPlayer hands = CardSetPlayer::Zero();
        for (auto card: north) {
            hands(NORTH, card) = 1;
        }
        for (auto card: east) {
            hands(EAST, card) = 1;
        }
        for (auto card: south) {
            hands(SOUTH, card) = 1;
        }
        for (auto card: west) {
            hands(WEST, card) = 1;
        }
        return hands;
    }

};