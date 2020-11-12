//
// Created by Thomas Koller on 07.11.18.
//

#include <gtest/gtest.h>

#include "jass/game/types.hpp"
#include "jass/game/const.hpp"

using namespace jass;

TEST(const_tests, color){
    CardSet hand = CardSet::Zero();

    hand(C6) = 1;
    hand(SA) = 1;

    EXPECT_TRUE(isColorInHand(hand, C));
    EXPECT_TRUE(isColorInHand(hand, S));
    EXPECT_FALSE(isColorInHand(hand, H));
    EXPECT_FALSE(isColorInHand(hand, D));
}

TEST(const_tests, mask) {
    CardSet hand = CardSet::Zero();

    hand(C6) = 1;
    hand(SA) = 1;
    hand(S10) = 1;

    auto masked = maskColor(hand, SPADES);
    EXPECT_TRUE(masked(C6) == 0);
    EXPECT_TRUE(masked(SA) == 1);
    EXPECT_TRUE(masked(S10) == 1);

    masked = maskColor(hand, C);
    EXPECT_TRUE(masked(C6) == 1);
    EXPECT_TRUE(masked(SA) == 0);
    EXPECT_TRUE(masked(S10) == 0);
}

TEST(const_tests, conversion) {
    CardSet hand = CardSet::Zero();

    hand(C6) = 1;
    hand(SA) = 1;
    hand(S10) = 1;

    CardList list = cardSetToList(hand);

    ASSERT_EQ(3, list.size());
    ASSERT_EQ(SA, list[0]);
    ASSERT_EQ(S10, list[1]);
    ASSERT_EQ(C6, list[2]);

    CardList list2;
    list2.push_back(HK);
    list2.push_back(D8);

    CardSet set = cardListToSet(list2);

    ASSERT_EQ(2, set.sum());
    ASSERT_EQ(1, set[HK]);
    ASSERT_EQ(1, set[D8]);
    ASSERT_EQ(0, set[D7]);
}

