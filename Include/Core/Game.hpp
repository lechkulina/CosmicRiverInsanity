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
#include <Core/AbstractSubsystem.hpp>
#include <Core/ComposedSubsystem.hpp>
#include <Core/VideoContext.hpp>
#include <Core/Texture.hpp>
#include <Core/Music.hpp>
#include <Game/Spacecraft.hpp>

namespace Cosmic {

namespace Core {

    enum class GameState : int {
        Startup,
        Menu,
        Running,
        Paused,
        Shutdown
    };

    class Game : public AbstractSubsystem {
        public:
            Game();
            virtual ~Game();

            virtual bool isInitialized() const;
            int execute();

        private:
            Common::Logger logger;
            GameState gameState;
            ComposedSubsystem composedSubsystem;
            boost::shared_ptr<VideoContext> videoContext;

            boost::shared_ptr<Texture> texture;
            boost::shared_ptr<Music> music;
            boost::shared_ptr<Cosmic::Game::Spacecraft> spacecraft;

            void handleEvent(const SDL_Event& event);
            void updateFrame(float deltaTime);
            void renderFrame();
            void resetFrame();
    };

}

}

#endif /* GAME_HPP_ */
