cmake_minimum_required(VERSION 3.14)
project(musidy)

set(CMAKE_CXX_STANDARD 14)

include(FindPkgConfig)
pkg_check_modules(PORTAUDIO portaudio-2.0)
pkg_check_modules(PORTAUDIOCPP portaudiocpp)
include_directories(${PORTAUDIO_INCLUDE_DIRS})

add_library(
        musidy SHARED
        source/SoundSystem.cpp
        include/musidy/libs/tsf.cpp
        source/Instrument.cpp
        source/songCreation/ScorePlayer.cpp
        source/utils.cpp
        source/songCreation/MusicScore.cpp
        source/songCreation/ScoreGenerator.cpp
        source/songCreation/chordProgressions.cpp
        source/songCreation/noteUtils.cpp
        source/Musidy.cpp include/musidy/Musidy.hpp)
target_include_directories(
        musidy
        PUBLIC $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(musidy ${PORTAUDIOCPP_LIBRARIES})

include(GNUInstallDirs)
install(
        TARGETS musidy
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_LIBDIR}/musidy
)
INSTALL(
        DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION include
)
foreach (LIB ${PORTAUDIOCPP_LIBRARIES})
    IF (NOT LIB MATCHES "^-")
        set(PRIVATE_LIBS "${PRIVATE_LIBS} -l${LIB}")
    ENDIF (NOT LIB MATCHES "^-")
endforeach ()
CONFIGURE_FILE("musidy.pc.in" "musidy.pc" @ONLY)
INSTALL(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/musidy.pc"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig"
)
