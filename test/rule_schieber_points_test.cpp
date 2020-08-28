//
// Created by Thomas Koller on 07.11.18.
//

#include <gtest/gtest.h>

#include "jass/game/types.hpp"
#include "jass/game/const.hpp"
#include "jass/game/RuleSchieber.hpp"

using namespace jass;

TEST(RuleSchieberPointsTest, trump) {
    RuleSchieber rule;
    CardTrick trick = CardTrick::Constant(-1);

    trick(0) = SA;
    trick(1) = SK;
    trick(2) = SQ;
    trick(3) = SJ;

    EXPECT_EQ(20, rule.calc_points(trick, false, DIAMONDS));
    EXPECT_EQ(25, rule.calc_points(trick, true, HEARTS));
    EXPECT_EQ(38, rule.calc_points(trick, false, SPADES));
    EXPECT_EQ(20, rule.calc_points(trick, false, CLUBS));

    trick(0) = SA;
    trick(1) = SJ;
    trick(2) = S6;
    trick(3) = S9;
    EXPECT_EQ(45, rule.calc_points(trick, false, SPADES));
}

TEST(RuleSchieberPointsTest, obe_une) {
    RuleSchieber rule;
    CardTrick trick = CardTrick::Constant(-1);

    trick(0) = SA;
    trick(1) = SK;
    trick(2) = SQ;
    trick(3) = SJ;

    EXPECT_EQ(20, rule.calc_points(trick, false, OBE_ABE));
    EXPECT_EQ(14, rule.calc_points(trick, true, UNE_UFE));

    trick(0) = CA;
    trick(1) = S8;
    trick(2) = S6;
    trick(3) = H6;
    EXPECT_EQ(19, rule.calc_points(trick, false, OBE_ABE));
    EXPECT_EQ(30, rule.calc_points(trick, false, UNE_UFE));
}

