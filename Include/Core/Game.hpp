/*
 * Game.hpp
 *
 * Created on: 26 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <boost/shared_ptr.hpp>
#include <SDL.h>
#include <Common/Logging.hpp>
#include <Core/ComposedSubsystem.hpp>
#include <Core/VideoContext.hpp>

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
            boost::shared_ptr<VideoContext> videoContext;
            GameState gameState;

            void handleEvent(const SDL_Event& event);
            void processFrame();
    };

}

}

#endif /* GAME_HPP_ */
