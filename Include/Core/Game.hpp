/*
 * Game.hpp
 *
 * Created on: 26 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <list>
#include <SDL.h>
#include <Common/Logging.hpp>
#include <Core/SubsystemsManager.hpp>

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
            boost::log::sources::severity_channel_logger<Common::Severity, std::string> logger;
            SubsystemsManager subsystemsManager;
            SDL_Window* m_window;
            SDL_Renderer* m_renderer;
            GameState m_gameState;

            void handleEvent(const SDL_Event& event);
            void processFrame();
    };

}

}

#endif /* GAME_HPP_ */
