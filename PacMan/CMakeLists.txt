# CMakeList.txt : CMake project for PacMan
#
#
cmake_minimum_required (VERSION 3.8)

#
project ("PacMan")

#
set(PacMan_VERSION_MAJOR "1")
set (PacMan_VERSION_MINOR "0")
set(PacMan_VERSION_PATCH "0")

# C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#
include_directories(include)
include(FetchContent)

#set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

#
set(debugName "x64-debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/out/build/${debugName}/bin)
set(releaseName "x64-release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/out/build/${releaseName}/bin)

#
add_executable (PacMan "AppIcon.rc" "src/main.cpp" "src/Entity.cpp" "src/PacMan.cpp" "src/Ghost.cpp" "src/GameController.cpp" "src/State.cpp" "src/Game.cpp" "src/Menu.cpp" "src/Map.cpp" "src/Dots.cpp" "src/Publisher.cpp" "src/Strategy.cpp" "src/Chase.cpp" "src/Scatter.cpp" "src/Frightened.cpp")

#
#add_subdirectory (SFML)

#
target_link_libraries(PacMan sfml-audio sfml-graphics #sfml-main
                      sfml-system sfml-window)

#
if (MSVC)
    set_property(TARGET PacMan PROPERTY WIN32_EXECUTABLE true)

    add_custom_command(TARGET PacMan POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:PacMan> 
                       $<TARGET_FILE_DIR:PacMan> COMMAND_EXPAND_LISTS
                      )
endif()

#
file(COPY "${CMAKE_SOURCE_DIR}/media" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# TESTS
add_subdirectory (tests)

#
install(TARGETS PacMan DESTINATION bin)
install(FILES "media/images/Ghost16.png" "media/images/Pacman16.png" "media/images/PacmanDeath16.png" "media/images/Map16.png" DESTINATION media/images)
install(FILES "media/fonts/namco.ttf" "media/fonts/pac-font.ttf" DESTINATION media/fonts)

#
if (MSVC)
    set(CPACK_PACKAGE_VERSION "1.0.0")
    set(CPACK_SOURCE_GENERATOR "TGZ")
    #
    #set(CPACK_NSIS_MODIFY_PATH "ON")
    
    #
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/media/images/pacman.ico")
    set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/media/images/pacman.ico")
    #
    set(CPACK_NSIS_INSTALLED_ICON_NAME "Uninstall.exe")
    #
    set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/media/images\\\\pacman.bmp")
    #
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "PacMan ${PacMan_VERSION_MAJOR}.${PacMan_VERSION_MINOR}.${PacMan_VERSION_PATCH}")
    
    #
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
    
    #
    set(CPACK_PACKAGE_VENDOR "felipx")
    
    #
    #set(CPACK_CREATE_DESKTOP_LINKS PacMan)
    
    #
    #set(CPACK_PACKAGE_EXECUTABLES "PacMan" "pacman" )
    
    #
    #set(CPACK_NSIS_MENU_LINKS "bin/PacMan.exe" "PacMan" "Uninstall.exe" "Uninstall")
    
    #
    set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
        SetOutPath '$INSTDIR\\\\bin'
        CreateShortCut \\\"$DESKTOP\\\\PacMan.lnk\\\" \\\"$INSTDIR\\\\bin\\\\PacMan.exe\\\"
    ")
    set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
        Delete \\\"$DESKTOP\\\\PacMan.lnk\\\"
    ")

    get_cmake_property(CPACK_COMPONENTS_ALL COMPONENTS)
    list(REMOVE_ITEM CPACK_COMPONENTS_ALL "devel" "lib")
    include(CPack)
endif()