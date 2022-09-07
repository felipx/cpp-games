# CMakeList.txt : CMake project for Battleship
#
#
cmake_minimum_required (VERSION 3.8)

project ("Battleship")

add_executable (initPositionsTest "initPositionsTest.cpp" "../src/Positions.cpp")
add_executable (stackPositionsTest "stackPositionsTest.cpp" "../src/Positions.cpp")
add_executable (setShipPositionsTest "setShipPositionTest.cpp" "../src/Ship.cpp")
add_executable (botShipsTest "botShipsTest.cpp" "../src/Entity.cpp" "../src/Bot.cpp" "../src/Positions.cpp" "../src/Ship.cpp")