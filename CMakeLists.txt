cmake_minimum_required (VERSION 2.8.11)
project (mkmotd C)

SET(PROGRAM_NAME "mkmotd")
SET(VERSION_MAJOR 1)
SET(VERSION_MINOR 0)
SET(VERSION_PATCH 0)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra -std=gnu99")

set(MOTD "/etc/motd" CACHE PATH "message of the day file (/etc/motd)")
set(MOTD_DIR "/etc/motd.d" CACHE PATH "directory of message of day files (/etc/motd.d)")

configure_file( "${PROJECT_SOURCE_DIR}/src/config.h.in" "${PROJECT_SOURCE_DIR}/src/config.h" )
add_executable(mkmotd src/mkmotd.c src/utils.c)

install(TARGETS mkmotd RUNTIME DESTINATION bin)
install(DIRECTORY DESTINATION ${MOTD_DIR})

install(DIRECTORY man DESTINATION share)
