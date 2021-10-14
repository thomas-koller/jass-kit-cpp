#
# Simple test for the inclusion of the cpp extension library for jass
#
from jass.game.const import *
from jass.game.game_util import deal_random_hand

import jasscpp

game = jasscpp.GameSimCpp()
rule = jasscpp.RuleSchieberCpp()
hands = deal_random_hand()
game.init_from_cards(hands, SOUTH)
game.perform_action_trump(OBE_ABE)
print(game.state)
print(game.state.dealer)
while not game.is_done():
    obs = jasscpp.observation_from_state(game.state, -1 )
    print(obs)
    # check both methods to obtain valid cards to test additional functions
    valid_cards = rule.get_valid_cards(obs.hand, obs.tricks[obs.current_trick], obs.nr_cards_in_trick, obs.trump)
    valid_cards2 = game.get_valid_cards()
    assert (valid_cards == valid_cards2).all()

    player = game.state.player
    card = np.random.choice(np.flatnonzero(valid_cards))
    print(card)
    game.perform_action_play_card(card)

    # check that card removed from original hands, and hands from the game are the same
    hands[player, card] = 0
    assert (hands == game.state.hands).all()
