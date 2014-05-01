/*
 * Game.hpp
 *
 * Created on: 26 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SDL.h>
#include <Common/Logging.hpp>
#include <Core/ComposedSubsystem.hpp>

namespace Cosmic {

namespace Core {

    enum class GameState : int {
        Startup,
        Menu,
        Running,
        Paused,
        Shutdown
    };

    class Game {
        public:
            Game();
            ~Game();

            int execute();

        private:
            Common::Logger logger;
            ComposedSubsystem composedSubsystem;
            GameState gameState;

            void handleEvent(const SDL_Event& event);
            void processFrame();
    };

}

}

#endif /* GAME_HPP_ */
