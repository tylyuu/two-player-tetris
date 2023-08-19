cmake_minimum_required(VERSION 3.25)
project(puppppy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Include directories
include_directories(puppytest/blocks)
include_directories(puppytest/board)
include_directories(puppytest/controller)
include_directories(puppytest/display)

# Add source files
add_executable(puppppy
        puppytest/blocks/block.cc
        puppytest/blocks/block.h
        puppytest/blocks/fblock.cc
        puppytest/blocks/fblock.h
        puppytest/blocks/iblock.cc
        puppytest/blocks/iblock.h
        puppytest/blocks/jblock.cc
        puppytest/blocks/jblock.h
        puppytest/blocks/lblock.cc
        puppytest/blocks/lblock.h
        puppytest/blocks/oblock.cc
        puppytest/blocks/oblock.h
        puppytest/blocks/sblock.cc
        puppytest/blocks/sblock.h
        puppytest/blocks/tblock.cc
        puppytest/blocks/tblock.h
        puppytest/blocks/zblock.cc
        puppytest/blocks/zblock.h
        puppytest/board/board.cc
        puppytest/board/board.h
        puppytest/board/cell.cc
        puppytest/board/cell.h
        puppytest/board/game.cc
        puppytest/board/game.h
        puppytest/board/generator.cc
        puppytest/board/generator.h
        puppytest/board/player.cc
        puppytest/board/player.h
        puppytest/board/subject.cc
        puppytest/board/subject.h
        puppytest/controller/controller.cc
        puppytest/controller/controller.h
        puppytest/controller/trienode.cc
        puppytest/controller/trienode.h
        puppytest/display/observer.cc
        puppytest/display/observer.h
        puppytest/display/text.cc
        puppytest/display/text.h
        puppytest/display/window.cc
        puppytest/display/window.h
        puppytest/main.cc puppytest/display/graphic.cc)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Link SFML libraries
target_link_libraries(puppppy sfml-graphics sfml-window sfml-system)
