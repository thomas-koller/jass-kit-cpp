import numpy as np

from jass.agents.agent_random_schieber import AgentRandomSchieber
from jass.game.const import *
from jass.game.game_sim import GameSim
from jass.game.game_state import GameState
from jass.game.game_util import deal_random_hand, get_cards_encoded
from jass.game.rule_schieber import RuleSchieber

import jasscpp

game = jasscpp.GameSimCpp()
hands = deal_random_hand()
game.init_from_cards(hands=hands, dealer=NORTH)
print(game.state)
while not game.is_done():
    valid_cards = game.get_valid_cards_from_state(game.state)
    card = np.random.choice(np.flatnonzero(valid_cards))
    game.action_play_card(card)
