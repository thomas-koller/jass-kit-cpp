
set (SOURCE_FILES
        const_test.cpp
        rule_schieber_points_test.cpp
        rule_schieber_test.cpp
        rule_schieber_winner_test.cpp
        GameSimTest.cpp
        GameObservationTest.cpp JassAgentTest.cpp)

set(TESTSET_NAME jass_tests)

add_executable(${TESTSET_NAME} ${SOURCE_FILES})
target_link_libraries(${TESTSET_NAME} jass gtest_main)
add_test(NAME ${TESTSET_NAME} COMMAND ${TESTSET_NAME})
