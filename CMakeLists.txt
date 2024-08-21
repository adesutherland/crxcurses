cmake_minimum_required(VERSION 3.9)
project(rxcurses C)

set(CMAKE_C_STANDARD 90)

# Including RXPlugin Build System
include(${CMAKE_SOURCE_DIR}/rxpa/RXPluginFunction.cmake)

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

# Include the Curses headers
include_directories(${CURSES_INCLUDE_DIR})

# Create dynamic plugin module
add_dynamic_plugin_target(curses rxcurses.c)
target_link_libraries(curses ${CURSES_LIBRARIES})

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

