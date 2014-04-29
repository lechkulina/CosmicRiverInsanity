/*
 * main.cpp
 *
 * Created on: 20 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#include <Common/Common.hpp>
#include <Core/Game.hpp>

int main(int argc, char** argv) {
    COSMIC_UNUSED(argc);
    COSMIC_UNUSED(argv);
    Cosmic::Core::Game game;

    return game.execute();
}


