//
// Created by Thomas Koller on 11/10/2021.
//

#include <pybind11/pybind11.h>
#include <iostream>
#include <jass/game/GameSim.hpp>
#include <jass/game/RuleSchieber.hpp>
#include <jass/game/GameUtils.hpp>
#include <jass/game/GameStateUtils.hpp>
#include <pybind11/eigen.h>

namespace py = pybind11;

/**
 * Module for python interface to the cpp classes.
 *
 * Most classes and methods are mapped directly, with some small changes:
 * - The GameSimCpp does not support a rule argument, but will instantiate a RuleSchieber object as the rule.
 *   (this is the only one currently implemented)
 * - The conversion between numpy arrays and the eigen arrays here should be done automatically. However, as
 *   most of the 3D arrays (AllTricks, CardSetPlayer) are not in the RowMajor order which is the natural layout
 *   of numpy arrays, those values will always be copied.
 */
PYBIND11_MODULE(jasscpp, m) {
    m.doc() = "Binding to cpp jass interface";
    py::class_<jass::GameState>(m, "GameStateCpp")
            .def_readwrite("dealer", &jass::GameState::dealer)
            .def_readwrite("player", &jass::GameState::player)
            .def_readwrite("trump", &jass::GameState::trump)
            .def_readwrite("declared_trump_player", &jass::GameState::declared_trump_player)
            .def_readwrite("forehand", &jass::GameState::forehand)
            .def_readwrite("hands", &jass::GameState::hands)
            .def_readwrite("tricks", &jass::GameState::tricks)
            .def_readwrite("trick_winner", &jass::GameState::trick_winner)
            .def_readwrite("trick_first_player", &jass::GameState::trick_first_player)
            .def_readwrite("trick_points", &jass::GameState::trick_points)
            .def_readwrite("current_trick", &jass::GameState::current_trick)
            .def_readwrite("nr_cards_in_trick", &jass::GameState::nr_cards_in_trick)
            .def_readwrite("nr_played_cards", &jass::GameState::nr_played_cards)
            .def_readwrite("points", &jass::GameState::points)
            .def("__repr__",[](const jass::GameState& state) {
                Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", " ", "", "", "[", "]");
                std::stringstream s;
                s << "GameStateCpp: " <<
                  "dealer: " << state.dealer <<
                  " player: " << state.player <<
                  " trump: " << state.trump <<
                  " declared: " << state.declared_trump_player <<
                  " forehand: " << state.forehand <<
                  " hand: " << state.hands.format(OctaveFmt) <<
                  " tricks: " << state.tricks.format(OctaveFmt) <<
                  " trick_winner: " << state.trick_winner.format(OctaveFmt) <<
                  " trick_first: " << state.trick_first_player.format(OctaveFmt) <<
                  " trick_points: " << state.trick_points.format(OctaveFmt) <<
                  " current_trick: " << state.current_trick <<
                  " nr_cards_in_trick: " << state.nr_cards_in_trick <<
                  " nr_played_cards: " << state.nr_played_cards;
                return s.str();
            });

    py::class_<jass::GameObservation>(m, "GameObservationCpp")
            .def_readwrite("dealer", &jass::GameObservation::dealer)
            .def_readwrite("player", &jass::GameObservation::player)
            .def_readwrite("trump", &jass::GameObservation::trump)
            .def_readwrite("declared_trump_player", &jass::GameObservation::declared_trump_player)
            .def_readwrite("forehand", &jass::GameObservation::forehand)
            .def_readwrite("hand", &jass::GameObservation::hand)
            .def_readwrite("tricks", &jass::GameObservation::tricks)
            .def_readwrite("trick_winner", &jass::GameObservation::trick_winner)
            .def_readwrite("trick_first_player", &jass::GameObservation::trick_first_player)
            .def_readwrite("trick_points", &jass::GameObservation::trick_points)
            .def_readwrite("current_trick", &jass::GameObservation::current_trick)
            .def_readwrite("nr_cards_in_trick", &jass::GameObservation::nr_cards_in_trick)
            .def_readwrite("nr_played_cards", &jass::GameObservation::nr_played_cards)
            .def_readwrite("points", &jass::GameObservation::points)
            .def("__repr__",[](const jass::GameObservation& obs) {
                Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", " ", "", "", "[", "]");
                std::stringstream s;
                s << "GameObservationCpp: " <<
                       "dealer: "  << obs.dealer <<
                       " player: " << obs.player <<
                       " trump: " << obs.trump <<
                       " declared: " << obs.declared_trump_player <<
                       " forehand: " << obs.forehand <<
                       " hand: " << obs.hand.format(OctaveFmt) <<
                       " tricks: " << obs.tricks.format(OctaveFmt) <<
                       " trick_winner: " << obs.trick_winner.format(OctaveFmt) <<
                       " trick_first: " << obs.trick_first_player.format(OctaveFmt) <<
                       " trick_points: " << obs.trick_points.format(OctaveFmt) <<
                       " current_trick: " << obs.current_trick <<
                       " nr_cards_in_trick: " << obs.nr_cards_in_trick <<
                       " nr_played_cards: " << obs.nr_played_cards;
                return s.str();
            });

    py::class_<jass::GameSim>(m, "GameSimCpp")
            .def(py::init([](){auto rule = std::make_shared<jass::RuleSchieber>();return jass::GameSim(rule);}))
            .def("init_from_cards", &jass::GameSim::initFromCards,
                    "Initialise the game from given cards",
                    py::arg("hands"), py::arg("dealer"))
            .def("perform_action_play_card", &jass::GameSim::performActionPlayCard,
                    "play a card in the simulation", py::arg("card"))
            .def("perform_action_trump", &jass::GameSim::performActionTrump,
                    "select trump in the simulation", py::arg("trump"))
            .def("perform_action_full", &jass::GameSim::performActionFull,
                    "perform a full action, either trump or play card",
                    py::arg("action"))
            .def("get_valid_cards", &jass::GameSim::getValidCards)
            .def("is_done", &jass::GameSim::isDone)
            .def_readwrite("state", &jass::GameSim::state);

    py::class_<jass::RuleSchieber>(m, "RuleSchieberCpp")
            .def(py::init())
            .def("get_valid_cards", &jass::RuleSchieber::getValidCards)
            .def("get_valid_cards_from_state", &jass::RuleSchieber::getValidCardsFromState)
            .def("get_valid_cards_from_obs", &jass::RuleSchieber::getFullValidActionsFromObs)
            .def("get_full_valid_actions_from_state", &jass::RuleSchieber::getFullValidActionsFromState)
            .def("get_full_valid_actions_from_obs", &jass::RuleSchieber::getFullValidActionsFromObs);


    py::class_<jass::GameUtils>(m, "GameUtilsCpp")
            .def(py::init())
            .def("deal_random_hand", &jass::GameUtils::dealRandomHand)
            .def("deal_hands", &jass::GameUtils::dealHands);

    m.def("observation_from_state", &jass::observationFromState);
    m.def("state_from_observation", &jass::stateFromObservation);
}
