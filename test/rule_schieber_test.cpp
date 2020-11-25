//
// Created by Thomas Koller on 07.11.18.
//

#include <gtest/gtest.h>
#include <jass/game/GameSim.hpp>
#include <jass/game/GameUtils.hpp>

#include "jass/game/types.hpp"
#include "jass/game/const.hpp"
#include "jass/game/RuleSchieber.hpp"

using namespace jass;

TEST(RuleSchieberTest, obe_une) {
    RuleSchieber rule;
    CardSet hand = CardSet::Zero();
    hand(SA) = 1;
    hand[SK] = 1;
    hand[H7] = 1;
    hand[HJ] = 1;

    CardTrick trick = CardTrick::Constant(-1);

    // no color, OBE
    trick(0) = CA;

    auto valid = rule.getValidCards(hand, trick, 1, OBE_ABE);
    EXPECT_TRUE(valid.isApprox(hand));

    // no color, UNE
    trick(0) = C6;
    valid = rule.getValidCards(hand, trick, 1, UNE_UFE);
    EXPECT_TRUE(valid.isApprox(hand));

    // color in hand
    trick(0) = SQ;
    valid = rule.getValidCards(hand, trick, 1, OBE_ABE);
    CardSet expected = CardSet::Zero();
    expected(SA) = expected(SK) = 1;
    EXPECT_TRUE(expected.isApprox(valid));

    trick(0) = S7;
    valid = rule.getValidCards(hand, trick, 1, OBE_ABE);
    EXPECT_TRUE(expected.isApprox(valid));
}

TEST(RuleSchieberTest, first_move) {
    RuleSchieber rule;
    CardSet hand = CardSet::Zero();
    hand(SA) = hand(SK) = hand(H7) = hand(HJ) = hand(C6) = hand(C7) = hand(D10) = 1;
    CardTrick trick = CardTrick::Constant(-1);

    auto valid = rule.getValidCards(hand, trick, 0, UNE_UFE);
    EXPECT_TRUE(valid.isApprox(hand));

    valid = rule.getValidCards(hand, trick, 0, OBE_ABE);
    EXPECT_TRUE(valid.isApprox(hand));

    valid = rule.getValidCards(hand, trick, 0, DIAMONDS);
    EXPECT_TRUE(valid.isApprox(hand));

    valid = rule.getValidCards(hand, trick, 0, SPADES);
    EXPECT_TRUE(valid.isApprox(hand));
}

TEST(RuleSchieberTest, no_trump) {
    RuleSchieber rule;
    CardSet hand = CardSet::Zero();
    hand(SA) = hand(SK) = hand(H7) = hand(HJ) = hand(C6) = hand(C7) = 1;
    CardTrick trick = CardTrick::Constant(-1);
    trick(0) = D10;

    auto valid = rule.getValidCards(hand, trick, 1, DIAMONDS);
    EXPECT_TRUE(valid.isApprox(hand));

    trick(0) = DJ;
    trick(1) = D9;
    trick(2) = D10;
    valid = rule.getValidCards(hand, trick, 3, DIAMONDS);
    EXPECT_TRUE(valid.isApprox(hand));
}

TEST(RuleSchieberTest, have_trump) {
    RuleSchieber rule;
    CardSet expected = CardSet::Zero();
    CardSet hand = CardSet::Zero();
    hand(SA) = hand(SK) = hand(H7) = hand(HJ) = hand(C6) = hand(C7) = 1;
    CardTrick trick = CardTrick::Constant(-1);

    // give one of the trumps
    trick(0) = SJ;
    auto valid = rule.getValidCards(hand, trick, 1, SPADES);
    expected(SA) = expected(SK) = 1;
    EXPECT_TRUE(expected.isApprox(valid));

    // give one of the trumps (including jack)
    trick(0) = H10;
    valid = rule.getValidCards(hand, trick, 1, HEARTS);
    expected = 0;
    expected(HJ) = expected(H7) = 1;
    EXPECT_TRUE(expected.isApprox(valid));
}

TEST(RuleSchieberTest, trump_jack) {
    RuleSchieber rule;
    CardSet hand = CardSet::Zero();
    hand(SA) = hand(SK) = hand(HJ) = hand(C6) = hand(C7) = 1;
    CardTrick trick = CardTrick::Constant(-1);

    // give one of the trumps
    trick(0) = H6;
    trick(1) = H8;
    auto valid = rule.getValidCards(hand, trick, 2, HEARTS);
    EXPECT_TRUE(valid.isApprox(hand));
}

TEST(RuleSchieberTest, other_color) {
    RuleSchieber rule;
    CardSet expected = CardSet::Zero();
    CardSet hand = CardSet::Zero();
    hand(SA) = hand(SK) = hand(HJ) = hand(C6) = hand(C7) = 1;
    CardTrick trick = CardTrick::Constant(-1);

    // give one of the trumps
    trick(0) = S10;
    trick(1) = C6;
    auto valid = rule.getValidCards(hand, trick, 2, HEARTS);
    expected(SA) = expected(SK) = expected(HJ) = 1;
    EXPECT_TRUE(expected.isApprox(valid));
}

TEST(RuleSchieberTest, other_color_trump_played_H) {
    RuleSchieber rule;
    CardSet expected = CardSet::Zero();
    CardSet hand = CardSet::Zero();
    hand(SA) = hand(SK) = hand(HJ) = hand(H8) = hand(H6) = hand(C6) = hand(C7) = 1;
    CardTrick trick = CardTrick::Constant(-1);

    // give color or higher trump
    trick(0) = C10;
    trick(1) = CA;
    trick(2) = H10;
    auto valid = rule.getValidCards(hand, trick, 3, HEARTS);
    expected(C6) = expected(C7) = expected(HJ) = 1;
    EXPECT_TRUE(expected.isApprox(valid));


    // same for higher trump played
    trick(0) = C10;
    trick(1) = CA;
    trick(2) = HA;
    valid = rule.getValidCards(hand, trick, 3, HEARTS);
    EXPECT_TRUE(expected.isApprox(valid));
}

