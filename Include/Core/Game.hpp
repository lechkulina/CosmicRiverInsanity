/*
 * Game.hpp
 *
 * Created on: 26 kwi 2014
 * Author: Lech Kulina
 * E-Mail: kulinalech@gmail.com
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <fstream>
#include <boost/log/common.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <SDL.h>

namespace Cosmic {

namespace Core {

    enum class GameState : int {
        Startup,
        Menu,
        Running,
        Paused,
        Shutdown
    };

    enum SeverityLevel : int {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

    typedef boost::log::sources::severity_logger<SeverityLevel> SeverityLogger;

    class Game {
        public:
            Game();
            ~Game();

            int execute();

        private:
            SeverityLogger logger;
            SDL_Window* m_window;
            SDL_Renderer* m_renderer;
            GameState m_gameState;

            void handleEvent(const SDL_Event& event);
            void processFrame();
    };

}

}

#endif /* GAME_HPP_ */
