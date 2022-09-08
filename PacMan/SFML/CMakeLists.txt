
# define a macro that helps defining an option
macro(sfml_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# these options have to be set before CMake detects/configures the toolchain

# determine whether to create a debug or release build
sfml_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")

# Suppress Cygwin legacy warning
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# Suppress Mac OS X RPATH warnings and adopt new related behaviors
cmake_policy(SET CMP0042 NEW)
if (NOT CMAKE_VERSION VERSION_LESS 3.9)
    cmake_policy(SET CMP0068 NEW)
endif()


# project name
project(SFML)

# include the configuration file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

# setup version numbers
set(VERSION_MAJOR 2)
set(VERSION_MINOR 5)
set(VERSION_PATCH 1)

# add an option for choosing the build type (shared or static)
sfml_set_option(BUILD_SHARED_LIBS TRUE BOOL "TRUE to build SFML as shared libraries, FALSE to build it as static libraries")


# add an option for building the examples
sfml_set_option(SFML_BUILD_EXAMPLES FALSE BOOL "TRUE to build the SFML examples, FALSE to ignore them")


# add options to select which modules to build
sfml_set_option(SFML_BUILD_WINDOW TRUE BOOL "TRUE to build SFML's Window module. This setting is ignored, if the graphics module is built.")
sfml_set_option(SFML_BUILD_GRAPHICS TRUE BOOL "TRUE to build SFML's Graphics module.")
sfml_set_option(SFML_BUILD_AUDIO TRUE BOOL "TRUE to build SFML's Audio module.")
sfml_set_option(SFML_BUILD_NETWORK FALSE BOOL "TRUE to build SFML's Network module.")

# add an option for building the API documentation
sfml_set_option(SFML_BUILD_DOC FALSE BOOL "TRUE to generate the API documentation, FALSE to ignore it")

# add an option for choosing the OpenGL implementation
if(SFML_BUILD_WINDOW)
    sfml_set_option(SFML_OPENGL_ES ${OPENGL_ES} BOOL "TRUE to use an OpenGL ES implementation, FALSE to use a desktop OpenGL implementation")
endif()


# Install directories
# For miscellaneous files
set(DEFAULT_INSTALL_MISC_DIR .)

# add an option to let the user specify a custom directory for doc, examples, licence, readme and other miscellaneous files
sfml_set_option(SFML_MISC_INSTALL_PREFIX "${DEFAULT_INSTALL_MISC_DIR}" PATH "Prefix installation path for miscellaneous files")


# force building sfml-window, if sfml-graphics module is built
if(SFML_BUILD_GRAPHICS AND NOT SFML_BUILD_WINDOW)
    message(WARNING "You're trying to build SFML's Graphics module without the Window module. Forcing building of the Window module as a dependency.")
    set(SFML_BUILD_WINDOW TRUE)
endif()

# allow not using bundled dependencies with a switch
# (except for stb_image)
# yes this is horrible, but GLOB_RECURSE sucks
sfml_set_option(SFML_USE_SYSTEM_DEPS FALSE BOOL "TRUE to use system dependencies, FALSE to use the bundled ones.")
if(SFML_USE_SYSTEM_DEPS)
    if(SFML_INSTALL_XCODE_TEMPLATES)
        message(FATAL_ERROR "XCode templates installation cannot be used with the SFML_USE_SYSTEM_DEPS option (the bundled frameworks are required.)")
    endif()

    file(GLOB_RECURSE DEP_LIBS    "${CMAKE_SOURCE_DIR}/extlibs/libs*/*")
    file(GLOB_RECURSE DEP_BINS    "${CMAKE_SOURCE_DIR}/extlibs/bin*/*")
    file(GLOB_RECURSE DEP_HEADERS "${CMAKE_SOURCE_DIR}/extlibs/headers/*")

    foreach(DEP_FILE ${DEP_LIBS} ${DEP_BINS} ${DEP_HEADERS})
        get_filename_component(DEP_DIR ${DEP_FILE} PATH)

        if(NOT DEP_DIR MATCHES "/stb_image(/|$)")
            set(CMAKE_IGNORE_PATH ${CMAKE_IGNORE_PATH} ${DEP_DIR})
        endif()

        get_filename_component(DEP_PARENT_DIR ${DEP_DIR} PATH)
        while(NOT DEP_PARENT_DIR STREQUAL "${CMAKE_SOURCE_DIR}/extlibs")
            if(NOT DEP_DIR MATCHES "/stb_image(/|$)")
                set(CMAKE_IGNORE_PATH ${CMAKE_IGNORE_PATH} ${DEP_PARENT_DIR})
            endif()

            get_filename_component(DEP_PARENT_DIR ${DEP_PARENT_DIR} PATH)
        endwhile()
    endforeach()

    list(REMOVE_DUPLICATES CMAKE_IGNORE_PATH)
endif()

# Visual C++: remove warnings regarding SL security and algorithms on pointers
if(SFML_COMPILER_MSVC)
    # add an option to choose whether PDB debug symbols should be generated (defaults to true when possible)
    if(CMAKE_VERSION VERSION_LESS 3.1)
        sfml_set_option(SFML_GENERATE_PDB FALSE BOOL "True to generate PDB debug symbols, FALSE otherwise. Requires CMake 3.1.")
        if(SFML_GENERATE_PDB)
            message(FATAL_ERROR "Generation of PDB files (SFML_GENERATE_PDB) requires at least CMake 3.1.0")
        endif()
    else()
        sfml_set_option(SFML_GENERATE_PDB TRUE BOOL "True to generate PDB debug symbols, FALSE otherwise. Requires CMake 3.1.")
    endif()

    add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
endif()

# define SFML_OPENGL_ES if needed
if(SFML_OPENGL_ES)
    add_definitions(-DSFML_OPENGL_ES)
    add_definitions(-DGL_GLEXT_PROTOTYPES)
endif()

# define an option for choosing between static and dynamic C runtime (Windows only)
if(SFML_OS_WINDOWS)
    sfml_set_option(SFML_USE_STATIC_STD_LIBS FALSE BOOL "TRUE to statically link to the standard libraries, FALSE to use them as DLLs")

    # the following combination of flags is not valid
    if (BUILD_SHARED_LIBS AND SFML_USE_STATIC_STD_LIBS)
        message(FATAL_ERROR "BUILD_SHARED_LIBS and SFML_USE_STATIC_STD_LIBS cannot be used together")
    endif()

    # for VC++, we can apply it globally by modifying the compiler flags
    if(SFML_COMPILER_MSVC AND SFML_USE_STATIC_STD_LIBS)
        foreach(flag
                CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
            endif()
        endforeach()
    endif()
endif()


# enable project folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# add the subdirectories
add_subdirectory(src/SFML)
if(SFML_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(SFML_BUILD_DOC)
    add_subdirectory(doc)
endif()

# on Linux and BSD-like OS, install pkg-config files by default
set(SFML_INSTALL_PKGCONFIG_DEFAULT FALSE)

sfml_set_option(SFML_INSTALL_PKGCONFIG_FILES ${SFML_INSTALL_PKGCONFIG_DEFAULT} BOOL "TRUE to automatically install pkg-config files so other projects can find SFML")

if(SFML_INSTALL_PKGCONFIG_FILES)
    sfml_set_option(SFML_PKGCONFIG_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/${SFML_PKGCONFIG_DIR}" PATH "Install directory for SFML's pkg-config .pc files")

    foreach(sfml_module IN ITEMS all system window graphics audio network)
        CONFIGURE_FILE(
            "tools/pkg-config/sfml-${sfml_module}.pc.in"
            "tools/pkg-config/sfml-${sfml_module}.pc"
            @ONLY)
        INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/tools/pkg-config/sfml-${sfml_module}.pc"
            DESTINATION "${SFML_PKGCONFIG_INSTALL_PREFIX}")
    endforeach()
endif()

# setup the install rules
#if(NOT SFML_BUILD_FRAMEWORKS)
#    install(DIRECTORY include
#            DESTINATION .
#            COMPONENT devel
#            FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")
#
#    if(SFML_GENERATE_PDB)
#        install(DIRECTORY ${PROJECT_BINARY_DIR}/lib
#                DESTINATION .
#                COMPONENT devel
#                FILES_MATCHING PATTERN "*.pdb")
#    endif()
#else()
#    # find only "root" headers
#    file(GLOB SFML_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/SFML/*")
#
#    # in fact we have to fool cmake to copy all the headers in subdirectories
#    # to do that we have to add the "root" headers to the PUBLIC_HEADER
#    # then we can run a post script to copy the remaining headers
#
#    # we need a dummy file in order to compile the framework
#    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp
#                       COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp)
#
#    set(SFML_SOURCES ${SFML_HEADERS})
#    list(APPEND SFML_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp)
#
#    # create SFML.framework
#    add_library(SFML ${SFML_SOURCES})
#
#    # set the target flags to use the appropriate C++ standard library
#    sfml_set_stdlib(SFML)
#
#    # edit target properties
#    set_target_properties(SFML PROPERTIES
#                          FRAMEWORK TRUE
#                          FRAMEWORK_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
#                          MACOSX_FRAMEWORK_IDENTIFIER org.sfml-dev.SFML
#                          MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
#                          MACOSX_FRAMEWORK_BUNDLE_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
#                          PUBLIC_HEADER "${SFML_HEADERS}")
#
#    # add the non-optional SFML headers
#    add_custom_command(TARGET SFML POST_BUILD COMMAND cp -r
#                       ${PROJECT_SOURCE_DIR}/include/SFML/Config.hpp
#                       ${PROJECT_SOURCE_DIR}/include/SFML/OpenGL.hpp
#                       ${PROJECT_SOURCE_DIR}/include/SFML/GpuPreference.hpp
#                       ${PROJECT_SOURCE_DIR}/include/SFML/System.hpp
#                       ${PROJECT_SOURCE_DIR}/include/SFML/Main.hpp
#                       ${PROJECT_SOURCE_DIR}/include/SFML/System
#                       $<TARGET_FILE_DIR:SFML>/Headers)
#
#    # add window module headers if enabled
#    if(SFML_BUILD_WINDOW)
#        add_custom_command(TARGET SFML POST_BUILD COMMAND cp -r
#                           ${PROJECT_SOURCE_DIR}/include/SFML/Window.hpp
#                           ${PROJECT_SOURCE_DIR}/include/SFML/Window
#                           $<TARGET_FILE_DIR:SFML>/Headers)
#    endif()
#
#    # add network module headers if enabled
#    if(SFML_BUILD_NETWORK)
#        add_custom_command(TARGET SFML POST_BUILD COMMAND cp -r
#                           ${PROJECT_SOURCE_DIR}/include/SFML/Network.hpp
#                           ${PROJECT_SOURCE_DIR}/include/SFML/Network
#                           $<TARGET_FILE_DIR:SFML>/Headers)
#    endif()
#
#     # add graphics module headers if enabled
#    if(SFML_BUILD_GRAPHICS)
#        add_custom_command(TARGET SFML POST_BUILD COMMAND cp -r
#                           ${PROJECT_SOURCE_DIR}/include/SFML/Graphics.hpp
#                           ${PROJECT_SOURCE_DIR}/include/SFML/Graphics
#                           $<TARGET_FILE_DIR:SFML>/Headers)
#    endif()
#
#     # add audio module headers if enabled
#    if(SFML_BUILD_AUDIO)
#        add_custom_command(TARGET SFML POST_BUILD COMMAND cp -r
#                           ${PROJECT_SOURCE_DIR}/include/SFML/Audio.hpp
#                           ${PROJECT_SOURCE_DIR}/include/SFML/Audio
#                           $<TARGET_FILE_DIR:SFML>/Headers)
#    endif()
#
#    # adapt install directory to allow distributing dylibs/frameworks in user's frameworks/application bundle
#    # NOTE: it's not required to link against SFML.framework
#    set_target_properties(SFML PROPERTIES INSTALL_NAME_DIR "@rpath")
#    if(NOT CMAKE_SKIP_BUILD_RPATH)
#        if (CMAKE_VERSION VERSION_LESS 3.9)
#            set_target_properties(${target} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
#        else()
#            set_target_properties(${target} PROPERTIES BUILD_WITH_INSTALL_NAME_DIR TRUE)
#        endif()
#    endif()
#
#    # install rule
#    install(TARGETS SFML
#            FRAMEWORK DESTINATION "."
#            COMPONENT devel)
#endif()
#
#nstall(FILES license.md DESTINATION ${SFML_MISC_INSTALL_PREFIX})
#nstall(FILES readme.md DESTINATION ${SFML_MISC_INSTALL_PREFIX})

# install 3rd-party libraries and tools
#if(SFML_OS_WINDOWS)
#
#    if(NOT SFML_USE_SYSTEM_DEPS)
#        # install the binaries of SFML dependencies
#        if(ARCH_32BITS)
#            install(DIRECTORY extlibs/bin/x86/ DESTINATION ${SFML_DEPENDENCIES_INSTALL_PREFIX}/bin)
#            if(SFML_COMPILER_MSVC AND SFML_MSVC_VERSION LESS 14)
#                install(DIRECTORY extlibs/libs-msvc/x86/ DESTINATION ${SFML_DEPENDENCIES_INSTALL_PREFIX}/lib)
#            elseif(SFML_COMPILER_MSVC)
#                install(DIRECTORY extlibs/libs-msvc-universal/x86/ DESTINATION ${SFML_DEPENDENCIES_INSTALL_PREFIX}/lib)
#            else()
#                install(DIRECTORY extlibs/libs-mingw/x86/ DESTINATION ${SFML_DEPENDENCIES_INSTALL_PREFIX}/lib)
#            endif()
#        elseif(ARCH_64BITS)
#            install(DIRECTORY extlibs/bin/x64/ DESTINATION ${SFML_DEPENDENCIES_INSTALL_PREFIX}/bin)
#            if(SFML_COMPILER_MSVC AND SFML_MSVC_VERSION LESS 14)
#                install(DIRECTORY extlibs/libs-msvc/x64/ DESTINATION ${SFML_DEPENDENCIES_INSTALL_PREFIX}/lib)
#            elseif(SFML_COMPILER_MSVC)
#                install(DIRECTORY extlibs/libs-msvc-universal/x64/ DESTINATION ${SFML_DEPENDENCIES_INSTALL_PREFIX}/lib)
#            else()
#                install(DIRECTORY extlibs/libs-mingw/x64/ DESTINATION ${SFML_DEPENDENCIES_INSTALL_PREFIX}/lib)
#            endif()
#        endif()
#    endif()
#
#    # install the Xcode templates if requested
#    if(SFML_INSTALL_XCODE_TEMPLATES)
#        # configure the templates plist files
#        foreach(TEMPLATE "SFML Compiler" "SFML App")
#            configure_file(
#                        "tools/xcode/templates/SFML/${TEMPLATE}.xctemplate/TemplateInfo.plist.in"
#                        "${CMAKE_CURRENT_BINARY_DIR}/tools/xcode/templates/SFML/${TEMPLATE}.xctemplate/TemplateInfo.plist"
#                        @ONLY)
#        endforeach()
#        install(DIRECTORY "tools/xcode/templates/SFML" "${CMAKE_CURRENT_BINARY_DIR}/tools/xcode/templates/SFML"
#                DESTINATION /Library/Developer/Xcode/Templates
#                PATTERN "*.in" EXCLUDE
#                PATTERN ".DS_Store" EXCLUDE)
#    endif()
#
#endif()

#sfml_export_targets()
