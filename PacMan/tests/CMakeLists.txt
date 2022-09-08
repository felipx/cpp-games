# CMakeList.txt : CMake project for PacMan, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("PacMan")

#TESTS
if (CMAKE_BUILD_TYPE STREQUAL Debug)

#---PacManImageTest---
add_executable (PacManImageTest "../src/Entity.cpp" "../src/PacMan.cpp" "../src/Map.cpp" "PacManImageTest.cpp" )

target_link_libraries(PacManImageTest sfml-graphics sfml-main
                      sfml-system sfml-window)

#---GhostImageTest---
add_executable (GhostImageTest "../src/Entity.cpp" "../src/PacMan.cpp" "../src/Map.cpp" "GhostImageTest.cpp" "../src/Ghost.cpp" "../src/Strategy.cpp" "../src/Chase.cpp")

target_link_libraries(GhostImageTest sfml-graphics sfml-main
                      sfml-system sfml-window)

#---MapImageTest---
add_executable (mapImageTest "../src/Map.cpp" "mapImageTest.cpp" "../src/Dots.cpp")

target_link_libraries(mapImageTest sfml-graphics sfml-main
                      sfml-system sfml-window)

#---MenuImageTest---
add_executable (menuImageTest "../src/Map.cpp" "../src/PacMan.cpp" "../src/Game.cpp" "../src/Entity.cpp" "../src/Ghost.cpp" "../src/Menu.cpp" "../src/GameController.cpp" "MenuImageTest.cpp" "../src/State.cpp" "../src/Dots.cpp" "../src/Publisher.cpp" "../src/Strategy.cpp" "../src/Chase.cpp" "../src/Scatter.cpp" "../src/Frightened.cpp")

target_link_libraries(menuImageTest sfml-graphics sfml-main
                        sfml-system sfml-window)

#---ScoreTest---
add_executable (ScoreTest "../src/Map.cpp" "../src/PacMan.cpp" "../src/Game.cpp" "../src/Entity.cpp" "../src/Ghost.cpp" "../src/Menu.cpp" "../src/GameController.cpp" "MenuImageTest.cpp" "../src/State.cpp" "../src/Dots.cpp" "../src/Publisher.cpp" "../src/Strategy.cpp" "../src/Chase.cpp" "../src/Scatter.cpp" "../src/Frightened.cpp" )

target_link_libraries(ScoreTest sfml-graphics sfml-main
                      sfml-system sfml-window)

#---PacManWallTest---
add_executable (PacManWallTest  "../src/Map.cpp" "../src/PacMan.cpp" "../src/Game.cpp" "../src/Entity.cpp" "../src/Ghost.cpp" "../src/Menu.cpp" "../src/GameController.cpp" "PacManWallTest.cpp" "../src/State.cpp" "../src/Dots.cpp" "../src/Publisher.cpp" "../src/Strategy.cpp" "../src/Chase.cpp" "../src/Scatter.cpp" "../src/Frightened.cpp" )

target_link_libraries(PacManWallTest sfml-graphics sfml-main
                      sfml-system sfml-window)

#---StrategyTest---
add_executable (StrategyTest "../src/Ghost.cpp" "../src/Chase.cpp" "../src/Entity.cpp" "../src/Map.cpp" "../src/PacMan.cpp" "../src/Strategy.cpp" "StrategyTest.cpp" "../src/State.cpp" "../src/Scatter.cpp" )

target_link_libraries(StrategyTest sfml-graphics sfml-main
                      sfml-system sfml-window)

#---GhostEatenTest---
add_executable (GhostEatenTest "../src/Ghost.cpp" "../src/Chase.cpp" "../src/Entity.cpp" "../src/Map.cpp" "../src/PacMan.cpp" "../src/Strategy.cpp" "GhostEatenTest.cpp" "../src/State.cpp" "../src/Scatter.cpp" )

target_link_libraries(GhostEatenTest sfml-graphics sfml-main
                      sfml-system sfml-window)

#---GhostDirectionTest---
add_executable (GhostDirectionTest "../src/Ghost.cpp" "../src/Chase.cpp" "../src/Entity.cpp" "../src/Map.cpp" "../src/PacMan.cpp" "../src/Strategy.cpp" "GhostDirectionTest.cpp" "../src/State.cpp" "../src/Scatter.cpp" )

target_link_libraries(GhostDirectionTest sfml-graphics sfml-main
                      sfml-system sfml-window)