TEST(RuleSchieberTest, other_color_trump_played_S) {
    RuleSchieber rule;
    CardSet expected = CardSet::Zero();
    CardSet hand = CardSet::Zero();
    hand(SA) = hand(SK) = hand(H8) = hand(H6) = hand(C6) = hand(C7) = 1;
    CardTrick trick = CardTrick::Constant(-1);

    // give color or higher trump
    trick(0) = HK;
    trick(1) = H8;
    trick(2) = SQ;
    auto valid = rule.getValidCards(hand, trick, 3, SPADES);
    expected(H8) = expected(H6) = expected(SA) = expected(SK) = 1;
    EXPECT_TRUE(expected.isApprox(valid));

    // no higher trump, only color allowed
    trick(0) = HK;
    trick(1) = SJ;
    valid = rule.getValidCards(hand, trick, 2, SPADES);
    expected = 0;
    expected(H8) = expected(H6) = 1;
    EXPECT_TRUE(expected.isApprox(valid));
}

TEST(RuleSchieberTest, other_color_trump_played_9) {
    RuleSchieber rule;
    CardSet expected = CardSet::Zero();
    CardSet hand = CardSet::Zero();
    hand(SA) = hand(SK) = hand(H9) = hand(H8) = hand(H6) = hand(C7) = hand(C6) = 1;
    CardTrick trick = CardTrick::Constant(-1);

    // give color or higher trump
    trick(0) = C10;
    trick(1) = CA;
    trick(2) = H10;
    auto valid = rule.getValidCards(hand, trick, 3, HEARTS);
    expected(C7) = expected(C6) = expected(H9) = 1;
    EXPECT_TRUE(expected.isApprox(valid));

    // same for higher trump played
    trick(0) = C10;
    trick(1) = CA;
    trick(2) = HA;
    valid = rule.getValidCards(hand, trick, 3, HEARTS);
    EXPECT_TRUE(expected.isApprox(valid));
}

TEST(RuleSchieberTest, only_trump) {
    RuleSchieber rule;
    CardSet expected = CardSet::Zero();
    CardSet hand = CardSet::Zero();
    hand(DA) = hand(DK) = hand(D8) = 1;

    CardTrick trick = CardTrick::Constant(-1);
    trick(0) = C10;
    trick(1) = DJ;
    trick(2) = H10;
    auto valid = rule.getValidCards(hand, trick, 3, DIAMONDS);
    EXPECT_TRUE(valid.isApprox(hand));
}

TEST(RuleSchieberTest, other_color_second_player) {
    RuleSchieber rule;
    CardSet expected = CardSet::Zero();
    CardSet hand = CardSet::Zero();
    hand(SA) = hand(SK) = hand(H9) = hand(H8) = hand(H6) = hand(C7) = hand(C6) = 1;
    CardTrick trick = CardTrick::Constant(-1);

    // give color or trump
    trick(0) = C10;
    auto valid = rule.getValidCards(hand, trick, 1, HEARTS);
    expected(C7) = expected(C6) = expected(H9) = expected(H8) = expected(H6) = 1;
    EXPECT_TRUE(expected.isApprox(valid));
}

TEST(RuleSchieberTest, trump_forehand) {
    auto rule = std::make_shared<RuleSchieber>();
    GameSim game(rule);

    // deal random hands
    GameUtils util;
    auto hands = util.dealRandomHand();

    game.initFromCards(hands, 1);

    auto valid = rule->getFullValidActionsFromState(game.state);
    EXPECT_EQ(7, valid.sum());
    EXPECT_EQ(1, valid(TRUMP_FULL_O));
    EXPECT_EQ(1, valid(TRUMP_FULL_U));
    EXPECT_EQ(1, valid(TRUMP_FULL_D));
    EXPECT_EQ(1, valid(TRUMP_FULL_C));
    EXPECT_EQ(1, valid(TRUMP_FULL_H));
    EXPECT_EQ(1, valid(TRUMP_FULL_S));
    EXPECT_EQ(1, valid(TRUMP_FULL_P));

    game.performActionTrump(PUSH);
    // push should no longer be valid
    valid = rule->getFullValidActionsFromState(game.state);
    EXPECT_EQ(6, valid.sum());
    EXPECT_EQ(1, valid(TRUMP_FULL_O));
    EXPECT_EQ(1, valid(TRUMP_FULL_U));
    EXPECT_EQ(1, valid(TRUMP_FULL_D));
    EXPECT_EQ(1, valid(TRUMP_FULL_C));
    EXPECT_EQ(1, valid(TRUMP_FULL_H));
    EXPECT_EQ(1, valid(TRUMP_FULL_S));

    game.performActionTrump(DIAMONDS);

    // trump selection should no longer be valid
    valid = rule->getFullValidActionsFromState(game.state);
    EXPECT_EQ(0, valid(TRUMP_FULL_O));
    EXPECT_EQ(0, valid(TRUMP_FULL_U));
    EXPECT_EQ(0, valid(TRUMP_FULL_D));
    EXPECT_EQ(0, valid(TRUMP_FULL_C));
    EXPECT_EQ(0, valid(TRUMP_FULL_H));
    EXPECT_EQ(0, valid(TRUMP_FULL_S));
    EXPECT_EQ(0, valid(TRUMP_FULL_P));

    auto valid2 = rule->getValidCardsFromState(game.state);
    EXPECT_EQ(valid.sum(), valid2.sum());
}







