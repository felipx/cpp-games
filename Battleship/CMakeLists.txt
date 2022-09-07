# CMakeList.txt : CMake project for Battleship
#
#
cmake_minimum_required (VERSION 3.8)

project ("Battleship")

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -Werror)
endif()

# include directory 
include_directories(include)

# .cpp files
#add_executable (main "src/main.cpp" "src/Controller.cpp" "src/State.cpp" "src/Game.cpp" "src/Menu.cpp")
add_executable (main "src/main.cpp" "src/Controller.cpp" "src/State.cpp" "src/Game.cpp" "src/Bot.cpp" "src/Positions.cpp" "src/Menu.cpp" "src/Ship.cpp" "src/Player.cpp" "src/Entity.cpp")

# TESTS
add_subdirectory (tests)