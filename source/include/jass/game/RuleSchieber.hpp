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

    /// @copydoc Rule::get_valid_cards()
    CardSet get_valid_cards(const CardSet &hand, const CardTrick &trick, int card_nr, int trump) override;

    /// @copydoc Rule::calc_points()
    int calc_points(const CardTrick &trick, bool is_last_card, int trump) override;

    /// @copydoc Rule::calc_winner()
    int calc_winner(const CardTrick &trick, int first_player, int trump) override;

    /// check invariants for this rule and state
    void assert_invariants(const GameState &state) const;

    /// check invariants for this rule and obs
    void assert_invariants(const GameObservation &obs) const;

private:
    Eigen::Array<int, 36, 36> higher_trump;
    Eigen::Array<int, 36, 36> lower_trump;

    Eigen::Array<int, 6, 36> card_values;


};

#endif //JASS_RULESCHIEBER_HPP
