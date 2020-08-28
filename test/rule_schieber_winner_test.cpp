//
// Created by Thomas Koller on 07.11.18.
//

#include <gtest/gtest.h>

#include "jass/game/types.hpp"
#include "jass/game/const.hpp"
#include "jass/game/RuleSchieber.hpp"

using namespace jass;

TEST(RuleSchieberWinnerTest, trick1) {
    RuleSchieber rule;
    CardTrick trick = CardTrick::Constant(-1);

    trick(0) = SA; // E
    trick(1) = SK; // N
    trick(2) = HQ; // W
    trick(3) = C7; // S

    EXPECT_EQ(EAST, rule.calc_winner(trick, EAST, DIAMONDS));
    EXPECT_EQ(WEST, rule.calc_winner(trick, EAST, HEARTS));
    EXPECT_EQ(EAST, rule.calc_winner(trick, EAST, SPADES));
    EXPECT_EQ(SOUTH, rule.calc_winner(trick, EAST, CLUBS));
    EXPECT_EQ(EAST, rule.calc_winner(trick, EAST, OBE_ABE));
    EXPECT_EQ(NORTH, rule.calc_winner(trick, EAST, UNE_UFE));
}

TEST(RuleSchieberWinnerTest, trick2) {
    RuleSchieber rule;
    CardTrick trick = CardTrick::Constant(-1);

    trick(0) = S9;
    trick(1) = S10;
    trick(2) = SQ;
    trick(3) = SK;

    EXPECT_EQ(EAST, rule.calc_winner(trick, EAST, SPADES));
}

TEST(RuleSchieberWinnerTest, trick3) {
    RuleSchieber rule;
    CardTrick trick = CardTrick::Constant(-1);

    trick(0) = S9;
    trick(1) = S10;
    trick(2) = SJ;
    trick(3) = SK;

    EXPECT_EQ(EAST, rule.calc_winner(trick, WEST, SPADES));

}

TEST(RuleSchieberWinnerTest, trick4) {
    RuleSchieber rule;
    CardTrick trick = CardTrick::Constant(-1);

    trick(0) = S9;
    trick(1) = S10;
    trick(2) = SJ;
    trick(3) = SK;

    EXPECT_EQ(WEST, rule.calc_winner(trick, EAST, SPADES));
}

TEST(RuleSchieberWinnerTest, trick5) {
    RuleSchieber rule;
    CardTrick trick = CardTrick::Constant(-1);

    trick(0) = SA;
    trick(1) = D6;
    trick(2) = D7;
    trick(3) = SJ;

    EXPECT_EQ(EAST, rule.calc_winner(trick, EAST, HEARTS));
    EXPECT_EQ(WEST, rule.calc_winner(trick, EAST, DIAMONDS));
    EXPECT_EQ(SOUTH, rule.calc_winner(trick, EAST, SPADES));
}

TEST(RuleSchieberWinnerTest, trick6) {
    RuleSchieber rule;
    CardTrick trick = CardTrick::Constant(-1);

    trick(0) = D7;
    trick(1) = SA;
    trick(2) = D6;
    trick(3) = S9;

    EXPECT_EQ(WEST, rule.calc_winner(trick, EAST, UNE_UFE));
}

TEST(RuleSchieberWinnerTest, trick7) {
    RuleSchieber rule;
    CardTrick trick = CardTrick::Constant(-1);

    trick(0) = SA;
    trick(1) = D6;
    trick(2) = D7;
    trick(3) = S9;

    EXPECT_EQ(SOUTH, rule.calc_winner(trick, EAST, UNE_UFE));
    EXPECT_EQ(EAST, rule.calc_winner(trick, EAST, OBE_ABE));
}


