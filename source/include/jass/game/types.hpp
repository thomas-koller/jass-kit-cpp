//
// Created by Thomas Koller on 06.11.18.
//

#ifndef JASS_TYPES_HPP
#define JASS_TYPES_HPP

#include <Eigen/Core>
#include <vector>

namespace jass {
    static const int NR_CARDS = 36;

    // Note on Eigen matrices:
    // - constructor is (row, cols)
    // - access is row index first, then col
    // - one dimensional arrays (cols or row vector) can be accesses with one index
    // access: row index is first

    // Set of cards, with a value of 0 or 1 depending if the card on the index is in the set
    typedef Eigen::Array<int, NR_CARDS, 1> CardSet;

    // Set of cards for each player
    typedef Eigen::Array<int, 4, NR_CARDS> CardSetPlayer;

    // All tricks in the order of tricks (row) and order of cards played (col)
    typedef Eigen::Array<int, 9, 4> CardAllTricks;
    typedef Eigen::Array<int, 4, 1> CardTrick;
    typedef Eigen::Array<int, 9, 1> TrickWinner;
    typedef Eigen::Array<int, 9, 1> TrickPlayer;
    typedef Eigen::Array<int, 9, 1> TrickPoints;

    // for list of cards, we use the standard vector class, that seems easier and supports iterators
    typedef std::vector<int> CardList;

    // results for action probabilities

    struct ResultPlayCardAction {
        Eigen::Array<float, 36, 1> probability;
        Eigen::Array<float, 36, 1> reward;
    };

    struct ResultTrumpAction {
        Eigen::Array<float, 7, 1> probability;
        Eigen::Array<float, 7, 1> reward;
    };

    // Card Distribution Probabilities
    typedef Eigen::Array<float, 4 /* rows */, NR_CARDS /* cols */> CardProbabilities;
}


#endif //JASS_TYPES_HPP
