set (SOURCE_FILES
        include/jass/game/types.hpp
        include/jass/game/const.hpp
        include/jass/game/GameRule.hpp
        include/jass/game/RuleSchieber.hpp
        src/jass/game/RuleSchieber.cpp
        src/jass/game/GameSim.cpp
        include/jass/game/GameSim.hpp
        src/jass/game/GameObservation.cpp
        include/jass/game/GameObservation.hpp
        src/jass/game/GameState.cpp
        include/jass/game/GameState.hpp
        include/jass/game/GameStateUtils.hpp
        include/jass/game/GameUtils.hpp
        include/jass/agents/JassAgent.hpp
        src/jass/agents/JassAgentRandom.cpp
        include/jass/agents/JassAgentRandom.hpp
        src/jass/game/GameStateUtils.cpp)

set (JASS_LIB jass)


add_library(${JASS_LIB} SHARED ${SOURCE_FILES})

SET_TARGET_PROPERTIES( ${JASS_LIB}
        PROPERTIES
        DEBUG_OUTPUT_NAME ${JASS_LIB}_debug
        RELEASE_OUTPUT_NAME ${JASS_LIB}
        )