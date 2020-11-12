//
// Created by Thomas Koller on 06.11.18.
//

#ifndef JASS_RULESCHIEBER_HPP
#define JASS_RULESCHIEBER_HPP

#include "jass/game/GameRule.hpp"

namespace jass {
    class RuleSchieber;
}

/**
 * Rules for Schieber.
 */
class jass::RuleSchieber : public GameRule {

public:
    typedef std::shared_ptr<RuleSchieber> Ptr;

    explicit RuleSchieber();

    /// @copydoc Rule::getValidCards()
    CardSet getValidCards(const CardSet &hand, const CardTrick &trick, int card_nr, int trump) override;

    /// @copydoc Rule::calcPoints()
    int calcPoints(const CardTrick &trick, bool is_last_card, int trump) override;

    /// @copydoc Rule::calcWinner()
    int calcWinner(const CardTrick &trick, int first_player, int trump) override;

    /// check invariants for this rule and state
    void assertInvariants(const GameState &state) const override;

    /// check invariants for this rule and obs
    void assertInvariants(const GameObservation &obs) const override;

private:
    Eigen::Array<int, 36, 36> higher_trump;
    Eigen::Array<int, 36, 36> lower_trump;

    Eigen::Array<int, 6, 36> card_values;


};

#endif //JASS_RULESCHIEBER_HPP
