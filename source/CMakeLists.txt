set (INCLUDE_FILES
        include/jass/game/types.hpp
        include/jass/game/const.hpp
        include/jass/game/GameRule.hpp
        include/jass/game/RuleSchieber.hpp
        include/jass/game/GameSim.hpp
        include/jass/game/GameObservation.hpp
        include/jass/game/GameState.hpp
        include/jass/game/GameStateUtils.hpp
        include/jass/game/GameUtils.hpp
        include/jass/agents/JassAgent.hpp
        include/jass/agents/JassAgentRandom.hpp
        include/jass/agents/JassAgentCheating.hpp
        )

set (SOURCE_FILES
        src/jass/game/RuleSchieber.cpp
        src/jass/game/GameSim.cpp
        src/jass/game/GameObservation.cpp
        src/jass/game/GameState.cpp
        src/jass/agents/JassAgentRandom.cpp
        src/jass/game/GameStateUtils.cpp
        )


set (SOURCE_FILES_PYBIND
        src/jass/interface/GameSimModule.cpp)

set (JASS_LIB jass)
set (JASS_LIB_STATIC jass_static)


add_library(${JASS_LIB} SHARED ${SOURCE_FILES}  )
add_library(${JASS_LIB_STATIC}  ${SOURCE_FILES})

# pybind11_add_module(jasscpp ${SOURCE_FILES} ${SOURCE_FILES_PYBIND})

SET_TARGET_PROPERTIES( ${JASS_LIB}
        PROPERTIES
        DEBUG_OUTPUT_NAME ${JASS_LIB}_debug
        RELEASE_OUTPUT_NAME ${JASS_LIB}
        )

SET_TARGET_PROPERTIES( ${JASS_LIB_STATIC}
        PROPERTIES
        DEBUG_OUTPUT_NAME ${JASS_LIB_STATIC}_debug
        RELEASE_OUTPUT_NAME ${JASS_LIB_STATIC}
        )

install(TARGETS ${JASS_LIB} ${JASS_LIB_STATIC}
        EXPORT ${JASS_LIB}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
       )

# install with preserving structure
install(
        DIRECTORY ${CMAKE_SOURCE_DIR}/source/include/jass
        EXPORT ${JASS_LIB}
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp"
)

install(EXPORT ${JASS_LIB} DESTINATION lib/jass)
