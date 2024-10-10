cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

# Add SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(untitled
        main.cpp
        Board.cpp
        Tile.hpp
        Tile.cpp
        Property.hpp
        Property.cpp
        Player.hpp
        Player.cpp
        Game.hpp
        Game.cpp
        Board.hpp
        SpecialTile.hpp
        SpecialTile.cpp
        Street.hpp
        Street.cpp
        Train.hpp
        Train.cpp
        Utility.hpp
        Utility.hpp
        Utility.cpp
        Logger.hpp
        Logger.cpp
        #tests.cpp
)

# Link SFML libraries
target_link_libraries(untitled sfml-graphics sfml-window sfml-system)
