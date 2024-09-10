cmake_minimum_required(VERSION 3.10)
project(rxcurses C)

set(CMAKE_C_STANDARD 90)

# If Windows build the pdcurses library from the pdcurses source directory
if(WIN32)

    set(PDC_BUILD_SHARED OFF)
    set(PDC_UTF8 ON)
    set(PDC_FORCE_UTF8 ON)
    set(PDC_WIDE OFF)
    set(PDCDEBUG OFF)
    set(PDC_CHTYPE_32 OFF)
    set(PDC_DOS_BUILD OFF)
    set(PDC_DOSVGA_BUILD OFF)
    set(PDC_SDL2_BUILD OFF)
    set(PDC_SDL2_DEPS_BUILD OFF)
    set(PDC_GL_BUILD OFF)

    add_subdirectory(pdcurses)

    # set pdcurses Locations
    set(PDCURSES_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/pdcurses" )
    set(PDCURSES_LIBRARY "${CMAKE_BINARY_DIR}/pdcurses/wincon/libpdcursesstatic.a")

    # Include the PDCurses headers
    include_directories("${PDCURSES_INCLUDE_DIR}")
    set(CURSES_LIBRARY ${PDCURSES_LIBRARY})
    set(CURSES_INCLUDE_DIR ${PDCURSES_INCLUDE_DIR})
    set(PDCURSES TRUE)

    # Define PDCURSES_STATIC to ensure static linking
    add_definitions(-DPDCURSES_STATIC)
    add_definitions(-DPDCURSES)

    # Define PDC_UTF8 and PDC_FORCE_UTF8 to enable UTF-8 support
    add_definitions(-DPDC_UTF8)
    add_definitions(-DPDC_FORCE_UTF8)

else()

    # Else use the ncurses library
    # Find the Curses package
    find_package(Curses REQUIRED)

    # Check if ncursesw was found
    if(CURSES_LIBRARY MATCHES ".*cursesw.*")
        message(STATUS "Found wide character version of ncurses: ${CURSES_LIBRARY}")
        # Define USE_UTF8 to enable UTF-8 support
        add_definitions(-DUSE_UTF8)
    else()
        # If it didn't find the wide version, you may need to manually specify it
        find_library(CURSES_LIBRARY ncursesw REQUIRED)
        if(CURSES_LIBRARY)
            message(STATUS "Manually found ncursesw: ${CURSES_LIBRARY}")
            # Define USE_UTF8 to enable UTF-8 support
            add_definitions(-DUSE_UTF8)
        else()
            message(WARNING "ncursesw not found - UTF-8 support will be disabled")
            # Don't define USE_UTF8
        endif()
    endif()
endif()

# Include the Curses headers
include_directories(${CURSES_INCLUDE_DIR})

# Including RXPlugin Build System
include(${CMAKE_SOURCE_DIR}/rxpa/RXPluginFunction.cmake)

# Create dynamic plugin module
add_dynamic_plugin_target(curses rxcurses.c)
target_include_directories(curses PRIVATE "${CURSES_INCLUDE_DIR}")
target_link_libraries(curses ${CURSES_LIBRARY})

# Add dependency on the pdcurses library and use static linking
if(PDCURSES)
    target_link_libraries(curses ${CURSES_LIBRARY} winmm)
    add_dependencies(curses wincon_pdcursesstatic)
    target_link_libraries(curses "${CMAKE_CURRENT_BINARY_DIR}/pdcurses/wincon/libpdcursesstatic.a")
    target_compile_definitions(curses PRIVATE PDCURSES_STATIC)

    # vt terminal version
    add_dynamic_plugin_target(cursesvt rxcurses.c)
    target_include_directories(cursesvt PRIVATE "${CURSES_INCLUDE_DIR}")
    add_dependencies(cursesvt vt_pdcursesstatic)
    target_link_libraries(cursesvt "${CMAKE_CURRENT_BINARY_DIR}/pdcurses/vt/libpdcursesstatic.a" winmm)
    target_compile_definitions(cursesvt PRIVATE PDCURSES_STATIC)

    # wingui terminal version
    add_dynamic_plugin_target(curseswingui rxcurses.c)
    target_include_directories(curseswingui PRIVATE "${CURSES_INCLUDE_DIR}")
    add_dependencies(curseswingui wingui_pdcursesstatic)
    target_link_libraries(curseswingui "${CMAKE_CURRENT_BINARY_DIR}/pdcurses/wingui/libpdcursesstatic.a" winmm)
    target_compile_definitions(curseswingui PRIVATE PDCURSES_STATIC)

endif()

# Build Integration Test - Rexx
add_custom_command(
        COMMAND rxc -i \"${CMAKE_CURRENT_BINARY_DIR}\" -o rxcurses_integration_test \"${CMAKE_CURRENT_SOURCE_DIR}/rxcurses_integration_test\" && rxas rxcurses_integration_test
        DEPENDS curses ${CMAKE_CURRENT_SOURCE_DIR}/rxcurses_integration_test.rexx
        OUTPUT rxcurses_integration_test.rxbin
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_target(rxcurses_integration_test ALL
        DEPENDS rxcurses_integration_test.rxbin
)

# Build Demonstrator
add_custom_command(
        COMMAND rxc -i \"${CMAKE_CURRENT_BINARY_DIR}\" -o demo \"${CMAKE_CURRENT_SOURCE_DIR}/demo\"  && rxas demo
        DEPENDS curses ${CMAKE_CURRENT_SOURCE_DIR}/demo.rexx
        OUTPUT demo.rxbin
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_target(demo ALL
        DEPENDS demo.rxbin
)

# Enable testing functionality
enable_testing()

# Dynamic Execution Test
add_test(NAME rxcurses_integration_test
        COMMAND rxvme rxcurses_integration_test rxcurses
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

set_tests_properties(rxcurses_integration_test PROPERTIES ENVIRONMENT "TERM=xterm-256color")