#---PacManDirectionTest---
add_executable (PacManDirectionTest "../src/Ghost.cpp" "../src/Chase.cpp" "../src/Entity.cpp" "../src/Map.cpp" "../src/PacMan.cpp" "../src/Strategy.cpp" "PacManDirectionTest.cpp" "../src/State.cpp" "../src/Scatter.cpp" )

target_link_libraries(PacManDirectionTest sfml-graphics sfml-main
                      sfml-system sfml-window)

#---PacManSpriteTest---
add_executable (PacManSpriteTest "../src/Ghost.cpp" "../src/Chase.cpp" "../src/Entity.cpp" "../src/Map.cpp" "../src/PacMan.cpp" "../src/Strategy.cpp" "PacManSpriteTest.cpp" "../src/State.cpp" "../src/Scatter.cpp" )

target_link_libraries(PacManSpriteTest sfml-graphics sfml-main
                      sfml-system sfml-window)

#---PacManMoveTest---
add_executable (pacmanMoveTest "PacManMoveTest.cpp" "../src/Map.cpp" "../src/PacMan.cpp" "../src/Game.cpp" "../src/Entity.cpp" "../src/Ghost.cpp" "../src/Menu.cpp" "../src/GameController.cpp" "../src/State.cpp" "../src/Dots.cpp" "../src/Strategy.cpp" "../src/Scatter.cpp" "../src/Chase.cpp" "../src/Frightened.cpp" "../src/Publisher.cpp")

target_link_libraries(pacmanMoveTest sfml-graphics sfml-main
                        sfml-system sfml-window)

#---SetDifficultyTest---
add_executable (SetDifficulty "PacManMoveTest.cpp" "../src/Map.cpp" "../src/PacMan.cpp" "../src/Game.cpp" "../src/Entity.cpp" "../src/Ghost.cpp" "../src/Menu.cpp" "../src/GameController.cpp" "../src/State.cpp" "../src/Dots.cpp" "../src/Strategy.cpp" "../src/Scatter.cpp" "../src/Chase.cpp" "../src/Frightened.cpp" "../src/Publisher.cpp")

target_link_libraries(SetDifficulty sfml-graphics sfml-main
                        sfml-system sfml-window)


#---pacmanGhostCollisionTest---
add_executable (pacmanGhostCollisionTest "PacManGhostCollisionTest.cpp" "../src/Map.cpp" "../src/PacMan.cpp" "../src/Game.cpp" "../src/Entity.cpp" "../src/Ghost.cpp" "../src/Menu.cpp" "../src/GameController.cpp" "../src/State.cpp" "../src/Dots.cpp" "../src/Strategy.cpp" "../src/Scatter.cpp" "../src/Chase.cpp" "../src/Frightened.cpp" "../src/Publisher.cpp")

target_link_libraries(pacmanGhostCollisionTest sfml-graphics sfml-main
                        sfml-system sfml-window)


#---GhosthWallTest---
add_executable (GhostWallTest "GhostWallTest.cpp" "../src/Map.cpp" "../src/PacMan.cpp" "../src/Game.cpp" "../src/Entity.cpp" "../src/Ghost.cpp" "../src/Menu.cpp" "../src/GameController.cpp" "../src/State.cpp" "../src/Dots.cpp" "../src/Strategy.cpp" "../src/Scatter.cpp" "../src/Chase.cpp" "../src/Frightened.cpp" "../src/Publisher.cpp")

target_link_libraries(GhostWallTest sfml-graphics sfml-main
                        sfml-system sfml-window)

#---GhostMoveTest---
add_executable (GhostMoveTest "GhostMoveTest.cpp" "../src/Map.cpp" "../src/PacMan.cpp" "../src/Game.cpp" "../src/Entity.cpp" "../src/Ghost.cpp" "../src/Menu.cpp" "../src/GameController.cpp" "../src/State.cpp" "../src/Dots.cpp" "../src/Strategy.cpp" "../src/Scatter.cpp" "../src/Chase.cpp" "../src/Frightened.cpp" "../src/Publisher.cpp")

target_link_libraries(GhostMoveTest sfml-graphics sfml-main
                        sfml-system sfml-window)

#add_executable (test "src/State.cpp" "src/Menu.cpp" "tests/test.cpp" )

#target_link_libraries(test sfml-graphics sfml-main
#                      sfml-system sfml-window)

endif()